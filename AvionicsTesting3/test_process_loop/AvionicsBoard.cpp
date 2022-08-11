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
#include "Beacon.h"
#include "mock_radio_board.h"
#include "mock_payload_board.h"

/**
 * @brief Construct a new Avionics Board:: Avionics Board object
 *
 */

AvionicsBoard::AvionicsBoard(){};

/**
 * @brief Initialize the Avionics Board
 *
 * @return true successful
 * @return false error
 */

bool AvionicsBoard::begin()
{
    // Critical I2C

    Log.traceln("Initializing critical I2C bus");
    Wire.begin();
    Log.traceln("Critical I2C bus initialization completed");

    // Non-Critical I2C

    // todo: manage busswitch for non-critical I2C

    Log.traceln("Initializing non-critical I2C bus");
    busswitch_begin();
    busswitch_enable();
    _ncWire.begin();
    pinPeripheral(SDA_NON_CRIT, PIO_SERCOM);
    pinPeripheral(SCL_NON_CRIT, PIO_SERCOM);
    busswitch_disable();
    Log.traceln("Non-critical I2C bus initialization completed");

    // Serial connections

    Log.traceln("Initializing serial buffers");
    serial_buffer_begin();
    Log.traceln("Serial buffer initialization completed");

    // External realtime clock

    Log.traceln("Initializing external realtime clock");

    // todo: replace with Avionics Board external realtime clock

    if (_external_rtc.begin())
    {
        Log.traceln("External realtime clock initialization completed");
    }
    else
    {
        Log.error("External realtime clock not initialized");
    };

    // Inertial Management Unit

    Log.traceln("Initializing inertial management unit");
    busswitch_enable();
    _imu.begin(&_ncWire);
    busswitch_disable();
    Log.traceln("Inertial measurement unit initialization completed");

    // FRAM

    Log.traceln("Initializing FRAM");
    busswitch_enable();
    _fram.begin();
    busswitch_disable();
    Log.traceln("FRAM initialization completed");

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
    _external_rtc.set_time(time);
    return true;
};

/**
 * @brief Return external realtime clock year
 *
 * @return String year
 */

String AvionicsBoard::get_year()
{
    return String(_external_rtc.get_year());
};

/**
 * @brief Return external realtime clock month
 *
 * @return String month
 */

String AvionicsBoard::get_month()
{
    return String(_external_rtc.get_month());
};

/**
 * @brief Return external realtime clock day
 *
 * @return String day
 */

String AvionicsBoard::get_day()
{
    return String(_external_rtc.get_day());
};

/**
 * @brief Return external realtime clock hour
 *
 * @return String hour
 */

String AvionicsBoard::get_hour()
{
    return String(_external_rtc.get_hour());
};

/**
 * @brief Return external realtime clock minute
 *
 * @return String minute
 */

String AvionicsBoard::get_minute()
{
    return String(_external_rtc.get_minute());
};

/**
 * @brief Return external realtime clock second
 *
 * @return String second
 */

String AvionicsBoard::get_second()
{
    return String(_external_rtc.get_second());
};

/**
 * @brief Return external realtime clock timestamp
 *
 * @return String
 */

String AvionicsBoard::get_timestamp()
{
    return _external_rtc.get_timestamp();
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
    if ((micros() - _last_beacon_time > _beacon_interval) && (_beacon_interval > 0))
    {
        // todo: get power status
        // todo: get payload status
        Beacon message{Beacon::excellent, Beacon::unknown, Beacon::unknown};
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
// todo: error handling for realtime clock not set
{
    if (_external_rtc.get_time() >= _picture_time)
    {
        Log.traceln("Photo time reached %s", get_timestamp().c_str());
        _picture_time = _future_invalid_date;
        extern MockPayloadBoard payload;
        payload.photo();
    };
    return true;
};

/**
 * @brief Get picture times
 *
 * @return String picture time
 */

String AvionicsBoard::get_pic_times()
{
    return _picture_time.timestamp();
};

/**
 * @brief Get telemetry
 *
 * @return String telemetry
 */

String AvionicsBoard::get_telemetry()
{
    busswitch_enable();
    return _imu.get_acceleration() + _imu.get_rotation() + _imu.get_temperature();
    busswitch_disable();
};

String AvionicsBoard::get_beacon_interval()
{
    return String(_beacon_interval / 1000 / 1000);
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
 * @brief Initialize I2C bus switch
 *
 * @return true successful
 * @return false error
 */

bool AvionicsBoard::busswitch_begin()
{
    Log.verboseln("Initializing I2C bus switch");
    pinMode(EN_EXT_I2C, OUTPUT);
    return true;
};

/**
 * @brief Enable I2C bus switch
 *
 * @return true successful
 * @return false error
 */

bool AvionicsBoard::busswitch_enable()
{
    Log.verboseln("Enabling I2C bus switch");
    digitalWrite(EN_EXT_I2C, LOW);
    return true;
};

/**
 * @brief Disable I2C bus switch
 *
 * @return true successful
 * @return false error
 */

bool AvionicsBoard::busswitch_disable()
{
    Log.verboseln("Disabling I2C bus switch");
    digitalWrite(EN_EXT_I2C, HIGH);
    return true;
};

/**
 * @brief Initialize serial buffers
 *
 * @return true successful
 * @return false error
 */

bool AvionicsBoard::serial_buffer_begin()
{
    Log.verboseln("Disabling drivers to other boards");
    pinMode(EN_PAYLOAD_SERIAL, OUTPUT);
    digitalWrite(EN_PAYLOAD_SERIAL, LOW);
    pinMode(EN_RADIO_SERIAL, OUTPUT);
    digitalWrite(EN_RADIO_SERIAL, LOW);
    return true;
};

/**
 * @brief Enable serial buffer to Radio Board
 *
 * @return true successful
 * @return false error
 */

bool AvionicsBoard::serial_buffer_enable()
{
    Log.verboseln("Enabling serial driver to Radio Board");
    digitalWrite(EN_RADIO_SERIAL, HIGH);
    return true;
};

/**
 * @brief Disable serial buffer to Radio Board
 *
 * @return true successful
 * @return false error
 */

bool AvionicsBoard::serial_buffer_disable()
{
    Log.verboseln("Disabling serial driver to Radio Board");
    digitalWrite(EN_RADIO_SERIAL, LOW);
    return true;
};

String AvionicsBoard::read_fram(size_t address)
{
    busswitch_enable();
    return String(_fram.read(address));
    busswitch_disable();
};