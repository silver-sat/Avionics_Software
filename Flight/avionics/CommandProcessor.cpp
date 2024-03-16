/**
 * @file CommandProcessor.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Manage command processing
 * @version 1.0.0
 * @date 2022-12-07
 *
 * This file implements the class that checks for ground commands, validates
 * and creates them and checks for local responses and processes them
 *
 */

#include "CommandProcessor.h"
#include "log_utility.h"
#include "Response.h"
#include "RadioBoard.h"

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
    if (radio.receive_frame(m_command_buffer, maximum_command_length, m_source))
    {
        String command_string{m_command_buffer};
        Log.verboseln("Command source: %X", m_source);
        if (m_source == REMOTE_FRAME)
        {
            Command *command{make_command(command_string)};
            Log.verboseln("Command object memory address: %s", ("0x" + String(reinterpret_cast<uint32_t>(command), HEX)).c_str());
            command->acknowledge_command();
            Log.traceln("Command acknowledged");

            if (command->execute_command())
            {
                Log.traceln("Executed (%l executed, %l failed, next sequence %l)", ++m_successful_commands, m_failed_commands, m_command_sequence);
                delete command;
                return true;
            }
            else
            {
                Log.errorln("Failed (%l executed, %l failed, next sequence %l)", m_successful_commands, ++m_failed_commands, m_command_sequence);
                delete command;
                return false;
            }
        }
        else
        {
            if (command_string.length() > RES.length() && command_string.startsWith(RES))
            {
                auto command_type{command_string[RES.length()]};
                auto radio_data{command_string.substring(RES.length() + 1)};
                Log.verboseln("Received type: %X, %s", command_type, radio_data.c_str());
                switch (command_type)
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
        }
    }
    return true;
}

/**
 * @brief Make command object
 *
 * @param buffer
 * @return next command to process
 *
 * For ground commands, validate signature, parse parameters, and construct
 * Command object
 *
 */

Command *CommandProcessor::make_command(String buffer)
{

    // validate signature

    String command_string;
    command_parser.validate_signature(buffer, command_string, m_validation_required, m_command_sequence);

    // tokenize the command string and create the command object

    size_t token_count{0};
    String command_tokens[command_parameter_limit]{};
    if (command_parser.parse_parameters(command_string, command_tokens, token_count))
    {
        Log.traceln("Constructing command object");
        return command_factory.BuildCommand(command_tokens, token_count);
    }
    else
    {
        Log.errorln("Invalid command");
        String invalid[]{"Invalid"};
        return command_factory.BuildCommand(invalid, 1);
    }
}