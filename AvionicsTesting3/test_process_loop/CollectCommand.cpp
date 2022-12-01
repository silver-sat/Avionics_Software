/**
 * @file CollectCommand.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Collect command, validate signature, and parse parameters
 * @version 1.0.0
 * @date 2022-09-27
 *
 *
 */

#include "CollectCommand.h"
#include "arduino_secrets.h"
#include "log_utility.h"
#include "mock_radio_board.h"
#include <BLAKE2s.h>

/**
 * @brief Construct a new CollectCommand::CollectCommand object
 *
 */

CollectCommand::CollectCommand(){};

/**
 * @brief Destroy the CollectCommand::CollectCommand object
 *
 */

CollectCommand::~CollectCommand()
{
    delete_command();
};

/**
 * @brief Check for command
 *
 * @return true no command or successful
 * @return false error
 */

bool CollectCommand::check_for_command()
{
    extern MockRadioBoard radio;
    if (radio.receive_command(m_command_buffer, maximum_command_length))
    {
        String command_string{m_command_buffer};
        make_command(command_string);
        m_command->acknowledge_command();
        Log.traceln("Command acknowledged");
        if (m_command->execute_command())
        {
            Log.traceln("Executed (%l executed, %l failed, next sequence %l)", ++m_successful_commands, m_failed_commands, m_command_sequence);
            delete_command();
            return true;
        }
        else
        {
            Log.errorln("Failed (%l executed, %l failed, next sequence %i)", m_successful_commands, ++m_failed_commands, m_command_sequence);
            delete_command();
            return false;
        };
    };
    return true;
};

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
// an even number of [0-9a-f] characters, and target to be sufficiently large

void hex2bin(const char *src, byte *target)
{
    while (*src && src[1])
    {
        *(target++) = (char2int(*src) << 4) + char2int(src[1]);
        src += 2;
    }
};

/**
 * @brief Validate the commmand signature
 *
 * @param buffer sequence, salt, command and HMAC
 * @param command_string output: command and parameters
 * @return true if valid
 * @return false if invalid
 */

bool CollectCommand::validate_signature(String &buffer, String &command_string)
{
    buffer.trim();
    size_t buffer_index = buffer.indexOf(command_message_separator);

    if (buffer_index == -1)
    {
        Log.verboseln("Command is not signed");
        command_string = buffer;
    }
    else
    {

        Log.verboseln("Command is signed", command_message_separator);

        // tokenize the buffer

        String buffer_tokens[buffer_token_limit]{};
        size_t buffer_token_index{0};
        size_t token_start_index{0};
        for (auto buffer_token_index = 0; buffer_token_index < buffer_token_limit; buffer_token_index++)
        {
            auto token_end_index = buffer.indexOf(command_message_separator, token_start_index);
            buffer_tokens[buffer_token_index] = buffer.substring(token_start_index, token_end_index++);
            token_start_index = token_end_index;
        }
        command_string = buffer_tokens[2];

        // validate sequence number

        for (auto index = 0; index < buffer_tokens[0].length(); index++)
        {
            if (!isDigit(buffer_tokens[0].charAt(index)))
            {
                if (m_validation_required)
                {
                    Log.errorln("Sequence is not a digit");
                    return false;
                }
                else
                {
                    Log.warningln("Sequence is not a digit");
                    break;
                }
            }
        }

        long command_sequence{buffer_tokens[0].toInt()};
        if (command_sequence != m_command_sequence)
        {
            if (m_validation_required)
            {

                Log.errorln("Command sequence invalid");
                return false;
            }
            else
            {
                Log.infoln("Command sequence invalid");
            }
        }
        else
        {
            Log.verboseln("Command sequence is valid");
            m_command_sequence++;
        }

        // todo: check for validation requirement
        // todo: check for valid lengths
        // todo: consider enforcing command sequence numbers

        const size_t sequence_length{buffer_tokens[0].length()};
        byte sequence[maximum_sequence_length]{};
        buffer_tokens[0].getBytes(sequence, maximum_sequence_length);

        const size_t salt_length{buffer_tokens[1].length()};
        byte salt[salt_size]{};
        hex2bin(buffer_tokens[1].c_str(), salt);

        const size_t command_length{buffer_tokens[2].length()};
        byte command[maximum_command_length]{};
        buffer_tokens[2].getBytes(command, maximum_command_length);

        const size_t sourceHMAC_length = buffer_tokens[3].length();
        byte sourceHMAC[HMAC_size]{};
        hex2bin(buffer_tokens[3].c_str(), sourceHMAC);

        const size_t secret_length = 16;
        const byte secret[]{SECRET_HASH_KEY};

        byte HMAC[HMAC_size];
        String hexHMAC{};

        BLAKE2s blake{};
        blake.resetHMAC(&secret, secret_size);
        blake.update(&sequence, sequence_length);
        blake.update(&command_message_separator, 1);
        blake.update(&salt, salt_size);
        blake.update(&command_message_separator, 1);
        blake.update(&command, command_length);
        blake.finalizeHMAC(secret, secret_size, HMAC, HMAC_size);
        for (auto index = 0; index < HMAC_size; index++)
        {
            if (HMAC[index] < 0x10)
            {
                hexHMAC += "0";
            };
            hexHMAC += String(HMAC[index], HEX);
        }

        Log.verboseln("Computed HMAC: %s", hexHMAC.c_str());
        if (hexHMAC == buffer_tokens[3])
        {
            Log.traceln("Command signature valid");
            return true;
        }
        else
        {
            if (m_validation_required)
            {
                Log.errorln("Command signature invalid");
                return false;
            }
            else
            {
                Log.warningln("Command signature invalid");
                return true;
            }
        }
    }
    return true;
};

/**
 * @brief Parse command parameters
 *
 * @param command_string command string
 * @param command_tokens output: tokens
 * @param token_index output: number of tokens
 * @return true successful
 * @return false failure
 */

bool CollectCommand::parse_parameters(const String &command_string, String command_tokens[], size_t &token_index)
{

    Log.verboseln("Parsing command");
    token_index = 0;
    for (auto string_index = 0; string_index < command_string.length(); string_index++)
    {
        if (command_string.charAt(string_index) != ' ')
        {
            command_tokens[token_index] += command_string.charAt(string_index);
        }
        else
        {
            Log.verboseln("Token processed: %s", command_tokens[token_index].c_str());
            if (token_index++ > command_token_limit)
            {
                Log.warningln("Too many command parameters");
                return false;
            }
        }
    }

    Log.verboseln("Token processed: %s", command_tokens[token_index].c_str());
    if (token_index > command_token_limit)
    {
        Log.warningln("Too many command parameters");
        return false;
    }
    return true;
};

/**
 * @brief Make command object
 *
 * @return next command to process
 *
 */

bool CollectCommand::make_command(String buffer)
{

    // validate signature

    String command_string;
    validate_signature(buffer, command_string);

    // tokenize the command string and create the command object

    String command_tokens[command_token_limit]{};
    size_t token_count{0};
    if (parse_parameters(command_string, command_tokens, token_count))
    {
        Log.traceln("Constructing command object");
        m_factory = new BuildCommand(command_tokens, token_count);
        m_command = m_factory->get_command();
        return true;
    }
    else
    {
        return false;
    }
};

/**
 * @brief Delete the command and the factory
 *
 * @return true successful
 * @return false erroe
 */
bool CollectCommand::delete_command()
{

    // destroy the command

    if (m_command)
    {
        delete m_command;
        m_command = NULL;
    }

    // destroy the factory

    if (m_factory)
    {
        delete m_factory;
        m_factory = NULL;
    }

    return true;
}
