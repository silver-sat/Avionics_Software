/**
 * @file CommandParser.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Collect command, validate signature, and parse parameters
 * @version 1.1.0
 * @date 2022-09-27
 *
 *
 */
#include "CommandParser.h"
#include "arduino_secrets.h"
#include "log_utility.h"
#include "RadioBoard.h"
#include <BLAKE2s.h>

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
 * @brief Validate the commmand signature
 *
 * Properly formed commands consist of four parts, separated by the
 * command_message_separator character
 *
 * 1. Sequence number, ascii digits, variable length up to maximum_sequence_length
 * 2. Salt, ascii hexadecial digits, fixed length of salt_size
 * 3. Command, ascii characters, command and space separated parameters, variable length
 *      up to maximum_command_length
 * 4. HMAC, ascii hexadecimal digits, fixed length of HMAC_soize
 *
 *
 * @param[in] buffer sequence, salt, command and HMAC
 * @param[out] command_string command and parameters
 * @param[in] validation_required true if command must have valid signature
 * @param[in, out] command_sequence next valid command sequence number
 * @return true valid signature
 * @return false invalid signature
 */

bool CommandParser::validate_signature(String &buffer, String &command_string, bool validation_required, long &expected_sequence)
{
    buffer.trim();
    auto buffer_index = buffer.indexOf(command_message_separator);

    if (buffer_index == -1)
    {
        Log.verboseln("Command is not signed");
        command_string = buffer;
    }
    else
    {

        Log.verboseln("Command is signed", command_message_separator);

        // Tokenize the buffer

        String buffer_tokens[buffer_token_limit]{};
        size_t token_start_index{0};
        for (size_t buffer_token_index = 0; buffer_token_index < buffer_token_limit; buffer_token_index++)
        {
            auto token_end_index = buffer.indexOf(command_message_separator, token_start_index);
            buffer_tokens[buffer_token_index] = buffer.substring(token_start_index, token_end_index++);
            token_start_index = token_end_index;
        }
        command_string = buffer_tokens[2];

        // Verify sequence contains digits
        // todo: consider enforcing command sequence numbers

        for (unsigned int index = 0; index < buffer_tokens[0].length(); index++)
        {
            if (!isDigit(buffer_tokens[0].charAt(index)))
            {
                if (validation_required)
                {
                    Log.errorln("Sequence character is not a digit");
                    return false;
                }
                else
                {
                    Log.warningln("Sequence character is not a digit");
                    break;
                }
            }
        }

        // Validate sequence number

        long transmitted_sequence{buffer_tokens[0].toInt()};
        if (transmitted_sequence != expected_sequence)
        {
            if (validation_required)
            {
                Log.errorln("Command sequence invalid");
                return false;
            }
            else
            {
                Log.warningln("Command sequence invalid");
            }
        }
        else
        {
            Log.verboseln("Command sequence valid");
            expected_sequence++;
        }

        // Marshal sequence, salt, command, and HMAC as ascii characters

        const size_t sequence_length{buffer_tokens[0].length()};
        byte sequence[maximum_sequence_length]{};
        buffer_tokens[0].getBytes(sequence, maximum_sequence_length);

        byte salt[salt_size]{};
        hex2bin(buffer_tokens[1].c_str(), salt);

        const size_t command_length{buffer_tokens[2].length()};
        byte command[maximum_command_length]{};
        buffer_tokens[2].getBytes(command, maximum_command_length);

        byte sourceHMAC[HMAC_size]{};
        hex2bin(buffer_tokens[3].c_str(), sourceHMAC);

        // Generate HMAC with shared secret

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
        for (size_t index = 0; index < HMAC_size; index++)
        {
            if (HMAC[index] < 0x10)
            {
                hexHMAC += "0"; // insert leading zero for single digit hex values
            };
            hexHMAC += String(HMAC[index], HEX);
        }

        // Validate HMAC

        Log.verboseln("Computed HMAC: %s", hexHMAC.c_str());
        if (hexHMAC == buffer_tokens[3])
        {
            Log.traceln("Command signature valid");
            return true;
        }
        else
        {
            if (validation_required)
            {
                Log.errorln("Command signature invalid");
                return false;
            }
            else
            {
                Log.warningln("Command signature invalid");
            }
        }
    }
    return true;
};

/**
 * @brief Parse command parameters
 *
 * @param[in] command_string command string
 * @param[out] command_tokens tokens
 * @param[out] token_index number of tokens
 * @return true successful
 * @return false failure
 */

bool CommandParser::parse_parameters(const String &command_string, String command_tokens[], size_t &token_index)
{

    Log.verboseln("Parsing command");
    token_index = 0;
    for (unsigned int string_index = 0; string_index < command_string.length(); string_index++)
    {
        if (command_string.charAt(string_index) != ' ')
        {
            command_tokens[token_index] += command_string.charAt(string_index);
        }
        else
        {
            Log.verboseln("Token processed: %s", command_tokens[token_index].c_str());
            if (token_index++ > command_parameter_limit)
            {
                Log.warningln("Too many command parameters");
                return false;
            }
        }
    }
    // todo: evaluate duplicate code
    Log.verboseln("Token processed: %s", command_tokens[token_index].c_str());
    if (token_index > command_parameter_limit)
    {
        Log.warningln("Too many command parameters");
        return false;
    }
    return true;
};
