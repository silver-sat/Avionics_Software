/**
 * @file beacon.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat beacon messages
 * @version 1.0.0
 * @date 2022-07-25
 *
 *
 */

#ifndef BEACON_H
#define BEACON_H

#include <Arduino.h>

class Beacon
{
public:

/**
 * @brief board status
 * 
 */
    enum status
    {
        excellent,
        good,
        fair,
        poor,
        critical,
        unknown,
    };

/**
 * @brief Construct a new Beacon object
 * 
 * @param avionics status
 * @param payload status
 * @param power status
 * @param radio status
 * @param reserved
 */
    Beacon(
        status avionics,
        status payload,
        status power,
        status radio,
        status reserved);

/**
 * @brief Get the Morse code for the beacon
 * 
 * @return String call sign and status for each board
 */
    String get_code();

private:
    // todo: convert call sign to Morse code ('.' '-')
    String _call_sign{"..--.. ..--.. ..--.. ..--.. ..--.. "}; // this is "?????"
    String _message {};
};

#endif