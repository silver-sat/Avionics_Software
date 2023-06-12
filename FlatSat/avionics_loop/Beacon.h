/**
 * @file Beacon.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat beacon messages
 * @version 2.1.1
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

/**
 * @brief Power Board Beacon
 *
 * see https://docs.google.com/spreadsheets/d/19ibkPfePBUwRdCt-2vd_L55o1tiCnPxzvAepbnGq8PU/edit?usp=sharing
 * 
 */

enum class PowerBeacon
{
    excellent,
    good,
    fair,
    poor,
    unknown,
};

/**
 * @brief Avionics Board Beacon
 *
 * see: https://docs.google.com/document/d/1TTygPny-VP51_k1m2dgPnB5O26MzPzFeGfu8ND0MskU/edit?usp=sharing
 * 
 */

enum class AvionicsBeacon
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
 * @brief Payload Board Beacon
 *
 * see https://docs.google.com/document/d/1y_QmltteIbUQHrYqqVDfCnWsfpcF2DDvKiVARtVozjs/edit?usp=sharing
 *
 */

enum class PayloadBeacon
{
    communicate_0_2,
    communicate_2_4,
    communicate_4_6,
    communicate_6_8,
    communicate_8_10,
    communicate_timeout,
    photo_0_2,
    photo_2_4,
    photo_4_6,
    photo_6_8,
    photo_8_10,
    photo_timeout,
    overcurrent_0_2,
    overcurrent_2_4,
    overcurrent_4_6,
    overcurrent_6_8,
    overcurrent_8_10,
    none,
    unknown,
};

/**
 * @brief Beacon message
 *
 */

class Beacon final : public Message
{
public:
    /**
     * @brief Construct a new Beacon::Beacon object
     *
     * @param power Power Board status
     * @param avionics Avionics Board status
     * @param payload Payload Board status
     */

    Beacon(const PowerBeacon power_beacon, const AvionicsBeacon avionics_beacon, const PayloadBeacon payload_beacon)
        : Message{beacon, " " + convert_power_beacon(power_beacon) + convert_avionics_status(avionics_beacon) + convert_payload_status(payload_beacon)}
    {
    }

private:
    const String convert_power_beacon(const PowerBeacon power_beacon)
    {
        switch (power_beacon)
        {
        case PowerBeacon::excellent:
            return "S";
        case PowerBeacon::good:
            return "E";
        case PowerBeacon::fair:
            return "I";
        case PowerBeacon::poor:
            return "T";
        case PowerBeacon::unknown:
            return "A";
        default:
            return "A";
        }
    }

    const String convert_avionics_status(const AvionicsBeacon avionics_beacon)
    {
        switch (avionics_beacon)
        {
        case AvionicsBeacon::everything_ok:
            return "A";
        case AvionicsBeacon::unknown_time:
            return "B";
        case AvionicsBeacon::FRAM_initialization_error:
            return "C";
        case AvionicsBeacon::antenna_deployment_error:
            return "D";
        case AvionicsBeacon::imu_initialization_error:
            return "E";
        case AvionicsBeacon::radio_connection_error:
            return "F";
        case AvionicsBeacon::unstable:
            return "G";
        case AvionicsBeacon::rtc_initialization_error:
            return "H";
        case AvionicsBeacon::power_board_initialization_error:
            return "I";
        case AvionicsBeacon::watchdog_reset:
            return "J";
        case AvionicsBeacon::unknown:
            return "U";
        default:
            return "U";
        }
    }

    const String convert_payload_status(PayloadBeacon payload_beacon)
    {
        switch (payload_beacon)
        {
        case PayloadBeacon::communicate_0_2:
            return "S";
        case PayloadBeacon::communicate_2_4:
            return "U";
        case PayloadBeacon::communicate_4_6:
            return "A";
        case PayloadBeacon::communicate_6_8:
            return "H";
        case PayloadBeacon::communicate_8_10:
            return "5";
        case PayloadBeacon::communicate_timeout:
            return "B";
        case PayloadBeacon::photo_0_2:
            return "N";
        case PayloadBeacon::photo_2_4:
            return "T";
        case PayloadBeacon::photo_4_6:
            return "I";
        case PayloadBeacon::photo_6_8:
            return "D";
        case PayloadBeacon::photo_8_10:
            return "R";
        case PayloadBeacon::photo_timeout:
            return "F";
        case PayloadBeacon::overcurrent_0_2:
            return "L";
        case PayloadBeacon::overcurrent_2_4:
            return "M";
        case PayloadBeacon::overcurrent_4_6:
            return "V";
        case PayloadBeacon::overcurrent_6_8:
            return "G";
        case PayloadBeacon::overcurrent_8_10:
            return "K";
        case PayloadBeacon::none:
            return "E";
        case PayloadBeacon::unknown:
            return "X";
        default:
            return "X";
        }
    }
};