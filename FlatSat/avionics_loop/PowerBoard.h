/**
 * @file PowerBoard.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat Power Board
 * @version 2.0.2
 * @date 2022-07-24
 *
 * This file declares the class that interfaces to the Power Board
 *
 */

#pragma once

#include "EPS_I.h"
#include "Beacon.h"

/**
 * @brief SilverSat Power Board Interface
 *
 */

class PowerBoard final
{
public:
    /**
     * @brief Initialize the Power Board
     *
     */
    bool begin();

    /**
     * @brief Get power status for beacon
     *
     */

    const PowerBeacon get_status();

    /**
     * @brief Check for adequate power for payload activity
     *
     * @return true adequate power
     * @return false inadequate power
     */
    bool power_adequate();

    /**
     * @brief Get the power detail for command response
     *
     */
    const String get_detail();

private:
    EPS_I m_eps_i{}; /**< Power Board */
};