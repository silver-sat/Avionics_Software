/**
 * @file PayloadBoard.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat Payload Board
 * @version 1.1.1
 * @date 2022-07-24
 *
 * This file implements the class which interfaces with the Payload Board
 *
 */

#include "PayloadBoard.h"
#include "log_utility.h"

/**
 * @brief Payload Board constants
 *
 *
 */

constexpr int startup_delay{90 * seconds_to_milliseconds};
constexpr int shutdown_delay{15 * seconds_to_milliseconds};
constexpr int maximum_cycle_time{10 * minutes_to_seconds * seconds_to_milliseconds};

/**
 * @brief Initialize Payload Board
 *
 * @return true successful
 * @return false error
 *
 */

bool PayloadBoard::begin()
{
    Log.traceln("Payload Board initializing");
    pinMode(PLD_ON_A_INT, OUTPUT);
    pinMode(PLD_ON_B_INT, OUTPUT);
    pinMode(PLD_ON_C_INT, OUTPUT);
    pinMode(STATES_A_INT, OUTPUT);
    pinMode(STATES_B_INT, OUTPUT);
    pinMode(STATES_C_INT, OUTPUT);
    pinMode(SHUTDOWN_A, INPUT);
    pinMode(SHUTDOWN_B, INPUT);
    pinMode(SHUTDOWN_C, INPUT);
    pinMode(PAYLOAD_OC, INPUT);
    power_down();
    Log.traceln("Payload Board initialization complete");
    return true;
}

/**
 * @brief Power up Payload Board and take photo
 *
 * @return true successful
 * @return false error
 *
 */

bool PayloadBoard::photo()
{
    // todo: check for sufficient power
    if (!m_payload_active)
    {
        Log.noticeln("Starting photo session");
        set_mode_photo();
        power_up();
        return true;
    }
    else
    {
        Log.errorln("Payload already active");
        return false;
    }
}

/**
 * @brief Power up Payload Board and communicate
 *
 * @return true successful
 * @return false error
 *
 */

bool PayloadBoard::communicate()
{
    // todo: check for sufficient power
    if (!m_payload_active)
    {
        Log.noticeln("Starting Communication session");
        set_mode_comms();
        power_up();
        return true;
    }
    else
    {
        Log.errorln("Payload already active");
        return false;
    }
}

/**
 * @brief Shut off Payload Board if ready to sleep
 *
 * @return true successful
 * @return false error
 *
 */

bool PayloadBoard::check_shutdown()
{
    // wait for startup delay, then check shutdown signal
    if (m_payload_active && (millis() - m_payload_start_time > startup_delay) && shutdown_signal_is_set())
    {
        if (m_in_shutdown_delay)
        {
            if (millis() - m_shutdown_start_time > shutdown_delay)
            {
                Log.verboseln("Powering down payload");
                power_down();
            }
        }
        else
        {
            Log.verboseln("Starting payload shutdown delay");
            m_in_shutdown_delay = true;
            m_shutdown_start_time = millis();
        }
    }
    // check for Payload Board timeout
    if (m_payload_active && (millis() - m_payload_start_time > maximum_cycle_time))
    {
        Log.errorln("Payload cycle too long");
        power_down();
        m_timeout_occurred = true;
        return false;
    }
    // check for Payload Board over current
    if (m_payload_active && digitalRead(PAYLOAD_OC))
    {
        Log.errorln("Payload over current");
        power_down();
        m_last_payload_activity = LastPayloadActivity::overcurrent;
        m_overcurrent_occurred = true;
        return false;
    }
    return true;
}

/**
 * @brief Power down Payload Board
 *
 * @return true successful
 * @return false error
 *
 */

bool PayloadBoard::power_down()
{
    digitalWrite(PLD_ON_A_INT, HIGH);
    digitalWrite(PLD_ON_B_INT, HIGH);
    digitalWrite(PLD_ON_C_INT, HIGH);
    m_payload_active = false;
    m_in_shutdown_delay = false;
    m_last_payload_duration = millis() - m_payload_start_time;
    Log.verboseln("Payload power off");
    return true;
}

/**
 * @brief Power up Payload Board
 *
 * @return true successful
 * @return false error
 *
 */

bool PayloadBoard::power_up()
{
    digitalWrite(PLD_ON_A_INT, LOW);
    digitalWrite(PLD_ON_B_INT, LOW);
    digitalWrite(PLD_ON_C_INT, LOW);
    m_timeout_occurred = false;
    m_overcurrent_occurred = false;
    m_payload_active = true;
    m_payload_start_time = millis();
    Log.verboseln("Payload power on");
    return true;
}

/**
 * @brief Set the mode to communications
 *
 * @return true successful
 * @return false error
 *
 */

bool PayloadBoard::set_mode_comms()
{
    digitalWrite(STATES_A_INT, HIGH);
    digitalWrite(STATES_B_INT, HIGH);
    digitalWrite(STATES_C_INT, HIGH);
    m_last_payload_activity = LastPayloadActivity::communicate;
    Log.verboseln("Payload mode set to communicate");
    return true;
}

/**
 * @brief Set the mode to photograph
 *
 * @return true successful
 * @return false error
 *
 */

bool PayloadBoard::set_mode_photo()
{
    digitalWrite(STATES_A_INT, LOW);
    digitalWrite(STATES_B_INT, LOW);
    digitalWrite(STATES_C_INT, LOW);
    m_last_payload_activity = LastPayloadActivity::photo;
    Log.verboseln("Payload mode set to photo");
    return true;
}

/**
 * @brief Check Payload Board shutdown signal
 *
 * @return true successful
 * @return false error
 *
 */

bool PayloadBoard::shutdown_signal_is_set() const
{
    auto shutdown_a = digitalRead(SHUTDOWN_A);
    auto shutdown_b = digitalRead(SHUTDOWN_B);
    auto shutdown_c = digitalRead(SHUTDOWN_C);
    return (shutdown_a + shutdown_b + shutdown_c) >= 2;
}

/**
 * @brief Get the payload activity status
 *
 * @return true active
 * @return false powered down
 *
 */

bool PayloadBoard::get_payload_active() const
{
    return m_payload_active;
}

/**
 * @brief Duration buckets for Payload Board beacon
 *
 */

enum class DurationBuckets
{
    bucket_0_2,   /**< 2 minutes or less */
    bucket_2_4,   /**< 2 to 4 minutes*/
    bucket_4_6,   /**< 4 to 6 minutes*/
    bucket_6_8,   /**< 6 to 8 minutes */
    bucket_8_10,  /** 8 to 10 minutes */
    bucket_error, /** error condition */
};

DurationBuckets get_bucket(unsigned long duration)
{
    double minutes{static_cast<double>(duration) / static_cast<double>(seconds_to_milliseconds) / static_cast<double>(minutes_to_seconds)};
    if (minutes <= 2.0)
        return DurationBuckets::bucket_0_2;
    if (minutes <= 4.0)
        return DurationBuckets::bucket_2_4;
    if (minutes <= 6.0)
        return DurationBuckets::bucket_4_6;
    if (minutes <= 8.0)
        return DurationBuckets::bucket_6_8;
    if (minutes <= 10.0)
        return DurationBuckets::bucket_8_10;
    return DurationBuckets::bucket_error;
}

/**
 * @brief Get status for beacon
 *
 */

PayloadBeacon PayloadBoard::get_status()
{
    // check for no payload activity
    if (m_last_payload_activity == LastPayloadActivity::none)
    {
        Log.verboseln("No payload activity has occurred");
        return PayloadBeacon::none;
    }
    // check for communications session
    if (m_last_payload_activity == LastPayloadActivity::communicate)
    {
        if (m_timeout_occurred)
        {
            Log.errorln("Timeout during last communications session");
            return PayloadBeacon::communicate_timeout;
        }
        else
        {
            Log.verboseln("Last communications session lasted %u milliseconds", m_last_payload_duration);
            switch (get_bucket(m_last_payload_duration))
            {
            case DurationBuckets::bucket_0_2:
                return PayloadBeacon::communicate_0_2;
            case DurationBuckets::bucket_2_4:
                return PayloadBeacon::communicate_2_4;
            case DurationBuckets::bucket_4_6:
                return PayloadBeacon::communicate_4_6;
            case DurationBuckets::bucket_6_8:
                return PayloadBeacon::communicate_6_8;
            case DurationBuckets::bucket_8_10:
                return PayloadBeacon::communicate_8_10;
            default:
                return PayloadBeacon::unknown;
            }
        }
    }
    // check for photo session
    if (m_last_payload_activity == LastPayloadActivity::photo)
    {
        if (m_timeout_occurred)
        {
            Log.errorln("Timeout during last photo session");
            return PayloadBeacon::photo_timeout;
        }
    }
    else
    {
        Log.verboseln("Last photo session lasted %u milliseconds", m_last_payload_duration);
        switch (get_bucket(m_last_payload_duration))
        {
        case DurationBuckets::bucket_0_2:
            return PayloadBeacon::photo_0_2;
        case DurationBuckets::bucket_2_4:
            return PayloadBeacon::photo_2_4;
        case DurationBuckets::bucket_4_6:
            return PayloadBeacon::photo_4_6;
        case DurationBuckets::bucket_6_8:
            return PayloadBeacon::photo_6_8;
        case DurationBuckets::bucket_8_10:
            return PayloadBeacon::photo_8_10;
        default:
            return PayloadBeacon::unknown;
        }
    }
    // check for overcurrent
    if (m_last_payload_activity == LastPayloadActivity::overcurrent)
    {
        Log.errorln("Payload overcurrent, session lasted %u milliseconds", m_last_payload_duration);
        switch (get_bucket(m_last_payload_duration))
        {
        case DurationBuckets::bucket_0_2:
            return PayloadBeacon::overcurrent_0_2;
        case DurationBuckets::bucket_2_4:
            return PayloadBeacon::overcurrent_2_4;
        case DurationBuckets::bucket_4_6:
            return PayloadBeacon::overcurrent_4_6;
        case DurationBuckets::bucket_6_8:
            return PayloadBeacon::overcurrent_6_8;
        case DurationBuckets::bucket_8_10:
            return PayloadBeacon::overcurrent_8_10;
        default:
            return PayloadBeacon::unknown;
        }
    }
    else
    {
        Log.errorln("Payload session beacon status error");
        return PayloadBeacon::unknown;
    }
}