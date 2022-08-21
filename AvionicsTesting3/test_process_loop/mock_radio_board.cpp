/**
 * @file mock_radio_board.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Mock Radio Board for Avionics testing
 * @version 1.1.0
 * @date 2022-07-24
 *
 *
 */

#include "mock_radio_board.h"
#include "log_utility.h"

/**
 * @brief Construct a new Mock Radio Board:: Mock Radio Board object
 *
 */

MockRadioBoard::MockRadioBoard(){};

/**
 * @brief Mock Radio Board Destructor
 *
 */

MockRadioBoard::~MockRadioBoard()
{
    // Free storage for command
    if (_factory)
    {
        delete _factory;
        _factory = NULL;
    }
};

/**
 * @brief initialize the Radio Board
 *
 * @return true successful
 * @return false error
 */

bool MockRadioBoard::begin()
{
    Log.traceln("Radio Board initializing");
    return true;
};

/**
 * @brief Notify radio board to deploy antenna
 *
 * @return true successful
 * @return false error
 */

bool MockRadioBoard::deploy_antenna()
{
    auto message = Message(Message::local_command, "DeployAntenna");
    return send_message(message);
};

/**
 * @brief Process commands
 *
 * @return true no command or successful
 * @return false error
 */

bool MockRadioBoard::check_command()
{
    if (command_received())
    {
        Log.verboseln("Command code: %d", _command->get_operation());
        _command->acknowledge_command();
        Log.traceln("Command acknowledged");
        if (_command->execute_command())
        {
            Log.traceln("Command executed");
            return true;
        }
        else
        {
            Log.errorln("Command failed");
            return false;
        };
    };
    return true;
};

/**
 * @brief Check for command
 *
 * @return true command available
 * @return false no command available
 */

bool MockRadioBoard::command_received()
{
    while (Serial.available())
    {
        char character = Serial.read();
        if (character == '\n')
        {
            _end_of_line = true;
            break;
        }
        else
        {
            _buffer += character;
        }
    };

    if (_end_of_line)
    {
        Log.verboseln("Remote command received: %s", _buffer.c_str());
        make_command(_buffer);
        _buffer = "";
        _end_of_line = false;
        return true;
    };

    return false;
};

/**
 * @brief Make command object
 *
 * @return next command to process
 *
 */

bool MockRadioBoard::make_command(String buffer)
{
    Log.traceln("Constructing new command");

    // destroy the last factory

    if (_factory)
    {
        delete _factory;
        _factory = NULL;
    }

    // trim and tokenize the buffer

    _buffer.trim();
    String tokens[_token_limit]{};
    size_t token_index{0};
    for (auto buffer_index = 0; buffer_index < _buffer.length(); buffer_index++)
    {
        if (_buffer.charAt(buffer_index) != ' ')
        {
            tokens[token_index] += _buffer.charAt(buffer_index);
        }
        else
        {
            token_index++;
            if (token_index > _token_limit)
            {
                Log.warningln("Too many command parameters");
                break;
            }
        }
    }

    // Return the new command

    _command = (new CommandFactory(tokens, token_index))->get_command();

    return true;
};

/**
 * @brief Send beacon
 *
 * @return true successful
 * @return false error
 */

void MockRadioBoard::send_beacon(Beacon beacon)
{
    Log.noticeln("Transmitting beacon %s %s", _call_sign.c_str(), beacon.get_message().c_str());
};

/**
 * @brief Send message
 *
 * @return true successful
 * @return false error
 */

bool MockRadioBoard::send_message(Message message)
{
    Log.noticeln("Sending message: %s", message.get_message().c_str());
    return true;
};
