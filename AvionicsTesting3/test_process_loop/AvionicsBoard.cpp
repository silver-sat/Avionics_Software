/**
 * @file AvionicsBoard.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test Avionics Board for SilverSat
 * @version 1.0.0
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

AvionicsBoard::AvionicsBoard()
{
    RTC_PCF8523 rtc;
    _external_rtc = rtc;

    /**
     * @brief Create interface objects
     *
     */

    // Watchdog watchdog{};
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
 * @brief Return external realtime clock status
 *
 * @return true clock is set
 * @return false clock is not set
 */

bool AvionicsBoard::get_external_rtc_is_set()
{
    return _external_rtc_is_set;
};

/**
 * @brief Return external realtime clock year
 *
 * @return int year
 */

int AvionicsBoard::get_year()
{
    return _external_rtc.now().year();
};

/**
 * @brief Return external realtime clock month
 *
 * @return int month
 */

int AvionicsBoard::get_month()
{
    return _external_rtc.now().month();
};

/**
 * @brief Return external realtime clock day
 *
 * @return int day
 */

int AvionicsBoard::get_day()
{
    return _external_rtc.now().day();
};

/**
 * @brief Return external realtime clock hour
 *
 * @return int hour
 */

int AvionicsBoard::get_hour()
{
    return _external_rtc.now().hour();
};

/**
 * @brief Return external realtime clock minute
 *
 * @return int minute
 */

int AvionicsBoard::get_minute()
{
    return _external_rtc.now().minute();
};

/**
 * @brief Return external realtime clock second
 *
 * @return int second
 */

int AvionicsBoard::get_second()
{
    return _external_rtc.now().second();
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

bool AvionicsBoard::beacon()
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
    if (_external_rtc.now() >= _picture_time)
    {
        Log.traceln("Photo time reached");
        _picture_time = _future_photo_date;
        extern MockPayloadBoard payload;
        payload.photo();
    };
    return true;
};