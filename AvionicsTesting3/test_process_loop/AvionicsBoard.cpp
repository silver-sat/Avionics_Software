/**
 * @file AvionicsBoard.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test Avionics Board for SilverSat
 * @version 1.0.2
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

    Log.traceln("Initializing non-critical I2C bus");
    busswitch_begin();
    busswitch_enable();
    Wire1.begin();
    // pinPeripheral(SDA_NON_CRIT, PIO_SERCOM);
    // pinPeripheral(SCL_NON_CRIT, PIO_SERCOM);
    busswitch_disable();
    Log.traceln("Non-critical I2C bus initialization completed");

    // Serial connections

    Log.traceln("Initializing serial buffers");
    serial_buffer_begin();
    Log.traceln("Serial buffer initialization completed");

    // External realtime clock

    Log.traceln("Initializing external realtime clock");

    // todo: replace with Avionics Board external realtime clock

    if (_external_rtc.begin(&Wire))
    {
        Log.traceln("External realtime clock initialization completed");
    }
    else
    {
        Log.errorln("External realtime clock not initialized");
    };

    // Inertial Management Unit

    Log.traceln("Initializing inertial management unit");
    busswitch_enable();
    auto status = _imu.begin(&Wire1);
    busswitch_disable();
    if (status)
    {
        Log.traceln("Inertial measurement unit initialization completed");
    }
    else
    {
        Log.errorln("Inertial management unit not initialized");
    }

    // FRAM

    Log.traceln("Initializing FRAM");
    busswitch_enable();
    status = _fram.begin(FRAM_I2C_ADDRESS, &Wire1);
    busswitch_disable();
    if (status)
    {
        Log.traceln("FRAM initialization completed");
    }
    else
    {
        Log.errorln("FRAM not initialized");
    }

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
    return _external_rtc.set_time(time);
};

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
    if (_external_rtc.is_set())
    {
        if (time > _external_rtc.get_time())
        {
            _picture_time = time;
            return true;
        }
        else
        {
            Log.errorln("Picture time is before current time");
            return false;
        }
    }
    else
    {
        Log.errorln("External realtime clock is not set");
        return false;
    }
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

    // todo: discard photo time if payload board is busy
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
    // todo: consider making busswitch object
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
    // todo: consider making serial buffer object
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

/**
 * @brief Read byte from FRAM
 *
 * @param address address of data
 * @return String byte read
 */

String AvionicsBoard::read_fram(size_t address)
{
    // todo: consider making FRAM object
    busswitch_enable();
    return String(_fram.read(address));
    busswitch_disable();
};

/**
 * @brief Unset the realtime clock
 *
 * @return true successful
 * @return false error
 */

bool AvionicsBoard::unset_clock()
{
    Log.verboseln("Unsetting the realtime clock");
    return _external_rtc.unset_clock();
}