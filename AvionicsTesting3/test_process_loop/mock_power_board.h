/**
 * @file mock_power_board.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test the Avionics Board mock Power Board
 * @version 1.0.0
 * @date 2022-07-24
 *
 *
 */

#ifndef MOCK_POWER_BOARD_H
#define MOCK_POWER_BOARD_H

#include <Arduino.h>

class MockPowerBoard
{
public:
    MockPowerBoard();

    enum PowerStatus
    {
        excellent,
        good,
        fair,
        poor,
        critical,
        unknown,
    };

    /**
     * @brief Get power status
     *
     */

    String get_power_status();

private:
    PowerStatus _power_status{fair};
};

#endif