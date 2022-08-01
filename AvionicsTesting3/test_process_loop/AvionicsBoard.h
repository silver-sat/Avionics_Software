/**
 * @file AvionicsBoard.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test Avionics Board for SilverSat
 * @version 1.0.1
 * @date 2022-07-29
 *
 *
 */

#ifndef AVIONICSBOARD_H
#define AVIONICSBOARD_H

#include <RTClib.h>

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
     * @brief Return external realtime clock year
     *
     * @return int year
     */

    int get_year();

    /**
     * @brief Return external realtime clock month
     *
     * @return int month
     */

    int get_month();

    /**
     * @brief Return external realtime clock day
     *
     * @return int day
     */

    int get_day();

    /**
     * @brief Return external realtime clock hour
     *
     * @return int hour
     */

    int get_hour();

    /**
     * @brief Return external realtime clock minute
     *
     * @return int minute
     */

    int get_minute();

    /**
     * @brief Return external realtime clock second
     *
     * @return int second
     */

    int get_second();

    /**
     * @brief Get the timestamp
     *
     * @return String timestamp
     */

    String get_timestamp();

    /**
     * @brief Set the external realtime clock
     *
     * @param time new time setting
     * @return true successful
     * @return false error
     */

    bool set_external_rtc(DateTime time);

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

private:
    const DateTime _future_invalid_date = DateTime(2050, 1, 1, 12, 0, 0);
    RTC_PCF8523 _external_rtc{};
    bool _external_rtc_is_set{false};
    unsigned long _beacon_interval{2 * 60 * 1000 * 1000}; // 2 minutes
    unsigned long _last_beacon_time{0};
    DateTime _picture_time{_future_invalid_date};
};

#endif