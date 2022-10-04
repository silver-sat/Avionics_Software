/**
 * @file AvionicsBoard.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test Avionics Board for SilverSat
 * @version 1.0.3
 * @date 2022-07-29
 *
 *
 */

#include "AvionicsBoard.h"
#include "log_utility.h"
#include "mock_radio_board.h"
#include "mock_payload_board.h"

/**
 * @brief Avionics Board constants
 * 
 */

constexpr uint16_t minimum_valid_year{2020};
constexpr uint16_t maximum_valid_year{2040};

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
    busswitch_disable();
    Log.traceln("Non-critical I2C bus initialization completed");

    // Serial connections

    Log.traceln("Initializing serial buffers");
    serial_buffer_begin();
    Log.traceln("Serial buffer initialization completed");

    // External realtime clock

    Log.traceln("Initializing external realtime clock");

    // todo: replace with Avionics Board external realtime clock
    // todo: does not fail if no clock attached
    // todo: clock fails on power change (e.g. adding 5v to board)

    if (m_external_rtc.begin(&Wire))
    {
        Log.traceln("External realtime clock initialization completed");
    }
    else
    {
        Log.errorln("External realtime clock not initialized");
    };

    // Inertial Management Unit

    Log.traceln("Initializing inertial management unit");
    // todo: initialization hangs if no IMU present
    auto status = m_imu.begin(&Wire1);
    if (status)
    {
        Log.traceln("Inertial measurement unit initialization completed");
    }
    else
    {
        Log.errorln("Inertial management unit not initialized");
    }

    // FRAM

    // todo: replace with Avionics Board FRAM

    Log.traceln("Initializing FRAM");
    // todo: initialization hangs if no FRAM present
    status = m_fram.begin(FRAM_I2C_ADDRESS, &Wire1);
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
    return m_watchdog.set_force_reset();
};

/**
 * @brief Set the external realtime clock
 *
 * @param time new time setting
 * @return true successful
 * @return false error
 */

bool AvionicsBoard::set_external_rtc(DateTime time)
{
    if ((time.year() <= minimum_valid_year) || (time.year() >= maximum_valid_year))
    {
        Log.errorln("Time must be between %d and %d, inclusive", minimum_valid_year, maximum_valid_year);
        return false;
    }

    return m_external_rtc.set_time(time);
};

/**
 * @brief Get a timestamp
 *
 * @return String timestamp
 */

String AvionicsBoard::get_timestamp()
{
    return m_external_rtc.get_timestamp();
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
    m_beacon_interval = seconds * SECONDS_TO_MILLISECONDS;
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
    if ((millis() - m_last_beacon_time > m_beacon_interval) && (m_beacon_interval > 0))
    {
        // todo: get power status
        m_avionics_status = Beacon::excellent;
        extern MockRadioBoard radio;
        // todo: retrieve and store radio status
        if (radio.get_status() == "unknown")
        {
            m_radio_status = Beacon::unknown;
        }
        else
        {
            m_radio_status = Beacon::unknown;
        }
        extern MockPayloadBoard payload;
        if (payload.get_payload_active())
        {
            m_payload_status = Beacon::on;
        }
        else
        {
            m_payload_status = Beacon::off;
        }
        Beacon message{m_power_status, m_avionics_status, m_radio_status, m_payload_status};
        radio.send_beacon(message);
        m_last_beacon_time = millis();
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
    if (!m_external_rtc.is_set())
    {
        Log.errorln("External realtime clock is not set");
        return false;
    }
    if ((time.year() <= minimum_valid_year) || (time.year() >= maximum_valid_year))
    {
        Log.errorln("Picture time must be between %d and %d, inclusive", minimum_valid_year, maximum_valid_year);
        return false;
    }
    if (time < m_external_rtc.get_time())
    {
        Log.errorln("Picture time is before current time");
        return false;
    }
    if (m_picture_count + 1 > maximum_scheduled_pictures)
    {
        Log.errorln("Too many picture times");
        return false;
    }
    size_t index{m_picture_count++};
    for (; index > 0; index--)
    {
        if (time > m_picture_times[index - 1])
        {
            break;
        }
        else
        {
            m_picture_times[index] = m_picture_times[index - 1];
        }
    }
    m_picture_times[index] = time;
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
    if (!m_external_rtc.is_set())
    {
        return false;
    }
    if ((m_external_rtc.get_time().year() < minimum_valid_year) || (m_external_rtc.get_time().year() > maximum_valid_year )) {
        Log.errorln("Invalid time from external real time clock: %x", m_external_rtc.get_time());
        return false;
    }
    if ((m_picture_count > 0) && (m_external_rtc.get_time() >= m_picture_times[0]))
    {
        Log.traceln("Photo time reached %s", get_timestamp().c_str());
        for (size_t index = 0; index < m_picture_count; index++)
        {
            m_picture_times[index] = m_picture_times[index + 1];
        }
        m_picture_count--;
        extern MockPayloadBoard payload;
        if (payload.get_payload_active())
        {
            Log.errorln("Payload board active, picture time ignored");
            return false;
        }
        else
        {
            payload.photo();
        }
    };
    return true;
};

/**
 * @brief Get picture times
 *
 * @return String count and timestamps
 */

String AvionicsBoard::get_pic_times()
{
    String response{m_picture_count};
    for (size_t index = 0; index < m_picture_count; index++)
    {
        response += m_picture_times[index].timestamp();
    }
    return response;
};

/**
 * @brief Clear picture times
 *
 * @return true successful
 * @return false error
 */

bool AvionicsBoard::clear_pic_times()
{
    m_picture_count = 0;
    return true;
};

/**
 * @brief Get telemetry
 *
 * @return String telemetry
 */

String AvionicsBoard::get_telemetry()
{
    return m_imu.get_acceleration() + m_imu.get_rotation() + m_imu.get_temperature();
};

String AvionicsBoard::get_beacon_interval()
{
    return String(m_beacon_interval / SECONDS_TO_MILLISECONDS);
};

/**
 * @brief Trigger the watchdog
 *
 * @return true successful
 * @return false error
 */

bool AvionicsBoard::trigger_watchdog()
{
    m_watchdog.trigger();
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
    Log.verboseln("Disabling serial connection to payload board");
    pinMode(EN_PAYLOAD_SERIAL, OUTPUT);
    digitalWrite(EN_PAYLOAD_SERIAL, LOW);
    // todo: verify connection to radio board should always be active
    // pinMode(EN_RADIO_SERIAL, OUTPUT);
    // digitalWrite(EN_RADIO_SERIAL, LOW);
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
    return String(m_fram.read(address));
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
    return m_external_rtc.unset_clock();
}