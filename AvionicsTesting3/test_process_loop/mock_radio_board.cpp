/**
 * @file mock_radio_board.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test the Avionics Board mock Radio Board
 * @version 1.0.0
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
 * @brief Check for command
 *
 */

bool MockRadioBoard::command_received()
{
    if (_is_command)
    {
        _is_command = false;
        return true;
    }
    else
    {
        return _is_command;
    }
};

/**
 * @brief Get command
 *
 */

String MockRadioBoard::get_command()
{
    return _command;
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