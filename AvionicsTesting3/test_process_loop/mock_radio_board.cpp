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

/**
 * @brief Construct a new Mock Radio Board:: Mock Radio Board object
 *
 */

MockRadioBoard::MockRadioBoard(){};

/**
 * @brief Free storage for command
 *
 */

MockRadioBoard::~MockRadioBoard()
{
    if (_factory)
    {
        delete _factory;
        _factory = NULL;
    }
};

/**
 * @brief initialize the connection
 *
 */

bool MockRadioBoard::begin()
{

    // Initial set clock command

    auto factory = new CommandFactory("SetClock", {2024, 1, 1, 10, 10, 0});
    _factory = factory;
    _command_ready = true;
    return true;
};

/**
 * @brief Send beacon
 *
 */

void MockRadioBoard::send_beacon(Beacon beacon)
{
    Serial.print(micros());
    Serial.print(" sending beacon: "), Serial.println(beacon.get_code());
};

/**
 * @brief Check for command
 *
 */

bool MockRadioBoard::command_received()
{
    if (_command_ready)
    {
        _command_ready = false;
        return true;
    }
    else
    {
        return false;
    }
};

/**
 * @brief Get command
 *
 */

Command *MockRadioBoard::get_command()
{
    return _factory->get_command();
};
