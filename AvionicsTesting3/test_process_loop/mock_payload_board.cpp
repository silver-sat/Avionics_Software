/**
 * @file mock_payload_board.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test the Avionics Board mock Payload Board
 * @version 1.0.1
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
    pinMode(PLD_ON_A_INT, OUTPUT);
    pinMode(PLD_ON_B_INT, OUTPUT);
    pinMode(PLD_ON_C_INT, OUTPUT);
    pinMode(STATES_A_INT, OUTPUT);
    pinMode(STATES_B_INT, OUTPUT);
    pinMode(STATES_C_INT, OUTPUT);
    pinMode(SHUTDOWN_A, INPUT);
    pinMode(SHUTDOWN_B, INPUT);
    pinMode(SHUTDOWN_C, INPUT);

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

    if (!m_payload_active)
    {
        Log.noticeln("Starting photo session");
        // todo: delete timing of photo for flatsat test
        m_action_duration = photo_duration;
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
    if (!m_payload_active)
    {
        Log.noticeln("Starting Twitter session");
        // todo: delete timing of tweet session for flatsat test
        m_action_duration = tweet_duration;
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
    // todo: delete for flatsat test
    if (m_payload_active && millis() - m_last_activity_time > m_action_duration)
    {
        end_activity();
    }
    if (power_down_signal_is_set())
    {
        Log.verboseln("Powering down payload");
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
// todo: delete for flatsat test
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
    digitalWrite(PLD_ON_A_INT, LOW);
    digitalWrite(PLD_ON_B_INT, LOW);
    digitalWrite(PLD_ON_C_INT, LOW);
    m_payload_active = false;
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
    digitalWrite(PLD_ON_A_INT, HIGH);
    digitalWrite(PLD_ON_B_INT, HIGH);
    digitalWrite(PLD_ON_C_INT, HIGH);
    m_payload_active = true;
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
    digitalWrite(STATES_A_INT, HIGH);
    digitalWrite(STATES_B_INT, HIGH);
    digitalWrite(STATES_C_INT, HIGH);
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
    digitalWrite(STATES_A_INT, LOW);
    digitalWrite(STATES_B_INT, LOW);
    digitalWrite(STATES_C_INT, LOW);
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
    bool a = digitalRead(SHUTDOWN_A);
    bool b = digitalRead(SHUTDOWN_B);
    bool c = digitalRead(SHUTDOWN_C);
    // todo: return (a + b + c) >= 2;
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
