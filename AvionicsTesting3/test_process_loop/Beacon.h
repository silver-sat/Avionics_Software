/**
 * @file beacon.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat beacon messages
 * @version 1.1.0
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
     */

    Beacon(
        status avionics,
        status payload,
        status power);
    
    /**
     * @brief Get the message for the beacon
     *
     * @return String status for each board
     */
    
    String get_message();

private:
    String _message{};
};

#endif