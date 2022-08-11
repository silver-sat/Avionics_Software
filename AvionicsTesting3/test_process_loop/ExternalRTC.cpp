/**
 * @file ExternalRTC.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief External Realtime Clock
 * @version 1.0.0
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
    Log.verboseln("Starting external realtime clock");
    if (!_rtc.begin(theWire))
    {
        return false;
    };
    if (!_rtc.initialized() || _rtc.lostPower())
    {
        Log.verboseln("Realtime clock is not set");
    }
    else
    {
        Log.verboseln("Realtime clock is set");
    }
    _rtc.start();
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
    _rtc.adjust(time);
    _rtc.start();
    _rtc_is_set = true;
    return true;
};

/**
 * @brief Return the current external realtime clock time
 *
 * @return * DateTime current time
 */

DateTime ExternalRTC::get_time()
{
    return _rtc.now();
};

/**
 * @brief Return external realtime clock year
 *
 * @return int year
 */

// todo: error reporting when realtime clock is not set

// int ExternalRTC::get_year()
// {
//     if (_rtc_is_set)
//     {

//         return _rtc.now().year();
//     }
//     else
//     {
//         Log.error("get_year: external realtime clock not set");
//         return -1;
//     }
// };

// /**
//  * @brief Return external realtime clock month
//  *
//  * @return int month
//  */

// int ExternalRTC::get_month()
// {
//     if (_rtc_is_set)
//     {

//         return _rtc.now().month();
//     }
//     else
//     {
//         Log.error("get_month: external realtime clock not set");
//         return -1;
//     }
// };

// /**
//  * @brief Return external realtime clock day
//  *
//  * @return int day
//  */

// int ExternalRTC::get_day()
// {
//     if (_rtc_is_set)
//     {

//         return _rtc.now().day();
//     }
//     else
//     {
//         Log.error("get_day: external realtime clock not set");
//         return -1;
//     }
// };

// /**
//  * @brief Return external realtime clock hour
//  *
//  * @return int hour
//  */

// int ExternalRTC::get_hour()
// {
//     if (_rtc_is_set)
//     {

//         return _rtc.now().hour();
//     }
//     else
//     {
//         Log.error("get_hour: external realtime clock not set");
//         return -1;
//     }
// };

// /**
//  * @brief Return external realtime clock minute
//  *
//  * @return int minute
//  */

// int ExternalRTC::get_minute()
// {
//     if (_rtc_is_set)
//     {

//         return _rtc.now().minute();
//     }
//     else
//     {
//         Log.error("get_minute: external realtime clock not set");
//         return -1;
//     }
// };

// /**
//  * @brief Return external realtime clock second
//  *
//  * @return int second
//  */

// int ExternalRTC::get_second()
// {
//     if (_rtc_is_set)
//     {

//         return _rtc.now().second();
//     }
//     else
//     {
//         Log.error("get_second: external realtime clock not set");
//         return -1;
//     }
// };

String ExternalRTC::get_timestamp()
{
    if (_rtc_is_set)
    {

        return _rtc.now().timestamp();
    }
    else
    {
        Log.errorln("External realtime clock not set");
        return "ERROR";
    }
};
