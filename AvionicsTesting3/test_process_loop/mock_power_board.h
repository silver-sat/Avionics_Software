/**
 * @file mock_power_board.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test the Avionics Board mock Power Board
 * @version 1.0.1
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
     * @brief Initialize the Power Board
     * 
     * @return true successful
     * @return false error
     */
    bool begin();

    /**
     * @brief Get power status
     *
     * @return String letter grade for beacon
     */

    String get_power_status();

    /**
     * @brief Get the power detail
     *
     * @return String power details
     */
    String get_power_detail();

private:
    PowerStatus _power_status{fair};
};

#endif