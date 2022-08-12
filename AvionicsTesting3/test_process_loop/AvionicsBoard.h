/**
 * @file AvionicsBoard.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test Avionics Board for SilverSat
 * @version 1.0.2
 * @date 2022-07-29
 *
 *
 */

#ifndef AVIONICSBOARD_H
#define AVIONICSBOARD_H

#include "Watchdog.h"
#include "ExternalRTC.h"
#include "IMU.h"
#include <Wire.h>
#include <wiring_private.h>
#include <Adafruit_FRAM_I2C.h>

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

private:
    /**
     * @brief Initialize I2C bus switch
     *
     */

    bool busswitch_begin();

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
     * @brief Initialize serial buffers
     *
     */

    bool serial_buffer_begin();

    /**
     * @brief Enable serial buffer to Radio Board
     *
     */

    bool serial_buffer_enable();

    /**
     * @brief Disable serial buffer to Radio Board
     *
     */

    bool serial_buffer_disable();

    ExternalRTC _external_rtc{};
    bool _external_rtc_is_set{false};
    Watchdog _watchdog{};
    unsigned long _beacon_interval{2 * 60 * 1000 * 1000}; // 2 minutes
    unsigned long _last_beacon_time{0};
    const DateTime _future_invalid_date = DateTime(2050, 1, 1, 12, 0, 0);
    DateTime _picture_time{_future_invalid_date}; // todo: sorted queue of picture times
    // TwoWire _ncWire{&SERCOM_NON_CRIT, SDA_NON_CRIT, SCL_NON_CRIT};
    IMU _imu{};
    // to consider: refactor FRAM as object
    Adafruit_FRAM_I2C _fram{};
};

#endif // AVIONICSBOARD_H