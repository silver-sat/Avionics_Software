/**
 * @file beacon.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat beacon messages
 * @version 1.2.0
 * @date 2022-07-25
 *
 *
 */

#include "Beacon.h"

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
 * @param power status
 * @param avionics status
 * @param radio status
 * @param payload status
 */

Beacon::Beacon(
    status power,
    status avionics,
    status radio,
    status payload)
{

    _message = (to_board_code(power) +
                to_board_code(avionics) +
                to_board_code(radio) +
                to_board_code(payload));
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