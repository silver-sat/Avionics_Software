/**
 * @file mock_power_board.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test the Avionics Board mock Power Board
 * @version 1.1.0
 * @date 2022-07-24
 *
 *
 */

#ifndef MOCK_POWER_BOARD_H
#define MOCK_POWER_BOARD_H

#include "EPS_I.h"
#include <Arduino.h>

/**
 * @brief Mock Power Board for testing the Avionics Board
 *
 */

class MockPowerBoard
{
public:
    MockPowerBoard();

    /**
     * @brief Status of the Power Board
     *
     */
    
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
     */
    bool begin();

    /**
     * @brief Get power status
     *
     */

    String get_status();

    /**
     * @brief Get the power detail
     *
     */
    String get_detail();

private:
// todo: consider where power status is gathered and stored
    PowerStatus m_power_status{fair};
    EPS_I eps_i{};
    
};

#endif // MOCK_POWER_BOARD_H