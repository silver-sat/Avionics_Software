/**
 * @file AvionicsBoard.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Avionics Board for SilverSat
 * @version 1.0.4
 * @date 2022-07-29
 *
 *
 */

#pragma once

#include "board_configuration.h"
#include "ExternalWatchdog.h"
#include "ExternalRTC.h"
#include "IMU.h"
#include "Beacon.h"
#include "CY15B256J.h"
#include <Wire.h>
#include <wiring_private.h>

/**
 * @brief Avionics Board constants
 *
 */
constexpr uint16_t minimum_beacon_interval{ 1 * minutes_to_seconds };  /**< Restrict to a reasonable value */
constexpr uint16_t maximum_beacon_interval{ 10 * minutes_to_seconds }; /**< Restrict to a reasonable value */
constexpr size_t maximum_scheduled_pictures{ 5 };                      /**< Assume small number of pictures in one orbit */
constexpr uint16_t minimum_valid_year{ 2020 };                         /**< Restrict to reasonable value */
constexpr uint16_t maximum_valid_year{ 2040 };                         /**< Restrict to reasonable value */

/**
 * @brief Avionics Board for testing the microcontroller and peripherals
 *
 */
class AvionicsBoard {
public:

  /**
     * @brief Initialize the Avionics Board
     *
     */

  bool begin();

  /**
     * @brief Force the watchdog to reset the processor
     *
     */

  void watchdog_force_reset();

  /**
     * @brief Set the external realtime clock
     *
     */

  bool set_external_rtc(DateTime time);

  /**
     * @brief Get a timestamp
     *
     */

  String get_timestamp();

  /**
     * @brief Set beacon interval
     *
     */

  // todo: consider using TimeSpan
  bool set_beacon_interval(int seconds);

  /**
     * @brief Send a beacon if the beacon interval has elapsed
     *
     */

  bool check_beacon();

  /**
     * @brief Set the time for the next payload photo
     *
     */

  bool set_picture_time(DateTime time);

  /**
     * @brief Check time for photo and start payload if required
     *
     */

  bool check_photo();

  /**
     * @brief Get scheduled picture times
     *
     */

  String get_pic_times();

  /**
     * @brief Clear picture times
     *
     */

  bool clear_pic_times();

  /**
     * @brief Get telemetry
     *
     */

  String get_telemetry();

  /**
     * @brief Get the beacon interval
     *
     */

  String get_beacon_interval();

  /**
     * @brief Trigger the watchdog
     *
     */
  void trigger_watchdog();

  /**
     * @brief Read a byte from the FRAM
     *
     */

  String read_fram(size_t address);

  /**
     * @brief Unset the realtime clock
     *
     */

  bool unset_clock();

  /**
     * @brief Enable I2C bus switch
     *
     */

  bool busswitch_enable();

  /**
     * @brief Disable I2C bus switch
     *
     */

  bool busswitch_disable();

  /**
     * @brief Initialize I2C bus switch
     *
     */

  bool busswitch_begin();

private:
  /**
     * @brief Avionics Board member variables
     *
     */

  ExternalWatchdog m_external_watchdog{};                                              /**< Watchdog */
  unsigned long m_beacon_interval{ 2 * minutes_to_seconds * seconds_to_milliseconds }; /**< Beacon interval */
  unsigned long m_last_beacon_time{ 0 };                                               /**< Last beacon time */
  Beacon::status m_power_status{ Beacon::status::unknown };                            /**< Power Board status */
  Beacon::status m_avionics_status{ Beacon::status::excellent };                       /**< Avionics Board status */
  Beacon::status m_radio_status{ Beacon::status::unknown };                            /**< Radio Board status */
  Beacon::status m_payload_status{ Beacon::status::unknown };                          /**< Payload Board status */
  size_t m_picture_count{ 0 };                                                         /**< Maximum picture count */
  DateTime m_picture_times[maximum_scheduled_pictures]{};                              /**< Scheduled picture times */
  ExternalRTC m_external_rtc{};                                                        /**< External Real Time Clock */
  IMU m_imu{};                                                                         /**< Inertial Measurement Unit */
  CY15B256J m_fram{};                                                                  /**< FRAM */
};