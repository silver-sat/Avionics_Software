/**
 * @file beacon.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat beacon messages
 * @version 1.2.0
 * @date 2022-07-25
 *
 *
 */

#ifndef BEACON_H
#define BEACON_H

#include <Arduino.h>

/**
 * @brief Beacon format sent by the Avionics Board
 * 
 */
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
     * @param power status
     * @param avionics status
     * @param radio status
     * @param payload status
     */

    Beacon(
        status power,
        status avionics,
        status radio,
        status payload);
    
    /**
     * @brief Get the message for the beacon
     *
     * @return String status for each board
     */
    
    String get_message();

private:
    String _message{};
};

#endif // BEACON_H