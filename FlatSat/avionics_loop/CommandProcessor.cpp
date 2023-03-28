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
        Log.verboseln("Command source: 0x%x", m_source);
        if (m_source == REMOTE_FRAME)
        {
            Command *command{make_command(command_string)};
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
            Response response{"INV"};
            switch (command_string[0])
            {
            case 'A': // ACK
                Log.verboseln("Received ACK, ignored");
                break;
            case 'N': // NACK
                Log.verboseln("Received NACK, ignored");
                break;
            case 'R': // RESponse
            {
                extern RadioBoard radio;
                auto type{command_string[RES.length()]};
                auto radio_data{command_string.substring(RES.length() + 1)};
                Log.verboseln("Received type: 0x%x, %s", type, radio_data.c_str());
                switch (type)
                {
                case GET_RADIO_STATUS:
                    response = {Response{"GRS" + radio_data}};
                    break;
                case MODIFY_FREQUENCY:
                    response = {Response{"RMF" + radio_data}};
                    break;
                case MODIFY_MODE:
                    response = {Response{"RMM" + radio_data}};
                    break;
                case ADJUST_FREQUENCY:
                    response = {Response{"RAF" + radio_data}};
                    break;
                case TRANSMIT_CW:
                    response = {Response{"RTC" + radio_data}};
                    break;
                case BACKGROUND_RSSI:
                    response = {Response{"RBR" + radio_data}};
                    break;
                case CURRENT_RSSI:
                    response = {Response{"RCR" + radio_data}};
                    break;
                case SWEEP_TRANMSMITTER:
                    response = {Response{"RST" + radio_data}};
                    break;
                case SWEEP_RECEIVER:
                    response = {Response{"RSR" + radio_data}};
                    break;
                case QUERY_REGISTER:
                    response = {Response{"RQR" + radio_data}};
                    break;
                default:
                    Log.errorln("Unknown local command type");
                    response = {Response{"UNK" + radio_data}};
                    break;
                }
                radio.send_message(response);
                break;
            }
            default:
                Log.errorln("Unknown local response type");
                response = (Response{"UNK"});
                radio.send_message(response);
                break;
            }
        }
    };
    return true;
};

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