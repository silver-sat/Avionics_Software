/**
 * @file mock_power_board.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test the Avionics Board mock Power Board
 * @version 1.1.0
 * @date 2022-07-24
 *
 *
 */

#include "mock_power_board.h"
#include "log_utility.h"
#include "AvionicsBoard.h"

MockPowerBoard::MockPowerBoard(){};

/**
 * @brief Initialize the Power Board
 *
 * @return true successful
 * @return false error
 */

bool MockPowerBoard::begin()
{
    Log.traceln("Power Board initializing");
    // todo: consider opening I2C bus full time
    // todo: consider getting initial values
    return true;
}

/**
 * @brief Get power status
 *
 * @return String letter grade for beacon
 */

String MockPowerBoard::get_status()
{

    // todo: access power data from Power Board
    extern AvionicsBoard avionics;
    avionics.busswitch_enable();
    switch (m_power_status)
    {
    case excellent:
        return "A";
    case good:
        return "B";
    case fair:
        return "C";
    case poor:
        return "D";
    case critical:
        return "F";
    default:
        return "U";
    };
    avionics.busswitch_disable();
};

/**
 * @brief Get the power detail
 *
 * @return String power details
 */

String MockPowerBoard::get_detail()
{

    // todo: open non-critical I2C bus, access power data from Power Board

    return "VP100.000" // Panel 1 voltage and current
           "CP100.000"
           "VP200.000" // Panel 2 voltage and current
           "CP200.000"
           "VP300.000" // Panel 3 voltage and current
           "CP300.000"
           "VP400.000" // Panel 4 voltage and current
           "CP400.000"
           "VP500.000" // Panel 5 voltage and current
           "CP500.000"
           "VP600.000" // Panel 6 voltage and current
           "CP600.000"
           "TPV00.000" // Total voltage and current (three channels)
           "TPC00.000"
           "O3V00.000" // Output voltage of LUP3.3V and LUP5V
           "O5V00.000"
           "BPV00.000" // Battery pack voltage, current and temperature
           "BPC00.000"
           "BPT00.000"
           "MT100.000" // Main and external temperature sensors
           "MT200.000"
           "MT300.000"
           "MT400.000"
           "ET100.000"
           "ET200.000"
           "ET300.000"
           "CFS00.000" // Critial fail status
           "OS500.000" // On off status for power buses
           "OS300.000"
           "OSR00.000"
           "OSC00.000"
           "IO100.000" // On off status for GPIO
           "IO200.000"
           "IO300.000"
           "IO400.000"
           "IO500.000"
           "IO600.000"
           "CMS00.000" // Charge mode status
           "SLS00.000" // Self lock mode status
           "BHS00.000" // Battery heater status
        ;
};