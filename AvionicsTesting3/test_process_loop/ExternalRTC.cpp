/**
 * @file ExternalRTC.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief External Realtime Clock
 * @version 1.0.1
 * @date 2022-08-11
 *
 *
 */

#include "ExternalRTC.h"
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
 */

bool ExternalRTC::begin(TwoWire *theWire)
{
    // todo: restore external realtime clock
    // Log.verboseln("Starting external realtime clock");
    // if (!m_rtc.begin(theWire))
    // {
    //     return false;
    // };
    // if (!m_rtc.initialized() || m_rtc.lostPower())
    // {
    //     m_rtc_is_set = false;
    //     Log.verboseln("Realtime clock is not set");
    // }
    // else
    // {
    //     m_rtc_is_set = true;
    //     Log.verboseln("Realtime clock is set");
    // }
    // m_rtc.start();
    Log.verboseln("Realtime clock is running");
    return true;
};

/**
 * @brief Set the external realtime clock
 *
 * @param time
 * @return true successful
 * @return false error
 */

bool ExternalRTC::set_time(DateTime time)
{
    if (time.isValid())
    {
        m_rtc.adjust(time);
        // todo: restore external realtime clock
        // m_rtc.start();
        m_rtc_is_set = true;
        return true;
    }
    else
    {
        // todo: reconcile invalidate time from RTC and invalid range in Avionics Board
        Log.errorln("Invalid time");
        return false;
    }
};

/**
 * @brief Get the current external realtime clock time
 *
 * @return * DateTime current time
 */

DateTime ExternalRTC::get_time()
{
    // todo: sanity check on RTC value
    return m_rtc.now();
};

/**
 * @brief Get a timestamp
 * 
 * @return String timestamp
 */

String ExternalRTC::get_timestamp()
{
    if (m_rtc_is_set)
    {

        return m_rtc.now().timestamp();
    }
    else
    {
        Log.errorln("External realtime clock not set");
        return "ERROR";
    }
};

/**
 * @brief Unset the realtime clock
 * 
 * @return true successful
 * @return false error
 */

// todo: for testing only, remove from flight software

bool ExternalRTC::unset_clock()
{
    m_rtc_is_set = false;
    return true;
};

/**
 * @brief Get status of realtime clock
 * 
 * @return true 
 * @return false 
 */
bool ExternalRTC::is_set()
{
    return m_rtc_is_set;
};
