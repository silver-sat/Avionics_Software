/**
 * @file Beacon.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat beacon messages
 * @version 2.1.0
 * @date 2022-07-25
 *
 * This file implements the Beacon class, which inherits from Message. Beacons are sent
 * at intervals and includes status for the Power, Avionics, and Payload boards.
 *
 * Beacon timing relies on a microcontroller timer. The realtime clock is not used for beacon timing.
 *
 * The Radio Board provides its own status and adds it to the beacon prior to transmission.
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
     * @brief Power Board Status
     *
     */

    enum class PowerStatus
    {
        excellent,
        fair,
        unknown,
    };

    /**
     * @brief Avionics Board Status
     *
     */

    enum class AvionicsStatus
    {
        everything_ok,
        unknown_time,
        FRAM_initialization_error,
        antenna_deployment_error,
        imu_initialization_error,
        radio_connection_error,
        unstable,
        rtc_initialization_error,
        power_board_initialization_error,
        watchdog_reset,
        unknown,
    };

    /**
     * @brief Payload Board Status
     *
     */

    enum class PayloadStatus
    {
        unknown,
    };

    /**
     * @brief Construct a new Beacon::Beacon object
     *
     * @param power Power Board status
     * @param avionics Avionics Board status
     * @param payload Payload Board status
     */

    Beacon(
        const PowerStatus powerStatus,
        const AvionicsStatus avionicsStatus,
        const PayloadStatus payloadStatus)
    {

        m_command = beacon;
        m_content = " " +
                    convertPowerStatus(powerStatus) +
                    convertAvionicsStatus(avionicsStatus) +
                    convertPayloadStatus(payloadStatus);
    }

private:

    const String convertPowerStatus(PowerStatus powerStatus)
    {
        switch (powerStatus)
        {
        // todo: update to reflect power team selections
        case PowerStatus::excellent:
            return "E";
        case PowerStatus::fair:
            return "F";
        case PowerStatus::unknown:
            return "U";
        default:
            return "U";
        }
    }

    const String convertAvionicsStatus(const AvionicsStatus avionicsStatus)
    {
        switch (avionicsStatus)
        {
        case AvionicsStatus::everything_ok:
            return "A";
        case AvionicsStatus::unknown_time:
            return "B";
        case AvionicsStatus::FRAM_initialization_error:
            return "C";
        case AvionicsStatus::antenna_deployment_error:
            return "D";
        case AvionicsStatus::imu_initialization_error:
            return "E";
        case AvionicsStatus::radio_connection_error:
            return "F";
        case AvionicsStatus::unstable:
            return "G";
        case AvionicsStatus::rtc_initialization_error:
            return "H";
        case AvionicsStatus::power_board_initialization_error:
            return "I";
        case AvionicsStatus::watchdog_reset:
            return "J";
        case AvionicsStatus::unknown:
            return "U";
        default:
            return "U";
        }
    }

    const String convertPayloadStatus(PayloadStatus payloadStatus)
    {
        switch (payloadStatus)
        {
        // todo: update to reflect payload team selections
        case PayloadStatus::unknown:
            return "U";
        default:
            return "U";
        }
    }
};