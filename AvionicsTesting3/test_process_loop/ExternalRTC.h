/**
 * @file ExternalRTC.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief External Realtime Clock
 * @version 1.0.0
 * @date 2022-08-11
 * 
 * 
 */

#ifndef EXTERNALRTC_H
#define EXTERNALRTC_H

#include <RTClib.h>

class ExternalRTC{
public:
ExternalRTC();
bool begin();
bool set_time(DateTime time);
DateTime get_time();
int get_year();
int get_month();
int get_day();
int get_hour();
int get_minute();
int get_second();
String get_timestamp();



private:

    RTC_PCF8523 _rtc{};
    bool _rtc_is_set{false};
};

#endif // EXTERNALRTC_H