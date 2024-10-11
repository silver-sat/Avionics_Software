/**
 * @file AvionicsBoard.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Avionics Board for SilverSat
 * @version 1.0.4
 * @date 2022-07-29
 *
 * This file declares the class which encapsulates the functions of the Avionics Board
 * hardware.
 */

#pragma once

#include "avionics_constants.h"
#include "ExternalWatchdog.h"
#include "ExternalRTC.h"
#include "IMU.h"
#include "Beacon.h"
#include "CY15B256J.h"
#include "PayloadQueue.h"
#include <Wire.h>
#include <wiring_private.h>

/**
 * @brief Avionics Board constants
 *
 */

constexpr uint16_t minimum_beacon_interval{1 * minutes_to_seconds};  /**< minimum beacon interval */
constexpr uint16_t maximum_beacon_interval{10 * minutes_to_seconds}; /**< maximum beacon interval */
constexpr uint16_t minimum_valid_year{2024};                         /**< minimum valid year */
constexpr uint16_t maximum_valid_year{2030};                         /**< maximum valid year */

/**
 * @brief Avionics Board class for managing the microcontroller and peripherals
 *
 */

class AvionicsBoard final
{
public:
   bool begin();
   void watchdog_force_reset();
   bool set_external_rtc(const DateTime time);
   String get_timestamp();
   bool set_beacon_interval(const int seconds);
   bool check_beacon();
   AvionicsBeacon get_status();
   bool set_picture_time(const DateTime time);
   bool set_SSDV_time(const DateTime time);
   bool check_payload();
   bool clear_payload_queue();
   size_t get_payload_queue_size();
   String get_telemetry();
   String get_beacon_interval();
   void service_watchdog();
   String read_fram(const size_t address);
   bool unset_clock();
   bool get_stability();

friend class CommandGetPayloadQueue;

private:
   bool busswitch_enable();
   bool valid_time(const DateTime time);
   ExternalWatchdog m_external_watchdog {};
   ExternalRTC m_external_rtc{};
   IMU m_imu{};
   CY15B256J m_fram{};
   unsigned long m_last_beacon_time{0};
   unsigned long m_beacon_interval{2 * minutes_to_seconds * seconds_to_milliseconds};
   bool m_rtc_initialization_error{false};
   bool m_imu_initialization_error{false};
   bool m_FRAM_initialization_error{false};
   bool m_radio_connection_error{false};
   PayloadQueue m_payload_queue{};
};
