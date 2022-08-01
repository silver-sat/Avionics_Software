/**
 * @file mock_radio_board.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Mock Radio Board for Avionics testing
 * @version 1.0.2
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
 * @brief Free storage for command
 *
 */

MockRadioBoard::~MockRadioBoard(){
    // if (_factory)
    // {
    //     delete _factory;
    //     _factory = NULL;
    // }
};

/**
 * @brief initialize the Radio Board
 *
 * @return true successful
 * @return false error
 */

bool MockRadioBoard::begin()
{
    Log.verboseln("Radio initialized");
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
    Log.noticeln("Transmitting beacon %s", beacon.get_code().c_str());
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
        auto command = get_command();
        Log.traceln("Command received: %d", command->get_operation());
        command->acknowledge_command();
        Log.traceln("Command acknowledged");
        if (command->execute_command())
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
 * @brief Send message
 *
 * @return true successful
 * @return false error
 */

bool MockRadioBoard::send_message(Message message)
{
    Log.noticeln("Sending message %s", message.get_message().c_str());
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
    return (micros() - _last_command_time > _command_interval);
};

/**
 * @brief Get command
 *
 * @return next command to process
 *
 */

Command *MockRadioBoard::get_command()
{
    _last_command_time = micros();

    // auto factory = new CommandFactory("SetClock", {2023, 1, 1, 10, 10, 0});
    // _command1 = factory->get_command();
    // _command2 = &sc2;
    // auto factory = new CommandFactory("BeaconSp", 10);
    // _factory = factory;
    // _command_ready = true;
    // return true;

    return _command_queue[_command_index++ % COMMAND_QUEUE_SIZE];
};
