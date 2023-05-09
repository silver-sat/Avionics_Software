/**
 * @file PowerBoard.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat Power Board
 * @version 2.0.0
 * @date 2022-07-24
 *
 * This file declares the class that interfaces to the Power Board
 *
 */

#pragma once

#include "EPS_I.h"
#include "Beacon.h"
#include <Arduino.h>

/**
 * @brief SilverSat Power Board Interface
 *
 */

class PowerBoard final
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
     * @brief Get power status for beacon
     *
     */

    Beacon::PowerStatus get_status();

    /**
     * @brief Get the power detail for command response
     *
     */
    String get_detail();

private:
    EPS_I m_eps_i{}; /**< Power Board */
    // beacon data
    bool m_initialization_error{false};                               /**< Initialization error */
};