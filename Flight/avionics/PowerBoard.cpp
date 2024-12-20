/**
 * @author Lee A. Congdon (lee@silversat.org)
 * @author Benjamin S. Cohen (ben@silversat.org)
 * @brief SilverSat Power Board
 *
 * This file implements the class that interfaces to the Power Board
 *
 */

#include "PowerBoard.h"
#include "log_utility.h"

// Raw battery voltage cutoffs for beacon character and payload session power

constexpr float battery_excellent{4.1f};
constexpr float battery_good{3.9f};
constexpr float battery_fair{3.7f};
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
        Log.traceln("EPS-I initialization completed");
        return true;
    }
    else
    {
        external_power = true;
        Log.errorln("EPS-I not initialized, assuming external power");
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
    auto battery_voltage{m_eps_i.getBatteryVoltage()};
    if ((battery_voltage > payload_session_minimum) || external_power)
    {
        return true;
    }
    Log.warningln("EPS-I voltage below payload session minimum: %FV", battery_voltage);
    return false;
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

/**
 * @brief Test the EPS-I
 *
 * @return true success
 * @return false error
 */

bool PowerBoard::test_EPS()
{
    Log.traceln("Retrieving key EPS-I values");
    auto battery_voltage = m_eps_i.getBatteryVoltage();
    m_eps_i.getBatteryCurrent();
    m_eps_i.getTemperatureSensor1();
    m_eps_i.getTemperatureSensor2();
    m_eps_i.getTemperatureSensor3();
    m_eps_i.getZNegativeCurrent();
    m_eps_i.get5VCurrent();
    m_eps_i.getLUP_5VVoltage();
    m_eps_i.getHeater1State();
    m_eps_i.getHeater2State();
    m_eps_i.getHeater3State();
    Log.traceln("Dumping EPS-I data");
    m_eps_i.dump_data();
    if (battery_voltage >= battery_good)
    {
        Log.noticeln("EPS-I battery voltage is %FV", battery_voltage);
        return true;
    }
    else
    {
        Log.warningln("EPS-I battery voltage is %FV", battery_voltage);
        return false;
    }
    return true;
}
