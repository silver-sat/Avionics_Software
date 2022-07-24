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

struct beacon
{
    byte content[256];
};

/**
 * @brief Get command
 *
 */

MockRadioBoard::command MockRadioBoard::get_command(){};

/**
 * @brief Send beacon
 *
 */

void MockRadioBoard::send_beacon(MockRadioBoard::beacon){};