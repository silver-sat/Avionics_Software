/**
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat External Realtime Clock
 *
 * This file implements the class that interfaces with the external realtime clock
 *
 */

#include "ExternalRTC.h"
#include "avionics_constants.h"
#include "log_utility.h"

/**
 * @brief Construct a new External realtime clock:: External realtime clock object
 *
 */

ExternalRTC::ExternalRTC(){};

/**
 * @brief Initialize the external realtime clock
 *
 * @return true successful
 * @return false error
 *
 */

bool ExternalRTC::begin(TwoWire *theWire)
{
    Log.verboseln("Starting external realtime clock");

    // Wait for realtime clock--not immediately available after processor reset with no power cycle
    unsigned long delayStartTime = millis();
    while ((!m_rtc.begin(theWire)) && ((millis() - delayStartTime) < wait_for_i2c_device))
        ;

    if (!m_rtc.begin(theWire))
    {
        Log.errorln("Error starting realtime clock");
        rtc_startup_error = true;
        return false;
    }
    else
    {
        Log.verboseln("Realtime clock is running");
        return true;
    }
}

/**
 * @brief Set the external realtime clock
 *
 * @param time
 * @return true successful
 * @return false error
 *
 */

bool ExternalRTC::set_time(const DateTime &time)
{
    if (time.isValid())
    {
        m_rtc.adjust(time);
        m_rtc_is_set = true;
        return true;
    }
    else
    {
        Log.errorln("Invalid time in set_time");
        m_rtc_is_set = false;
        return false;
    }
}

/**
 * @brief Get the current external realtime clock time
 *
 * @return * DateTime current time
 * @return true successful
 * @return false otherwise
 *
 */

bool ExternalRTC::get_time(DateTime &time)
{
    if (!m_rtc_is_set)
    {
        Log.errorln("External realtime clock not set");
        return false;
    }
    time = m_rtc.now();
    if (time.isValid())
        return true;
    else
    {
        Log.errorln("Invalid time in get_time");
        m_rtc_is_set = false;
        return false;
    }
}

/**
 * @brief Get a timestamp
 *
 * @return String timestamp
 *
 */

String ExternalRTC::get_timestamp()
{
    if (!m_rtc_is_set)
    {
        Log.errorln("External realtime clock not set");
        return "ERROR";
    }
    DateTime time = m_rtc.now();
    if (time.isValid())
        return m_rtc.now().timestamp();
    else
    {
        Log.errorln("Invalid time in get_timestamp");
        m_rtc_is_set = false;
        return "ERROR";
    }
}

/**
 * @brief Unset the realtime clock
 *
 * @return true successful
 * @return false error
 *
 */


bool ExternalRTC::unset_clock()
{
    m_rtc_is_set = false;
    return true;
}

/**
 * @brief Get status of realtime clock
 *
 * @return true
 * @return false
 *
 */

bool ExternalRTC::is_set() const
{
    return m_rtc_is_set;
}
