/**
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat beacon messages
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
 * see https://docs.google.com/spreadsheets/d/1_hdVNVKwpzFvHbcQnjpvcPh6uuIx0EniHY1gVKyH-vw/edit?usp=sharing
 *
 */

enum class PayloadBeacon
{
    none,
    overcurrent_0_1,
    overcurrent_1_2,
    overcurrent_2_4,
    overcurrent_4_6,
    overcurrent_6_8,
    overcurrent_8_10,
    overcurrent_timeout,
    photo_0_1,
    photo_1_2,
    photo_2_4,
    photo_4_6,
    photo_6_8,
    photo_8_10,
    photo_timeout,
    SSDV_0_1,
    SSDV_1_2,
    SSDV_2_4,
    SSDV_4_6,
    SSDV_6_8,
    SSDV_8_10,
    SSDV_timeout,
    communicate_0_1,
    communicate_1_2,
    communicate_2_4,
    communicate_4_6,
    communicate_6_8,
    communicate_8_10,
    communicate_timeout,
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
        : Message{beacon, convert_power_beacon(power_beacon) + convert_avionics_status(avionics_beacon) + convert_payload_status(payload_beacon)}
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
            return "E";
        case AvionicsBeacon::unknown_time:
            return "S";
        case AvionicsBeacon::FRAM_initialization_error:
            return "A";
        case AvionicsBeacon::antenna_deployment_error:
            return "H";
        case AvionicsBeacon::imu_initialization_error:
            return "N";
        case AvionicsBeacon::radio_connection_error:
            return "U";
        case AvionicsBeacon::unstable:
            return "I";
        case AvionicsBeacon::rtc_initialization_error:
            return "D";
        case AvionicsBeacon::power_board_initialization_error:
            return "R";
        case AvionicsBeacon::watchdog_reset:
            return "T";
        case AvionicsBeacon::unknown:
            return "5";
        default:
            return "5";
        }
    }

    const String convert_payload_status(PayloadBeacon payload_beacon)
    {
        switch (payload_beacon)
        {
        case PayloadBeacon::none:
            return "E";
        case PayloadBeacon::overcurrent_0_1:
            return "P";
        case PayloadBeacon::overcurrent_1_2:
            return "X";
        case PayloadBeacon::overcurrent_2_4:
            return "Z";
        case PayloadBeacon::overcurrent_4_6:
            return "O";
        case PayloadBeacon::overcurrent_6_8:
            return "3";
        case PayloadBeacon::overcurrent_8_10:
            return "7";
        case PayloadBeacon::overcurrent_timeout:
            return "J";
        case PayloadBeacon::photo_0_1:
            return "D";
        case PayloadBeacon::photo_1_2:
            return "N";
        case PayloadBeacon::photo_2_4:
            return "I";
        case PayloadBeacon::photo_4_6:
            return "R";
        case PayloadBeacon::photo_6_8:
            return "U";
        case PayloadBeacon::photo_8_10:
            return "B";
        case PayloadBeacon::photo_timeout:
            return "4";
        case PayloadBeacon::SSDV_0_1:
            return "V";
        case PayloadBeacon::SSDV_1_2:
            return "G";
        case PayloadBeacon::SSDV_2_4:
            return "K";
        case PayloadBeacon::SSDV_4_6:
            return "A";
        case PayloadBeacon::SSDV_6_8:
            return "W";
        case PayloadBeacon::SSDV_8_10:
            return "H";
        case PayloadBeacon::SSDV_timeout:
            return "C";
        case PayloadBeacon::communicate_0_1:
            return "S";
        case PayloadBeacon::communicate_1_2:
            return "5";
        case PayloadBeacon::communicate_2_4:
            return "F";
        case PayloadBeacon::communicate_4_6:
            return "L";
        case PayloadBeacon::communicate_6_8:
            return "T";
        case PayloadBeacon::communicate_8_10:
            return "M";
        case PayloadBeacon::communicate_timeout:
            return "6";
        case PayloadBeacon::unknown:
            return "0";

        default:
            return "0";
        }
    }
};