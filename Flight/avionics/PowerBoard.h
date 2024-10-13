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
    bool begin();
    PowerBeacon get_status();
    bool power_adequate();
    const String get_detail();
    bool cycle_radio_5v();
    bool test_EPS();
private:
    EPS_I m_eps_i{};
};