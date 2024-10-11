/**
 * @author Lee A. Congdon (lee@silversat.org)
 * @author Benjamin S. Cohen (ben@silversat.org)
 * @brief SilverSat Power Board
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

    PowerBeacon get_status();

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

    /**
     * @brief cycles the radio 5v power
     *
     */
    bool cycle_radio_5v();

private:
    EPS_I m_eps_i{}; /**< Power Board */
};