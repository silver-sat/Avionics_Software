/**
 * @file PowerBoard.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat Power Board
 * @version 2.0.0
 * @date 2022-07-24
 *
 * This file implements the class that interfaces to the Power Board
 *
 */

#include "PowerBoard.h"
#include "log_utility.h"

PowerBoard::PowerBoard(){};

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
    if (eps_i.begin())
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
 * @brief Get power status
 *
 * @return String letter grade for beacon
 */

Beacon::Status PowerBoard::get_status()
{
    // todo: develop and implement battery status beacon character
    if(eps_i.getBatteryVoltage() >= 3.5) {
        return Beacon::Status::excellent;
    } else {
        return Beacon::Status::fair;
    }
}

/**
 * @brief Get the power detail
 *
 * @return String power details
 *
 */

String PowerBoard::get_detail()
{
    return " BBV " + String(eps_i.getBatteryVoltage()) +
        " BBC " + String(eps_i.getBatteryCurrent()) +
        " TS1 " + String(eps_i.getTemperatureSensor1()) +
        " TS2 " + String(eps_i.getTemperatureSensor2()) +
        " 5VC " + String(eps_i.get5VCurrent()) +
        " H1S " + String(eps_i.getHeater1State()) +
        " H2S " + String(eps_i.getHeater2State()) +
        " H3S " + String(eps_i.getHeater3State());
}