/**
 * @author Lee A. Congdon (lee@silversat.org)
 * @author Benjamin S. Cohen (ben@silversat.org)
 * @brief Manage command processing
 *
 * This file implements the class that checks for ground commands, validates
 * and retrieves them and checks for local responses and commands and processes them
 *
 */

#include "CommandProcessor.h"
#include "log_utility.h"
#include "Response.h"
#include "AvionicsBoard.h"
#include "RadioBoard.h"
#include "PowerBoard.h"
#include "arduino_secrets.h"
#include "BLAKE2s.h"

// Command constants

constexpr auto hmac_length{32};                                                                                       /**< HMAC length in bytes */
constexpr auto hmac_length_hex_ascii{hmac_length * 2};                                                                /**< HMAC length as hex characters */
constexpr auto salt_length{8};                                                                                        /**< Salt length in bytes */
constexpr auto salt_length_hex_ascii{salt_length * 2};                                                                /**< Salt length as hex characters */
constexpr auto sequence_length{4};                                                                                    /**< Sequence length in bytes */
constexpr auto sequence_length_hex_ascii{sequence_length * 2};                                                        /**< Sequence length as hex characters */
constexpr auto signature_length_hex_ascii{hmac_length_hex_ascii + salt_length_hex_ascii + sequence_length_hex_ascii}; /**< Signature length as hex ascii */
constexpr unsigned long validation_entry_timeout = 30 * seconds_to_milliseconds;                                      /**< Bypass validation delay */
constexpr auto radio_response_limit{191};                                                                             /**< Radio response limit, does not include 'RES GRS ' */

/**
 * @brief Helper function to determine if a string is hexadecimal digits
 *
 */

bool is_hex(const String &str)
{
    for (auto i{0}; i < str.length(); i++)
    {
        if (!isxdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}

/**
 * @brief Helper function for hexadecimal text to binary conversion
 *
 * @param input a character in one of the ranges 0-9, a-f, or A-F
 * @return int value of the hexadecimal representation (e.g. "A" == 0x0A, decimal 10)
 */

int char2int(const char input)
{
    if (input >= '0' && input <= '9')
        return input - '0';
    if (input >= 'A' && input <= 'F')
        return input - 'A' + 10;
    if (input >= 'a' && input <= 'f')
        return input - 'a' + 10;
    return 0; // invalid data
};

/**
 * @brief Convert hexadecimal text representation to binary values
 *
 * @param src hexadecimal representation
 * @param target binary values
 */

// This function assumes src to be a zero terminated sanitized string with
// an even number of [0-9a-f] characters and target to be sufficiently large

void hex2bin(const char *src, byte *target)
{
    while (*src && src[1])
    {
        *(target++) = (char2int(*src) << 4) + char2int(src[1]);
        src += 2;
    }
};

/**
 * @brief Check for command from Radio Board
 *
 * @return true no command or successful
 * @return false error
 *
 * Check to determine if the Radio Board has received a frame. If so, either
 * validate, acknowledge and execute ground command or process local message
 *
 */
bool CommandProcessor::check_for_command()
{
    extern RadioBoard radio;
    if (radio.receive_frame())
    {
        auto frame{radio.get_frame()};
        Log.noticeln("Frame received on serial port");
        auto command_code{frame.type};
        Log.verboseln("Command code: %x", command_code);
        String command_string{frame.command};
        Log.verboseln("Command string: %s", command_string.c_str());

        switch (command_code)
        {
        // Ground command
        case REMOTE_FRAME:
        {
            auto valid_signature{validate_signature(command_string)};
            if (!valid_signature)
            {
                Log.errorln("Invalid digital signature");
                return false;
            }
            Log.verboseln("Command signature is valid");
            Command *command{get_command(command_string.substring(signature_length_hex_ascii))};
            command->acknowledge_receipt();
            Log.traceln("Acknowledge completed");

            if (command->execute())
            {
                Log.traceln("Executed (%l executed, %l failed)", ++m_successful_commands, m_failed_commands);
                return true;
            }
            else
            {
                Log.errorln("Failed (%l executed, %l failed)", m_successful_commands, ++m_failed_commands);
                return false;
            }
            break;
        }
        // Local response
        case LOCAL_FRAME:
        {
            if (command_string.startsWith(RES))
            {
                auto response_type_end{command_string.indexOf(' ', RES.length() + 1)};
                auto response_type_char{command_string.substring(RES.length() + 1, response_type_end)};
                auto response_type_length{response_type_char.length()};
                if (!is_hex(response_type_char) || response_type_char.length() < 1 || response_type_char.length() > 2)
                {
                    Log.errorln("Invalid response type");
                    return false;
                }
                if ((response_type_length % 2) != 0)
                {
                    response_type_char = "0" + response_type_char; // hex2bin requires even number of characters
                }
                byte response_type{};
                hex2bin(response_type_char.c_str(), &response_type);
                auto radio_data{command_string.substring(RES.length() + 1 + response_type_length + 1)};
                if (radio_data.length() == 0)
                {
                    Log.verboseln("Response type: %X", response_type);
                }
                else
                {
                    Log.verboseln("Response type: %X, content: %s", response_type, radio_data.c_str());
                }
                switch (response_type)
                {
                case GET_RADIO_STATUS:
                    // todo: refactor quick test
                    Response{"GRS " + radio_data.substring(0, radio_response_limit)}.send();
                    break;
                default:
                    break;
                }
            }
            break;
        }
        // Cycle radio 5v
        case TOGGLE_RADIO_5V:
        {
            if (command_string.length() == 0 && command_code == TOGGLE_RADIO_5V)
            {
                Log.verboseln("Received reset 5v from radio");
                extern PowerBoard power;
                power.cycle_radio_5v();
            }
            break;
        }
        default:
            break;
        }
    }
    return true;
}

/**
 * @brief Validate command signature
 *
 * @param buffer
 * return true valid signature
 *
 * Validate the signature for ground commands
 *
 */

bool CommandProcessor::validate_signature(const String &buffer)
{
    Log.verboseln("Validating command signature");

    if (buffer.length() < signature_length_hex_ascii)
    {
        Log.errorln("Invalid command length");
        return false;
    }

    String hmac_hex_ascii{buffer.substring(0, hmac_length_hex_ascii)};
    // Log.verboseln("HMAC: %s", hmac_hex_ascii.c_str());
    byte hmac[hmac_length]{};
    hex2bin(hmac_hex_ascii.c_str(), hmac);

    String salt_hex_ascii{buffer.substring(hmac_length_hex_ascii, hmac_length_hex_ascii + salt_length_hex_ascii)};
    // Log.verboseln("Salt: %s", salt_hex_ascii.c_str());
    byte salt[salt_length]{};
    hex2bin(salt_hex_ascii.c_str(), salt);

    String sequence_hex_ascii{buffer.substring(hmac_length_hex_ascii + salt_length_hex_ascii, hmac_length_hex_ascii + salt_length_hex_ascii + sequence_length_hex_ascii)};
    Log.verboseln("Sequence: %s", sequence_hex_ascii.c_str());
    if (m_command_sequence == sequence_hex_ascii.toInt())
    {
        Log.verboseln("Sequence number is valid");
        ++m_command_sequence;
    }
    else
    {
        Log.errorln("Invalid sequence number, expected %l", m_command_sequence);
        if (m_validate_sequence)
        {
            return false;
        }
    }
    String command{buffer.substring(signature_length_hex_ascii)};
    Log.verboseln("Command: %s", command.c_str());

    BLAKE2s blake{};
    byte secret[]{SECRET_HASH_KEY};
    byte computed_hmac[hmac_length]{};
    blake.resetHMAC(secret, sizeof(secret));
    blake.update(salt, salt_length);
    blake.update(sequence_hex_ascii.c_str(), sequence_length_hex_ascii);
    blake.update(command.c_str(), buffer.length() - signature_length_hex_ascii);
    blake.finalizeHMAC(secret, sizeof(secret), computed_hmac, hmac_length);
    return memcmp(computed_hmac, hmac, hmac_length) == 0;
}

/**
 * @brief Retrieve command object
 *
 * @param buffer
 * @return next command to process
 *
 * For ground commands parse parameters and retrieve Command object
 *
 */

Command *CommandProcessor::get_command(const String &buffer)
{

    // tokenize the command string and retrieve the command object

    String command_string{buffer};
    size_t token_count{0};
    String command_tokens[command_parameter_limit]{};
    command_string.trim();
    if (parse_parameters(command_string, command_tokens, token_count))
    {
        Log.traceln("Retrieving command object");
        return command_warehouse.RetrieveCommand(command_tokens, token_count);
    }
    else
    {
        Log.errorln("Invalid command");
        String invalid[]{"Invalid"};
        return command_warehouse.RetrieveCommand(invalid, 1);
    }
}

/**
 * @brief Parse command parameters
 *
 * @param[in] command_string command string
 * @param[out] command_tokens tokens
 * @param[out] token_count number of tokens
 * @return true successful
 * @return false failure
 */

bool CommandProcessor::parse_parameters(const String &command_string, String command_tokens[], size_t &token_count)
{
    size_t token_index{0};
    String command{command_string};
    while (command.length() > 0)
    {
        if (token_index >= command_parameter_limit)
        {
            Log.warningln("Too many command parameters");
            return false;
        }
        command.trim();
        int next_blank{command.indexOf(' ')};
        if (next_blank == -1)
        {
            command_tokens[token_index++] = command;
            command = "";
        }
        else
        {
            command_tokens[token_index++] = command.substring(0, static_cast<unsigned int>(next_blank));
            command = command.substring(static_cast<unsigned int>(next_blank));
        }
    }
    token_count = token_index;
    return true;
}

/**
 * @brief Get sequence
 *
 * @return sequence number
 *
 * Get last successful command sequence number
 *
 */

String CommandProcessor::get_sequence()
{
    return String{m_command_sequence - 1}; // last successful command sequence number is one less than the expected sequence number
}

/**
 * @brief Get validation
 *
 * @return true successful
 * @return false error
 *
 * Get validation status
 *
 */

bool CommandProcessor::get_validation()
{
    unsigned long start_time{millis()};
    char incoming_char{};
    extern AvionicsBoard avionics;

    Serial.print("Press 'n' or 'N' to bypass command sequence validation: ");

    while (millis() - start_time < validation_entry_timeout)
    {
        avionics.service_watchdog(); // service the watchdog while waiting
        if (Serial.available() > 0)
        {
            incoming_char = Serial.read();
            if (incoming_char != 'n' && incoming_char != 'N')
            {
                Serial.write(BELL);
                continue;
            }
            Serial.println(incoming_char);
            Log.noticeln("Command sequence numbers will not be validated");
            m_validate_sequence = false;
            return true;
        }
    }
    Serial.println();
    Log.noticeln("Timeout during validation entry, command sequence numbers will be validated");
    m_validate_sequence = true;
    return false;
}