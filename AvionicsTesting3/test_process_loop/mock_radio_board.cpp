/**
 * @file mock_radio_board.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Mock Radio Board for Avionics testing
 * @version 1.0.1
 * @date 2022-07-24
 *
 *
 */

#include "mock_radio_board.h"
#include "timestamp.h"

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
 * @brief initialize the connection
 *
 */

bool MockRadioBoard::begin()
{
    return true;
};

/**
 * @brief Send beacon
 *
 */

void MockRadioBoard::send_beacon(Beacon beacon)
{
    timestamp();
    Serial.print("Sending beacon: "), Serial.println(beacon.get_code());
};

/**
 * @brief Check for command
 *
 */

bool MockRadioBoard::command_received()
{
    return (micros() - _last_command_time > _command_interval);
};

/**
 * @brief Get command
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
