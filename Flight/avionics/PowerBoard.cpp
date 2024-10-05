/**
 * @file PowerBoard.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @author Benjamin S. Cohen (ben@silversat.org)
 * @brief SilverSat Power Board
 * @version 2.0.2
 * @date 2022-07-24
 *
 * This file implements the class that interfaces to the Power Board
 *
 */

#include "PowerBoard.h"
#include "log_utility.h"

// Raw battery voltage cutoffs for beacon character and payload session power

constexpr float battery_excellent{3.8f};
constexpr float battery_good{3.7f};
constexpr float battery_fair{3.6f};
constexpr float payload_session_minimum{3.65f};

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
        m_eps_i.turn_off_3v3_LUP();
        m_eps_i.turn_on_5v_LUP();
        Log.noticeln("EPS-I battery voltage: %F", m_eps_i.getBatteryVoltage());
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

PowerBeacon PowerBoard::get_status()
{
    auto battery_voltage{m_eps_i.getBatteryVoltage()};
    if (battery_voltage > battery_excellent)
    {
        return PowerBeacon::excellent;
    }
    else if (battery_voltage > battery_good)
    {
        return PowerBeacon::good;
    }
    else if (battery_voltage > battery_fair)
    {
        return PowerBeacon::fair;
    }
    else
    {
        return PowerBeacon::poor;
    }
}

/**
 * @brief Check for adequate power for payload activity
 *
 * @return true adequate power
 * @return false inadequate power
 */

bool PowerBoard::power_adequate()
{
    if (m_eps_i.getBatteryVoltage() > payload_session_minimum)
    {
        return true;
    }
    else
    {
        Log.warningln("EPS-I voltage below payload session minimum");
        // todo: restore battery voltage test for flight
        return false;
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
           " L5V " + String(m_eps_i.getLUP_5VVoltage()) +
           " H1S " + String(m_eps_i.getHeater1State()) +
           " H2S " + String(m_eps_i.getHeater2State()) +
           " H3S " + String(m_eps_i.getHeater3State());
}

/**
 * @brief cycles the radio 5v power
 *
 */

bool PowerBoard::cycle_radio_5v()
{
    Log.warningln("Cycling radio 5v");
    return m_eps_i.cycle_5v_bus();
}