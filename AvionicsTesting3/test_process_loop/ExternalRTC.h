/**
 * @file ExternalRTC.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief External Realtime Clock
 * @version 1.0.1
 * @date 2022-08-11
 *
 *
 */

#ifndef EXTERNALRTC_H
#define EXTERNALRTC_H

#include <RTClib.h>

class ExternalRTC
{
public:
    ExternalRTC();
    bool begin(TwoWire *theWire);
    bool set_time(DateTime time);
    DateTime get_time();
    String get_timestamp();
    bool unset_clock();
    bool is_set();

private:
    RTC_PCF8523 _rtc{};
    bool _rtc_is_set{false};
};

#endif // EXTERNALRTC_H