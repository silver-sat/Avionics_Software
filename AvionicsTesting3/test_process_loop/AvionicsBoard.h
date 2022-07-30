/**
 * @file AvionicsBoard.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test Avionics Board for SilverSat
 * @version 1.0.0
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
     * @brief Set the external realtime clock
     *
     * @param date_time
     * @return true successful
     * @return false error
     */

    bool set_external_rtc(DateTime);
    
    /**
     * @brief Return external realtime clock status
     *
     * @return true clock is set
     * @return false clock is not set
     */

    bool get_external_rtc_is_set();
    
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
    
    bool beacon();

private:
    RTC_PCF8523 _external_rtc{};
    bool _external_rtc_is_set{false};
    unsigned long _beacon_interval{2 * 60 * 1000 * 1000}; // 2 minutes
    unsigned long _last_beacon_time{0};
};

#endif