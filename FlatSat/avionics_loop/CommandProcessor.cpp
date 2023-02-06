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
#include "Response.h"
#include "RadioBoard.h"

/**
 * @brief Check for command
 *
 * @return true no command or successful
 * @return false error
 */

bool CommandProcessor::check_for_command()
{
    extern RadioBoard radio;
    char source{};
    if (radio.receive_frame(m_command_buffer, maximum_command_length, source))
    {
        String command_string{m_command_buffer};
        Log.verboseln("Command source: 0x%x", source);
        if (source == REMOTE_FRAME)
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
                Log.verboseln("Received: %s, ignored", command_string.c_str());
                break;
            case 'N': // NACK
                Log.verboseln("Received: %s, ignored", command_string.c_str());
                break;
            case 'R': // RESponse
            {
                extern RadioBoard radio;
                // todo: convert local response type to printable data
                Log.verboseln("Received: %s", command_string.c_str());
                auto radio_data{command_string.substring(RES.length())};
                auto type{radio_data[0]};
                switch (type)
                {
                case GET_RADIO_STATUS:
                    // todo: differentiate between local request for beacon and ground request
                    response = {Response{"GRS" + radio_data}};
                    break;
                case MODIFY_FREQUENCY:
                    response = {Response{"RMF" + radio_data}};
                    break;
                case MODIFY_MODE:
                    response = {Response{"RMM" + radio_data}};
                case ADJUST_FREQUENCY:
                    response = {Response{"RAF" + radio_data}};
                case TRANSMIT_CW:
                    response = {Response{"RTC" + radio_data}};
                case BACKGROUND_RSSI:
                    response = {Response{"RBR" + radio_data}};
                case CURRENT_RSSI:
                    response = {Response{"RCR" + radio_data}};
                case SWEEP_TRANMSMITTER:
                    response = {Response{"RST" + radio_data}};
                case SWEEP_RECEIVER:
                    response = {Response{"RSR" + radio_data}};
                case QUERY_REGISTER:
                    response = {Response{"RQR" + radio_data}};
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
 * @param command Command object
 * @return next command to process
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