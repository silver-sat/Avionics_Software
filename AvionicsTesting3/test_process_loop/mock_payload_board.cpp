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

    power_down();
    Log.verboseln("Payload initialized");
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
    if (!_payload_active)
    {

        Log.noticeln("Starting photo session");
        _payload_active = true;
        _action_duration = _photo_duration;
        _last_activity_time = micros();
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
    if (!_payload_active)
    {

        Log.noticeln("Starting Twitter session");
        _payload_active = true;
        _action_duration = _tweet_duration;
        _last_activity_time = micros();
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
    if (_payload_active && (micros() - _last_activity_time > _action_duration))
    {
        Log.traceln("Payload activity ending");
        _payload_active = false;
        _power_down_signal = true;
    }
    if (power_down_signal_is_set())
    {
        Log.verboseln("Received power off signal from payload");
        // todo: verify timing of shutdown signal reset
        _power_down_signal = false;
        power_down();
    }
    return true;
}

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
    // toto: set GPIO pins for power up
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
    return _power_down_signal;
};
