/**
 * @file AvionicsBoard.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test Avionics Board for SilverSat
 * @version 1.0.1
 * @date 2022-07-29
 *
 *
 */

#include "AvionicsBoard.h"
#include "log_utility.h"
#include "beacon.h"
#include "mock_radio_board.h"
#include "mock_payload_board.h"

/**
 * @brief Construct a new Avionics Board:: Avionics Board object
 *
 */

AvionicsBoard::AvionicsBoard(){

    /**
     * @brief Create interface objects
     *
     */

    // RTC_PCF8523 rtc;
    // _external_rtc = rtc;
    // Watchdog watchdog;
    // _watchdog = watchdog;
    // IMU imu{};
    // FRAM fram{};
    // BusSwitch bus_switch;
    // Create serial buffer as serial_buffer;
};

/**
 * @brief Initialize the Avionics Board
 *
 * @return true successful
 * @return false error
 */

bool AvionicsBoard::begin()
{
    // Critical I2C
    // Disable I2C non crit links
    // busswitch.disable();
    // pinMode(EN_EXT_I2C, OUTPUT);
    // digitalWrite(EN_EXT_I2C, LOW);

    // Disconnect from the Payload serial port
    // serial_buffer.disable(payload);

    // Connect to the Radio Board serial port
    // serial_buffer.enable(radio);

    // Enable external realtime clock

    Log.traceln("Initializing external realtime clock");
    // todo: replace with Avionics Board external realtime clock
    _external_rtc.begin();
    Log.traceln("External realtime clock initialized");

    // Initialize connection to IMU
    // imu.begin();

    // Initialize connection to FRAM

    return true;
};

/**
 * @brief Trigger the watchdog
 *
 * @return true successful
 * @return false error
 */

bool AvionicsBoard::trigger_watchdog()
{
    _watchdog.trigger();
    return true;
};

/**
 * @brief Force the watchdog to reset the processor
 *
 * @return true successful
 * @return false error
 */

bool AvionicsBoard::watchdog_force_reset()
{
    Log.fatalln("Forcing watchdog reset");
    return _watchdog.set_force_reset();
};

/**
 * @brief Set the external realtime clock
 *
 * @param time
 * @return true successful
 * @return false error
 */

bool AvionicsBoard::set_external_rtc(DateTime time)
{
    _external_rtc.adjust(time);
    _external_rtc.start();
    _external_rtc_is_set = true;
    return true;
};

/**
 * @brief Return external realtime clock year
 *
 * @return int year
 */

int AvionicsBoard::get_year()
{
    if (_external_rtc_is_set)
    {

        return _external_rtc.now().year();
    }
    else
    {
        Log.error("get_year: external realtime clock not set");
        return _future_invalid_date.year();
    }
};

/**
 * @brief Return external realtime clock month
 *
 * @return int month
 */

int AvionicsBoard::get_month()
{
    if (_external_rtc_is_set)
    {

        return _external_rtc.now().month();
    }
    else
    {
        Log.error("get_month: external realtime clock not set");
        return _future_invalid_date.month();
    }
};

/**
 * @brief Return external realtime clock day
 *
 * @return int day
 */

int AvionicsBoard::get_day()
{
    if (_external_rtc_is_set)
    {

        return _external_rtc.now().day();
    }
    else
    {
        Log.error("get_day: external realtime clock not set");
        return _future_invalid_date.day();
    }
};

/**
 * @brief Return external realtime clock hour
 *
 * @return int hour
 */

int AvionicsBoard::get_hour()
{
    if (_external_rtc_is_set)
    {

        return _external_rtc.now().hour();
    }
    else
    {
        Log.error("get_hour: external realtime clock not set");
        return _future_invalid_date.hour();
    }
};

/**
 * @brief Return external realtime clock minute
 *
 * @return int minute
 */

int AvionicsBoard::get_minute()
{
    if (_external_rtc_is_set)
    {

        return _external_rtc.now().minute();
    }
    else
    {
        Log.error("get_minute: external realtime clock not set");
        return _future_invalid_date.minute();
    }
};

/**
 * @brief Return external realtime clock second
 *
 * @return int second
 */

int AvionicsBoard::get_second()
{
    if (_external_rtc_is_set)
    {

        return _external_rtc.now().second();
    }
    else
    {
        Log.error("get_second: external realtime clock not set");
        return _future_invalid_date.second();
    }
};

String AvionicsBoard::get_timestamp()
{
    if (_external_rtc_is_set)
    {

        return _external_rtc.now().timestamp();
    }
    else
    {
        Log.error("get_timestamp: external realtime clock not set");
        return _future_invalid_date.timestamp();
    }

    return _external_rtc.now().timestamp();
};

/**
 * @brief Set beacon interval
 *
 * @param seconds
 * @return true successful
 * @return false error
 */

bool AvionicsBoard::set_beacon_interval(int seconds)
{
    _beacon_interval = seconds * 1000 * 1000;
    return true;
};

/**
 * @brief Send a beacon if the beacon interval has elapsed
 *
 * @return true successful
 * @return false error
 */

bool AvionicsBoard::check_beacon()
{
    if (micros() - _last_beacon_time > _beacon_interval)
    {
        // todo: get power statusu
        // todo: get payload status
        // todo: format beacon message
        Beacon message{Beacon::excellent, Beacon::good, Beacon::fair, Beacon::poor, Beacon::critical};
        extern MockRadioBoard radio;
        radio.send_beacon(message);
        _last_beacon_time = micros();
    };
    return true;
};

/**
 * @brief Set the time for the next payload photo
 *
 * @param time time for photo
 * @return true successful
 * @return false error
 */

bool AvionicsBoard::set_picture_time(DateTime time)
{
    _picture_time = time;
    return true;
};

/**
 * @brief Check time for photo and start payload if required
 *
 * @return true successful
 * @return false error
 */

bool AvionicsBoard::check_photo()
{
    if (_external_rtc_is_set && (_external_rtc.now() >= _picture_time))
    {
        Log.traceln("Photo time reached %s", get_timestamp().c_str());
        _picture_time = _future_invalid_date;
        extern MockPayloadBoard payload;
        payload.photo();
    };
    return true;
};

String AvionicsBoard::get_pic_times()
{
    return _picture_time.timestamp();
};
