/**
 * @file Beacon.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat beacon messages
 * @version 2.0.0
 * @date 2022-07-25
 *
 * This file implements the Beacon class, which inherits from Message. Beacons are sent
 * at intervals and include a call sign and status for the satellite boards. Beacon timing
 * relies on a microcontroller timer.
 *
 */

#pragma once

#include "Message.h"
#include "avionics_constants.h"
#include <Arduino.h>

/**
 * @brief Beacon message
 *
 */
class Beacon final : public Message
{
public:
    /**
     * @brief board status for beacon
     *
     */
    enum class Status
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
     * @brief Construct a new Beacon:: Beacon object
     *
     * @param power status
     * @param avionics status
     * @param radio status
     * @param payload status
     */

    Beacon(
        Status power,
        Status avionics,
        Status radio,
        Status payload)
    {

        m_command = beacon;
        m_content = call_sign +
                    getStatus(power) +
                    getStatus(avionics) +
                    getStatus(radio) +
                    getStatus(payload);
    };

    const String getStatus(Status status)
    {
        switch (status)
        {

        case Status::excellent:
            return "E";
        case Status::good:
            return "G";
        case Status::fair:
            return "F";
        case Status::poor:
            return "P";
        case Status::critical:
            return "C";
        case Status::on:
            return "N";
        case Status::off:
            return "F";
        case Status::unknown:
            return "U";
        default:
            return "I";
        }
    }
};