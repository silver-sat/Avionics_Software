/**
 * @file beacon.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat beacon messages
 * @version 1.3.0
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
        on,
        off,
        unknown,
    };

    /**
     * @brief Construct a new Beacon object
     *
     */

    Beacon(
        status power,
        status avionics,
        status radio,
        status payload);

    /**
     * @brief Convert board status to string
     *
     */

    String to_board_code(Beacon::status status);

    /**
     * @brief Get the message for the beacon
     *
     */

    String get_message();

private:
    String m_message{};
};

#endif // BEACON_H