/**
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat External Realtime Clock
 *
 * This file declares the class that interfaces with the external realtime clock
 *
 */

#pragma once

#include "DS1337.h"
#include <RTClib.h>

/**
 * @brief External realtime clock for testing the Avionics Board
 *
 */

class ExternalRTC final
{
public:
    ExternalRTC();
    bool begin(TwoWire *theWire);
    bool set_time(const DateTime &time);
    bool get_time(DateTime &time);
    String get_timestamp();
    bool unset_clock();
    bool startup_error() const { return rtc_startup_error; };
    bool is_set() const;

private:
    RTC_DS1337 m_rtc{};
    bool rtc_startup_error{false};
    bool m_rtc_is_set{false};
};