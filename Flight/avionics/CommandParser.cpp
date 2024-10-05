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
            command_tokens[token_index++] = command.substring(0, static_cast<unsigned int>(next_blank));
            command = command.substring(static_cast<unsigned int>(next_blank));
        }
    }
    token_count = token_index;
    return true;
}
