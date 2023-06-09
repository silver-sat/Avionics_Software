/**
 * @file CommandParser.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Collect command, validate signature, and parse parameters
 * @version 1.1.0
 * @date 2022-09-27
 *
 * This file implements the class which parses command parameters and validates command signatures
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
 *
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
}

/**
 * @brief Convert hexadecimal text representation to binary values
 *
 * @param src hexadecimal representation
 * @param target binary values
 *
 * This function assumes src to be a zero terminated sanitized string with
 * an even number of [0-9a-f] characters and target to be sufficiently large
 *
 */

void hex2bin(const char *src, byte *target)
{
    while (*src && src[1])
    {
        *(target++) = (char2int(*src) << 4) + char2int(src[1]);
        src += 2;
    }
}

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
 * @param[in, out] expected_sequence next valid command sequence number
 * @return true valid signature
 * @return false invalid signature
 *
 */

bool CommandParser::validate_signature(String &buffer, String &command_string, const bool validation_required, long &expected_sequence)
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

        // Separate the buffer into the signed command parts

        String buffer_parts[buffer_part_limit]{};
        size_t part_start_index{0};
        for (size_t buffer_part_index = 0; buffer_part_index < buffer_part_limit; ++buffer_part_index)
        {
            auto part_end_index = buffer.indexOf(command_message_separator, part_start_index);
            buffer_parts[buffer_part_index] = buffer.substring(part_start_index, part_end_index);
            part_start_index = ++part_end_index;
        }
        command_string = buffer_parts[2];

        // Verify sequence contains digits
        // todo: consider enforcing command sequence numbers

        for (unsigned int index = 0; index < buffer_parts[0].length(); ++index)
            if (!isDigit(buffer_parts[0].charAt(index)))
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

        // Validate sequence number

        long transmitted_sequence{buffer_parts[0].toInt()};
        if (transmitted_sequence != expected_sequence)
            if (validation_required)
            {
                Log.errorln("Command sequence invalid");
                return false;
            }
            else
                Log.warningln("Command sequence invalid");
        else
        {
            Log.verboseln("Command sequence valid");
            ++expected_sequence;
        }

        // Marshal sequence, salt, command, and HMAC as ascii characters

        const size_t sequence_length{buffer_parts[0].length()};
        byte sequence[maximum_sequence_length]{};
        buffer_parts[0].getBytes(sequence, maximum_sequence_length);

        byte salt[salt_size]{};
        hex2bin(buffer_parts[1].c_str(), salt);

        const size_t command_length{buffer_parts[2].length()};
        byte command[maximum_command_length]{};
        buffer_parts[2].getBytes(command, maximum_command_length);

        byte sourceHMAC[HMAC_size]{};
        hex2bin(buffer_parts[3].c_str(), sourceHMAC);

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
        for (size_t index = 0; index < HMAC_size; ++index)
        {
            if (HMAC[index] < 0x10)
                hexHMAC += "0"; // insert leading zero for single digit hex values
            hexHMAC += String(HMAC[index], HEX);
        }

        // Validate HMAC

        Log.verboseln("Computed HMAC: %s", hexHMAC.c_str());
        if (hexHMAC == buffer_parts[3])
        {
            Log.traceln("Command signature valid");
            return true;
        }
        else if (validation_required)
        {
            Log.errorln("Command signature invalid");
            return false;
        }
        else
            Log.warningln("Command signature invalid");
    }
    return true;
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

bool CommandParser::parse_parameters(const String &command_string, String command_tokens[], size_t &token_count)
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
            command_tokens[token_index++] = command.substring(0, next_blank);
            command = command.substring(next_blank);
        }
    }
    token_count = token_index;
    return true;
}
