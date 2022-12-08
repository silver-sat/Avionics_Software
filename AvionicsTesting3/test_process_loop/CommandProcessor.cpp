/**
 * @file CommandProcessor.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Manage command processing
 * @version 1.0.0
 * @date 2022-12-07
 *
 *
 */

#include "CommandProcessor.h"
#include "log_utility.h"
#include "mock_radio_board.h"

/**
 * @brief Check for command
 *
 * @return true no command or successful
 * @return false error
 */

bool CommandProcessor::check_for_command()
{
    extern MockRadioBoard radio;
    if (radio.receive_command(m_command_buffer, maximum_command_length))
    {
        String command_string{m_command_buffer};
        Command* command{make_command(command_string)};
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
            Log.errorln("Failed (%l executed, %l failed, next sequence %i)", m_successful_commands, ++m_failed_commands, m_command_sequence);
            delete command;
            return false;
        };
    };
    return true;
};

/**
 * @brief Make command object
 *
 * @param buffer 
 * @param command Command object
 * @return next command to process
 *
 */

Command* CommandProcessor::make_command(String buffer)
{

    // validate signature

    String command_string;
    command_parser.validate_signature(buffer, command_string, m_validation_required, m_command_sequence);

    // tokenize the command string and create the command object

    String command_tokens[command_parameter_limit]{};
    size_t token_count{0};
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
};