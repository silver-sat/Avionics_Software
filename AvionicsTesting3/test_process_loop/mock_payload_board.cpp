/**
 * @file mock_payload_board.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test the Avionics Board mock Payload Board
 * @version 1.0.0
 * @date 2022-07-24
 *
 *
 */

#include "mock_payload_board.h"
#include "log_utility.h"
#include <Arduino.h>

/**
 * @brief Construct a new Mock Payload Board:: Mock Payload Board object
 *
 */

MockPayloadBoard::MockPayloadBoard(){

};

/**
 * @brief Initialize Payload Board
 *
 * @return true successful
 * @return false error
 */

bool MockPayloadBoard::begin()
{

    Log.traceln("Payload Board initializing");
    return true;
};

/**
 * @brief Power up Payload Board and take photo
 *
 * @return true successful
 * @return false error
 */

bool MockPayloadBoard::photo()
{

    // todo: check for adequate power
    if (!m_payload_active)
    {

        Log.noticeln("Starting photo session");
        m_payload_active = true;
        m_action_duration = m_photo_duration;
        m_last_activity_time = millis();
        set_mode_photo();
        power_up();
        return true;
    }
    else
    {
        Log.errorln("Payload already active");
        return false;
    }
};

/**
 * @brief Power up Payload Board and tweet
 *
 * @return true successful
 * @return false error
 */

bool MockPayloadBoard::tweet()
{
    // todo: check for adequate power
    if (!m_payload_active)
    {

        Log.noticeln("Starting Twitter session");
        m_payload_active = true;
        m_action_duration = m_tweet_duration;
        m_last_activity_time = millis();
        set_mode_comms();
        power_up();
        return true;
    }
    else
    {
        Log.errorln("Payload already active");
        return false;
    }
};

/**
 * @brief Shut off Payload Board if ready to sleep
 *
 * @return true successful
 * @return false error
 */

bool MockPayloadBoard::check_shutdown()
{
    if (m_payload_active && millis() - m_last_activity_time > m_action_duration)
    {
        end_activity();
    }
    if (power_down_signal_is_set())
    {
        Log.verboseln("Powering down payload");
        // todo: verify timing of shutdown signal reset
        m_power_down_signal = false;
        power_down();
    }
    return true;
}

/**
 * @brief End payload session
 *
 * @return true successful
 * @return false error
 */

bool MockPayloadBoard::end_activity()
{
    if (!m_payload_active)
    {
        Log.traceln("No payload activity");
    }
    else
    {
        Log.traceln("Payload activity ending");
    }
    m_payload_active = false;
    m_power_down_signal = true;
    return true;
};

/**
 * @brief Power down Payload Board
 *
 * @return true successful
 * @return false error
 */

bool MockPayloadBoard::power_down()
{
    // todo: set GPIO pins for power down
    Log.verboseln("Payload power off");
    return true;
};

/**
 * @brief Power up Payload Board
 *
 * @return true successful
 * @return false error
 */

bool MockPayloadBoard::power_up()
{
    // todo: set GPIO pins for power up
    Log.verboseln("Payload power on");
    return true;
};

/**
 * @brief Set the mode to communications
 *
 * @return true successful
 * @return false error
 */
bool MockPayloadBoard::set_mode_comms()
{
    // todo: set appropriate GPIO pins for tweet
    Log.verboseln("Payload mode set to tweet");
    if (m_photo_count > 0)
    {
        m_photo_count -= 1;
    }
    return true;
};

/**
 * @brief Set the mode to photograph
 *
 * @return true successful
 * @return false error
 */
bool MockPayloadBoard::set_mode_photo()
{
    // todo: set appropriate GPIO pins for photo
    Log.verboseln("Payload mode set to photo");
    m_photo_count += 1;
    return true;
};

/**
 * @brief Check Payload Board shutdown signal
 *
 * @return true successful
 * @return false error
 */

bool MockPayloadBoard::power_down_signal_is_set()
{
    return m_power_down_signal;
};

/**
 * @brief Get the photo count
 *
 * @return int photo count
 */

int MockPayloadBoard::get_photo_count()
{
    // todo: provide I2C interface to FRAM to access photo count

    return m_photo_count;
}

/**
 * @brief Get the payload activity status
 *
 * @return true active
 * @return false powered down
 */

bool MockPayloadBoard::get_payload_active()
{
    return m_payload_active;
};
