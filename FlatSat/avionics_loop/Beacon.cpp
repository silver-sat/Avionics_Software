/**
 * @file beacon.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat beacon messages
 * @version 1.3.0
 * @date 2022-07-25
 *
 *
 */

#include "Beacon.h"

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

    m_message = (to_board_code(power) +
                to_board_code(avionics) +
                to_board_code(radio) +
                to_board_code(payload));
};

/**
 * @brief Convert board status to string
 *
 * @param status status of a board
 * @return String status character
 */

String Beacon::to_board_code(status status) const
{
    switch (status)
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
    case on:
        return "1";
    case off:
        return "0";
    case unknown:
        return "U";
    default:
        return "U";
    }
}
/**
 * @brief get the message for the beacon
 *
 * @return String
 */
String Beacon::get_message() const
{
    return m_message;
};