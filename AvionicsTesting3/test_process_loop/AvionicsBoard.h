/**
 * @file AvionicsBoard.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test Avionics Board for SilverSat
 * @version 1.0.4
 * @date 2022-07-29
 *
 *
 */

#ifndef AVIONICSBOARD_H
#define AVIONICSBOARD_H

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
constexpr uint16_t minimum_beacon_interval{1 * minutes_to_seconds};  /**< Restrict to a reasonable value */
constexpr uint16_t maximum_beacon_interval{10 * minutes_to_seconds}; /**< Restrict to a reasonable value */
constexpr size_t maximum_scheduled_pictures{5};                      /**< Assume small number of pictures in one orbit */
constexpr uint16_t minimum_valid_year{2020};                         /**< Restrict to reasonable value */
constexpr uint16_t maximum_valid_year{2040};                         /**< Restrict to reasonable value */

/**
 * @brief Avionics Board for testing the microcontroller and peripherals
 *
 */
class AvionicsBoard
{
public:
    /**
     * @brief Construct a new Avionics Board:: Avionics Board object
     *
     */

    AvionicsBoard();

    /**
     * @brief Initialize the Avionics Board
     *
     * @return true successful
     * @return false error
     */

    bool begin();

    /**
     * @brief Force the watchdog to reset the processor
     *
     * @return true successful
     * @return false error
     */

    bool watchdog_force_reset();

    /**
     * @brief Set the external realtime clock
     *
     * @param time new time setting
     * @return true successful
     * @return false error
     */

    bool set_external_rtc(DateTime time);

    /**
     * @brief Get a timestamp
     *
     * @return String timestamp
     */

    String get_timestamp();

    /**
     * @brief Set beacon interval
     *
     * @param seconds
     * @return true successful
     * @return false error
     */

    bool set_beacon_interval(int seconds);

    /**
     * @brief Send a beacon if the beacon interval has elapsed
     *
     * @return true successful
     * @return false error
     */

    bool check_beacon();

    /**
     * @brief Set the time for the next payload photo
     *
     * @param time time for photo
     * @return true successful
     * @return false error
     */
    bool set_picture_time(DateTime time);

    /**
     * @brief Check time for photo and start payload if required
     *
     * @return true successful
     * @return false error
     */

    bool check_photo();

    /**
     * @brief Get scheduled picture times
     *
     * @return String number of pictures available
     */

    String get_pic_times();

    /**
     * @brief Clear picture times
     *
     * @return true successful
     * @return false error
     */

    bool clear_pic_times();

    /**
     * @brief Get telemetry
     *
     * @return String telemetry data
     */

    String get_telemetry();

    /**
     * @brief Get the beacon interval
     *
     * @return String interval
     */

    String get_beacon_interval();

    /**
     * @brief Trigger the watchdog
     *
     * @return true successful
     * @return false error
     */
    bool trigger_watchdog();

    /**
     * @brief Read a byte from the FRAM
     *
     * @return String byte read
     */

    String read_fram(size_t address);

    /**
     * @brief Unset the realtime clock
     *
     * @return true successful
     * @return false error
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

private:
    /**
     * @brief Initialize I2C bus switch
     *
     */

    bool busswitch_begin();

    /**
     * @brief Avionics Board member variables
     *
     */

    ExternalWatchdog m_external_watchdog{};
    unsigned long m_beacon_interval{2 * minutes_to_seconds * seconds_to_milliseconds};
    unsigned long m_last_beacon_time{0};
    Beacon::status m_power_status{Beacon::status::unknown};
    Beacon::status m_avionics_status{Beacon::status::excellent};
    Beacon::status m_radio_status{Beacon::status::unknown};
    Beacon::status m_payload_status{Beacon::status::unknown};
    size_t m_picture_count{0};
    DateTime m_picture_times[maximum_scheduled_pictures]{};
    ExternalRTC m_external_rtc{};
    IMU m_imu{};
    CY15B256J m_fram{};
};

#endif // AVIONICSBOARD_H