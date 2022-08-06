/**
 * @file beacon.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat beacon messages
 * @version 1.1.0
 * @date 2022-07-25
 *
 *
 */

#include "beacon.h"

/**
 * @brief Convert board status to string
 * 
 * @param status status of a board
 * @return String status character
 */

String to_board_code(Beacon::status status)
{
    switch (status)
    {
    case Beacon::excellent:
        return "A";
    case Beacon::good:
        return "B";
    case Beacon::fair:
        return "C";
    case Beacon::poor:
        return "D";
    case Beacon::critical:
        return "F";
    case Beacon::unknown:
        return "U";
    default:
        return "U";
    }
}

/**
 * @brief Construct a new Beacon:: Beacon object
 *
 * @param avionics status
 * @param payload status
 * @param power status
 */

Beacon::Beacon(
    status avionics,
    status payload,
    status power)
{

    _message = (to_board_code(avionics) +
                to_board_code(payload) +
                to_board_code(power));
};

/**
 * @brief get the message for the beacon
 *
 * @return String
 */
String Beacon::get_message()
{
    return _message;
};