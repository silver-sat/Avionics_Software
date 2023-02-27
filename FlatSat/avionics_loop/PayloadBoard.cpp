/**
 * @file PayloadBoard.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat Payload Board
 * @version 1.1.0
 * @date 2022-07-24
 *
 * This file implements the class which interfaces with the Payload Board
 *
 */

#include "PayloadBoard.h"
#include "log_utility.h"

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
    power_down();
    Log.traceln("Payload Board initialization complete");
    return true;
};

/**
 * @brief Power up Payload Board and take photo
 *
 * @return true successful
 * @return false error
 *
 */

bool PayloadBoard::photo()
{

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
};

/**
 * @brief Power up Payload Board and communicate
 *
 * @return true successful
 * @return false error
 *
 */

bool PayloadBoard::communicate()
{
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
};

/**
 * @brief Shut off Payload Board if ready to sleep
 *
 * @return true successful
 * @return false error
 *
 */

bool PayloadBoard::check_shutdown()
{
    if (m_payload_active && power_down_signal_is_set())
    {
        Log.verboseln("Powering down payload");
        power_down();
    }
    return true;
}

    /**
     * @brief Get the photo count
     * 
     */
    // todo: count is not reliable, recommending deprecating the GetPhotos command
    int PayloadBoard::get_photo_count() const {
        return -1;
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
 *
 */

bool PayloadBoard::power_up()
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
 *
 */

bool PayloadBoard::set_mode_comms()
{
    digitalWrite(STATES_A_INT, HIGH);
    digitalWrite(STATES_B_INT, HIGH);
    digitalWrite(STATES_C_INT, HIGH);
    Log.verboseln("Payload mode set to communicate");
    return true;
};

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
    Log.verboseln("Payload mode set to photo");
    return true;
};

/**
 * @brief Check Payload Board shutdown signal
 *
 * @return true successful
 * @return false error
 *
 */

bool PayloadBoard::power_down_signal_is_set() const
{
    auto a = digitalRead(SHUTDOWN_A);
    auto b = digitalRead(SHUTDOWN_B);
    auto c = digitalRead(SHUTDOWN_C);
    if ((a + b + c) >= 2) {
        Log.verboseln("Shutdown signal received");
    }
    return ((a + b + c) >= 2);
};

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
};
