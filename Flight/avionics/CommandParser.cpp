/**
 * @file CommandParser.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Collect command and parse parameters
 * @version 1.1.0
 * @date 2022-09-27
 *
 * This file implements the class which parses command parameters
 * 
 */
#include "CommandParser.h"
#include "log_utility.h"
#include "RadioBoard.h"

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
        *(target++) = static_cast<byte>((char2int(*src) << 4) | char2int(src[1]));
        src += 2;
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
            // todo: complier warning: conversion to 'unsigned int' from 'int' may change the sign of the result (next_blank)
            command_tokens[token_index++] = command.substring(0, next_blank);
            // todo: complier warning: conversion to 'unsigned int' from 'int' may change the sign of the result (next_blank)
            command = command.substring(next_blank);
        }
    }
    token_count = token_index;
    return true;
}
