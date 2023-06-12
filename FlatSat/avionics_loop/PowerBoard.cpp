/**
 * @file PowerBoard.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat Power Board
 * @version 2.0.2
 * @date 2022-07-24
 *
 * This file implements the class that interfaces to the Power Board
 *
 */

#include "PowerBoard.h"
#include "log_utility.h"

/**
 * @brief Initialize the Power Board
 *
 * @return true successful
 * @return false error
 *
 */

bool PowerBoard::begin()
{
    Log.traceln("Power Board initializing");
    Log.traceln("Initializing EPS-I");
    if (m_eps_i.begin())
    {
        Log.traceln("EPS-I initialization completed");
        return true;
    }
    else
    {
        Log.errorln("EPS-I not initialized");
        return false;
    }
}

/**
 * @brief Get power status for beacon
 *
 * @return PowerBeacon Power Board status
 */

const PowerBeacon PowerBoard::get_status()
{
    auto battery_voltage{m_eps_i.getBatteryVoltage()};
    if (battery_voltage > 3.8)
    {
        return PowerBeacon::excellent;
    }
    else if (battery_voltage > 3.7)
    {
        return PowerBeacon::good;
    }
    else if (battery_voltage > 3.6)
    {
        return PowerBeacon::fair;
    }
    else
    {
        return PowerBeacon::poor;
    }
}

/**
 * @brief Get the power detail for command response
 *
 * @return String power details
 *
 */

const String PowerBoard::get_detail()
{
    return " BBV " + String(m_eps_i.getBatteryVoltage()) +
           " BBC " + String(m_eps_i.getBatteryCurrent()) +
           " TS1 " + String(m_eps_i.getTemperatureSensor1()) +
           " TS2 " + String(m_eps_i.getTemperatureSensor2()) +
           " 5VC " + String(m_eps_i.get5VCurrent()) +
           " H1S " + String(m_eps_i.getHeater1State()) +
           " H2S " + String(m_eps_i.getHeater2State()) +
           " H3S " + String(m_eps_i.getHeater3State());
}