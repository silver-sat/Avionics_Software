/**
 * @file PowerBoard.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat Power Board
 * @version 1.1.0
 * @date 2022-07-24
 *
 *
 */

#pragma once

#include "EPS_I.h"
#include <Arduino.h>

/**
 * @brief SilverSat Power Board Interface
 *
 */

class PowerBoard
{
public:
    PowerBoard();

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