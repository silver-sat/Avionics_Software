/**
 * @file Beacon.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat beacon messages
 * @version 2.0.0
 * @date 2022-07-25
 *
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
    enum status
    {
        excellent = 'E',
        good = 'G',
        fair = 'F',
        poor = 'P',
        critical = 'C',
        on = 'N',
        off = 'F',
        unknown = 'U',
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
        status power,
        status avionics,
        status radio,
        status payload)
    {

        m_command = beacon;
        m_content = call_sign +
                         String(power) +
                         String(avionics) +
                         String(radio) +
                         String(payload);
    };
};