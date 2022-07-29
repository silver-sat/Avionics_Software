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
    AvionicsBoard();
    bool begin();
    // todo: replace with Avionics Board external realtime clock
    bool initialize_external_rtc();
    bool set_external_rtc(DateTime);
    bool get_external_rtc_is_set();
    int get_year();
    int get_month();
    int get_day();
    int get_hour();
    int get_minute();
    int get_second();

private:
    RTC_PCF8523 _external_rtc{};
    bool _external_rtc_is_set{false};
};

#endif