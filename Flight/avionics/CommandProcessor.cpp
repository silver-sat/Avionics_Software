/**
 * @file CommandProcessor.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @author Benjamin S. Cohen (ben@silversat.org)
 * @brief Manage command processing
 * @version 1.0.0
 * @date 2022-12-07
 *
 * This file implements the class that checks for ground commands, validates
 * and retrieves them and checks for local responses and commands and processes them
 *
 */

#include "CommandProcessor.h"
#include "log_utility.h"
#include "Response.h"
#include "RadioBoard.h"
#include "PowerBoard.h"
#include "arduino_secrets.h"
#include "BLAKE2s.h"

/**
 * @brief Command constants
 *
 */
constexpr auto hmac_length{32};                                                                                       /**< HMAC length in bytes */
constexpr auto hmac_length_hex_ascii{hmac_length * 2};                                                                /**< HMAC length as hex characters */
constexpr auto salt_length{8};                                                                                        /**< Salt length in bytes */
constexpr auto salt_length_hex_ascii{salt_length * 2};                                                                /**< Salt length as hex characters */
constexpr auto sequence_length{4};                                                                                    /**< Sequence length in bytes */
constexpr auto sequence_length_hex_ascii{sequence_length * 2};                                                        /**< Sequence length as hex characters */
constexpr auto signature_length_hex_ascii{hmac_length_hex_ascii + salt_length_hex_ascii + sequence_length_hex_ascii}; /**< Signature length as hex ascii */

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
        Log.verboseln("Command code: %X", command_code);
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
                Log.errorln("Invalid digitial signature");
                return false;
            }
            Log.verboseln("Command signature is valid");
            Command *command{get_command(command_string.substring(signature_length_hex_ascii))};
            command->acknowledge_command();
            Log.traceln("Command acknowledged");

            if (command->execute_command())
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
            if (command_string.length() > RES.length() && command_string.startsWith(RES))
            {
                auto response_type{command_string[RES.length()]};
                auto radio_data{command_string.substring(RES.length() + 1)};
                Log.verboseln("Response type: %X, content: %s", response_type, radio_data.c_str());
                switch (response_type)
                {
                case GET_RADIO_STATUS:
                    Response{"GRS " + radio_data}.send();
                    break;
                case MODIFY_MODE:
                    Response{"RMM " + radio_data}.send();
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
    Log.verboseln("Validating signature of command");

    String hmac_hex_ascii{buffer.substring(0, hmac_length_hex_ascii)};
    Log.verboseln("HMAC: %s", hmac_hex_ascii.c_str());
    byte hmac[hmac_length]{};
    hex2bin(hmac_hex_ascii.c_str(), hmac);

    String salt_hex_ascii{buffer.substring(hmac_length_hex_ascii, hmac_length_hex_ascii + salt_length_hex_ascii)};
    Log.verboseln("Salt: %s", salt_hex_ascii.c_str());
    byte salt[salt_length]{};
    hex2bin(salt_hex_ascii.c_str(), salt);

    String sequence_hex_ascii{buffer.substring(hmac_length_hex_ascii + salt_length_hex_ascii, hmac_length_hex_ascii + salt_length_hex_ascii + sequence_length_hex_ascii)};
    Log.verboseln("Sequence: %s", sequence_hex_ascii.c_str());

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
    if (command_parser.parse_parameters(command_string, command_tokens, token_count))
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
