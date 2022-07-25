/**
 * @file beacon.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat beacon messages
 * @version 1.0.0
 * @date 2022-07-25
 *
 *
 */

#include "beacon.h"

/**
 * @brief convert status to Morse code
 * 
 * @param status 
 * @return String 
 */

String toMorse(Beacon::status status)
{
    switch (status)
    {
    case Beacon::excellent:
        return ".- "; // "A"
    case Beacon::good:
        return "-... "; // "B"
    case Beacon::fair:
        return "-.-. "; // "C"
    case Beacon::poor:
        return "-.. "; // "D"
    case Beacon::critical:
        return "..-. "; // "F"
    case Beacon::unknown:
        return "..--.. "; // "?"
    default:
        return "..--.. "; // "?"
    }
};
/**
 * @brief Construct a new Beacon:: Beacon object
 * 
 * @param avionics status
 * @param payload status
 * @param power status
 * @param radio status
 * @param reserved 
 */
Beacon::Beacon(

    status avionics,
    status payload,
    status power,
    status radio,
    status reserved)
{

    _message = (_call_sign +
                toMorse(avionics) +
                toMorse(payload) +
                toMorse(power) +
                toMorse(radio) +
                toMorse(reserved));
};

/**
 * @brief get the Morse code for the beacon
 * 
 * @return String 
 */
String Beacon::get_code()
{
    return _message;
};