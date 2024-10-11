/**
 * @file PayloadBoard.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @author Benjamin S. Cohen (ben@silversat.org)
 * @brief SilverSat Payload Board
 * @version 1.1.1
 * @date 2022-07-24
 *
 * This file implements the class which interfaces with the Payload Board
 *
 */

#include "PayloadBoard.h"
#include "PowerBoard.h"
#include "log_utility.h"

/**
 * @brief Payload Board constants
 *
 *
 */

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
    power_down();
    pinMode(STATES_A_INT, OUTPUT);
    pinMode(STATES_B_INT, OUTPUT);
    pinMode(STATES_C_INT, OUTPUT);
    pinMode(SHUTDOWN_A, INPUT);
    pinMode(SHUTDOWN_B, INPUT);
    pinMode(SHUTDOWN_C, INPUT);
    pinMode(PAYLOAD_OC, INPUT);
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
    if (m_state != PayloadState::off)
    {
        Log.errorln("Payload already active");
        return false;
    }
    extern PowerBoard power;
    if (!power.power_adequate())
    {
        Log.errorln("Inadequate power for photo session");
        return false;
    }
    Log.noticeln("Starting photo session");
    set_mode_photo();
    power_up();
    return true;
}

/**
 * @brief Power up Payload Board and start SSDV
 *
 * @return true successful
 * @return false error
 *
 */

bool PayloadBoard::SSDV()
{
    if (m_state != PayloadState::off)
    {
        Log.errorln("Payload already active");
        return false;
    }
    extern PowerBoard power;
    if (!power.power_adequate())
    {
        Log.errorln("Inadequate power for photo session");
        return false;
    }
    Log.noticeln("Starting SSDV session");
    set_mode_SSDV_start();
    power_up();
    return true;
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
    if (m_state != PayloadState::off)
    {
        Log.errorln("Payload already active");
        return false;
    }
    extern PowerBoard power;
    if (!power.power_adequate())
    {
        Log.errorln("Inadequate power for communications session");
        return false;
    }
    Log.noticeln("Starting communication session");
    set_mode_comms();
    power_up();
    return true;
}

/**
 * @brief Shut off Payload Board if ready to sleep
 *
 *
 */

void PayloadBoard::check_shutdown()
{
    bool shutdown{shutdown_vote()};
    check_timeout();
    check_overcurrent();
    switch (m_state)
    {
    case PayloadState::off:
    {
        break;
    }
    case PayloadState::user_state_wait:
    {
        if (!shutdown)
        {
            Log.verboseln("Payload user state active");
            if (m_activity == PayloadActivity::photo)
            {
                Log.verboseln("Photo session requested");
                m_state = PayloadState::photo;
            }
            else if (m_activity == PayloadActivity::communications)
            {
                Log.verboseln("Communications session requested");
                m_state = PayloadState::communications;
            }
            else if (m_activity == PayloadActivity::SSDV)
            {
                Log.verboseln("SSDV session requested");
                m_SSDV_signal_start_time = millis();
                m_state = PayloadState::signal_SSDV;
            }
            else
            {
                Log.errorln("Payload activity not set");
                m_state = PayloadState::off;
            }
        }
        break;
    }
    case PayloadState::photo:
    {
        if (shutdown)
        {
            Log.verboseln("Photo session complete");
            m_state = PayloadState::shutdown;
            m_shutdown_start_time = millis();
        }
        break;
    }
    case PayloadState::communications:
    {
        if (shutdown)
        {
            Log.verboseln("Communications session complete");
            m_state = PayloadState::shutdown;
            m_shutdown_start_time = millis();
        }
        break;
    }
    case PayloadState::signal_SSDV:
    {
        if (millis() - m_SSDV_signal_start_time > 1 * seconds_to_milliseconds)
        {
            set_mode_SSDV_transition();
            Log.verboseln("SSDV signal completed");
            m_state = PayloadState::SSDV;
        }
        break;
    }
    case PayloadState::SSDV:
    {
        if (shutdown)
        {
            Log.verboseln("SSDV session complete");
            m_state = PayloadState::shutdown;
            m_shutdown_start_time = millis();
        }
        break;
    }
    case PayloadState::shutdown:
    {
        if (millis() - m_shutdown_start_time > shutdown_delay)
        {
            Log.verboseln("Payload shutdown delay complete");
            power_down();
        }
        break;
    }
    case PayloadState::timeout:
    {
        Log.errorln("Payload cycle timeout");
        power_down();
        m_timeout_occurred = true;
        break;
    }
    case PayloadState::overcurrent:
    {
        Log.errorln("Payload overcurrent");
        power_down();
        m_overcurrent_occurred = true;
        break;
    }
    default:
    {
        break;
    }
    }
    return;
}

/**
 * @brief Shutdown vote
 *
 * @return true shutdown signal was set
 * @false shutdown signal was not set
 *
 */
bool PayloadBoard::shutdown_vote()
{
    auto shutdown_a{digitalRead(SHUTDOWN_A)};
    auto shutdown_b{digitalRead(SHUTDOWN_B)};
    auto shutdown_c{digitalRead(SHUTDOWN_C)};
    return (shutdown_a + shutdown_b + shutdown_c >= 2);
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
    m_state = PayloadState::off;
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
    m_state = PayloadState::user_state_wait;
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
    m_activity = PayloadActivity::communications;
    Log.verboseln("STATES set to communicate");
    return true;
}

/**
 * @brief Set the mode to SSDV start
 *
 * @return true successful
 * @return false error
 *
 */

bool PayloadBoard::set_mode_SSDV_start()
{
    digitalWrite(STATES_A_INT, HIGH);
    digitalWrite(STATES_B_INT, HIGH);
    digitalWrite(STATES_C_INT, HIGH);
    m_activity = PayloadActivity::SSDV;
    Log.verboseln("STATES set to SSDV start");
    return true;
}

/**
 * @brief Set the mode to SSDV transition
 *
 * @return true successful
 * @return false error
 *
 */

bool PayloadBoard::set_mode_SSDV_transition()
{
    digitalWrite(STATES_A_INT, LOW);
    digitalWrite(STATES_B_INT, LOW);
    digitalWrite(STATES_C_INT, LOW);
    Log.verboseln("STATES set to SSDV transition");
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
    m_activity = PayloadActivity::photo;
    Log.verboseln("STATES set to photo");
    return true;
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
    return m_state != PayloadState::off;
}

/**
 * @brief Get status for beacon
 *
 */

PayloadBeacon PayloadBoard::get_status()
{
    const int duration_bucket{static_cast<int>(m_last_payload_duration / seconds_to_milliseconds / minutes_to_seconds)};

    if (m_overcurrent_occurred)
    {
        Log.errorln("Payload overcurrent during previous activity, session lasted %u milliseconds (duration bucket %d)", m_last_payload_duration, duration_bucket);
        switch (duration_bucket)
        {
        case 0:
            return PayloadBeacon::overcurrent_0_1;
        case 1:
            return PayloadBeacon::overcurrent_1_2;
        case 2:
            return PayloadBeacon::overcurrent_2_3;
        case 3:
            return PayloadBeacon::overcurrent_3_4;
        case 4:
            return PayloadBeacon::overcurrent_4_5;
        case 5:
            return PayloadBeacon::overcurrent_5_6;
        case 6:
            return PayloadBeacon::overcurrent_6_7;
        case 7:
            return PayloadBeacon::overcurrent_7_8;
        case 8:
            return PayloadBeacon::overcurrent_8_9;
        case 9:
            return PayloadBeacon::overcurrent_9_10;
        default:
            return PayloadBeacon::unknown;
        }
    }
    switch (m_activity)
    {

    // no payload activity
    case PayloadActivity::none:
    {
        Log.verboseln("No payload activity has occurred");
        return PayloadBeacon::none;
    }

    // communications session
    case PayloadActivity::communications:
    {
        if (m_timeout_occurred)
        {
            Log.errorln("Timeout during previous activity (communications)");
            return PayloadBeacon::communicate_timeout;
        }
        else
        {
            Log.verboseln("Previous activity (communications) lasted %u milliseconds (duration bucket %d)", m_last_payload_duration, duration_bucket);
            switch (duration_bucket)
            {
            case 0:
                return PayloadBeacon::communicate_0_1;
            case 1:
                return PayloadBeacon::communicate_1_2;
            case 2:
                return PayloadBeacon::communicate_2_3;
            case 3:
                return PayloadBeacon::communicate_3_4;
            case 4:
                return PayloadBeacon::communicate_4_5;
            case 5:
                return PayloadBeacon::communicate_5_6;
            case 6:
                return PayloadBeacon::communicate_6_7;
            case 7:
                return PayloadBeacon::communicate_7_8;
            case 8:
                return PayloadBeacon::communicate_8_9;
            case 9:
                return PayloadBeacon::communicate_9_10;
            default:
                return PayloadBeacon::unknown;
            }
        }
    }

    // photo session
    case PayloadActivity::photo:
    {
        if (m_timeout_occurred)
        {
            Log.errorln("Timeout during previous activity (photo)");
            return PayloadBeacon::photo_timeout;
        }
        else
        {
            Log.verboseln("Previous activity (photo) lasted %u milliseconds (duration bucket %d)", m_last_payload_duration, duration_bucket);
            switch (duration_bucket)
            {
            case 0:
                return PayloadBeacon::photo_0_1;
            case 1:
                return PayloadBeacon::photo_1_2;
            case 2:
                return PayloadBeacon::photo_2_3;
            case 3:
                return PayloadBeacon::photo_3_4;
            case 4:
                return PayloadBeacon::photo_4_5;
            case 5:
                return PayloadBeacon::photo_5_6;
            case 6:
                return PayloadBeacon::photo_6_7;
            case 7:
                return PayloadBeacon::photo_7_8;
            case 8:
                return PayloadBeacon::photo_8_9;
            case 9:
                return PayloadBeacon::photo_9_10;
            default:
                return PayloadBeacon::unknown;
            }
        }
    }

    // unknown beacon status
    default:
    {
        Log.errorln("Payload session beacon status error");
        return PayloadBeacon::unknown;
    }
    }
}

/**
 * @brief Check timeout
 *
 */
void PayloadBoard::check_timeout()
{
    if (millis() - m_payload_start_time > maximum_cycle_time && m_state != PayloadState::off)
    {
        m_state = PayloadState::timeout;
    }
}

/**
 * @brief Check overcurrent
 *
 */
void PayloadBoard::check_overcurrent()
{
    if (!digitalRead(PAYLOAD_OC))
    {
        m_state = PayloadState::overcurrent;
    }
}
