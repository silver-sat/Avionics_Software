/**
 * @file ExternalRTC.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat External Realtime Clock
 * @version 1.0.1
 * @date 2022-08-11
 *
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
    /**
     * @brief Construct a new External realtime clock:: External realtime clock object
     *
     */

    ExternalRTC();

    /**
     * @brief Initialize the external realtime clock
     *
     */

    bool begin(TwoWire *theWire);

    /**
     * @brief Set the external realtime clock
     *
     */

    bool set_time(const DateTime& time);

    /**
     * @brief Get the current external realtime clock time
     *
     */

    bool get_time(DateTime &time);

    /**
     * @brief Get a timestamp
     *
     */

    String get_timestamp();

    /**
     * @brief Unset the realtime clock
     *
     */

    // todo: for testing only, remove from flight softwarebool unset_clock();

    bool unset_clock();

    /**
     * @brief Get status of realtime clock
     *
     */

    bool is_set() const;

private:
    RTC_DS1337 m_rtc{};
    bool m_rtc_is_set{false};
};