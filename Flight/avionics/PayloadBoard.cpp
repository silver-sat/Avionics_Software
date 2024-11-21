/**
 * @author Lee A. Congdon (lee@silversat.org)
 * @author Benjamin S. Cohen (ben@silversat.org)
 * @brief SilverSat Payload Board
 *
 * This file implements the class which interfaces with the Payload Board
 *
 */

#include "PayloadBoard.h"
#include "PowerBoard.h"
#include "Beacon.h"
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
    if (!check_startup())
    {
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
    if (!check_startup())
    {
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
    if (!check_startup())
    {
        return false;
    }
    Log.noticeln("Starting communication session");
    set_mode_comms();
    power_up();
    return true;
}

/**
 * @brief Verify Payload Board is ready to start
 *
 * @return true Payload Board is ready
 * @return false Payload Board is not ready
 */

bool PayloadBoard::check_startup()
{
    if (m_state != PayloadState::off)
    {
        Log.errorln("Payload already active");
        return false;
    }
    extern PowerBoard power;
    if (!power.power_adequate())
    {
        Log.errorln("Inadequate power for Payload session");
        return false;
    }
    return true;
}

/**
 * @brief Manage Payload Board state
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
    digitalWrite(STATES_A_INT, LOW);
    digitalWrite(STATES_B_INT, LOW);
    digitalWrite(STATES_C_INT, LOW);
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
    digitalWrite(STATES_A_INT, HIGH);
    digitalWrite(STATES_B_INT, HIGH);
    digitalWrite(STATES_C_INT, HIGH);
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

/*
 * @brief Get the duration interval for the last payload activity
 *
 * @return duration_interval
 *
 */

PayloadBoard::DurationInterval PayloadBoard::get_duration_interval(unsigned long duration_ms)
{
    const unsigned long duration_min = duration_ms / seconds_to_milliseconds / minutes_to_seconds;

    if (duration_min < 1)
    {
        return DurationInterval::less_than_1_minute;
    }
    else if (duration_min < 2)
    {
        return DurationInterval::between_1_and_2_minutes;
    }
    else if (duration_min < 4)
    {
        return DurationInterval::between_2_and_4_minutes;
    }
    else if (duration_min < 6)
    {
        return DurationInterval::between_4_and_6_minutes;
    }
    else if (duration_min < 8)
    {
        return DurationInterval::between_6_and_8_minutes;
    }
    else if (duration_min < 10)
    {
        return DurationInterval::between_8_and_10_minutes;
    }
    else
    {
        return DurationInterval::forced_shutdown;
    }
}

/**
 * @brief Get status for beacon
 *
 */

PayloadBeacon PayloadBoard::get_status()
{
    const auto duration_interval{get_duration_interval(m_last_payload_duration)};

    if (m_overcurrent_occurred)
    {
        Log.errorln("Payload overcurrent during previous activity, session lasted %u milliseconds (interval %d)", m_last_payload_duration, duration_interval);
        return static_cast<PayloadBeacon>(static_cast<size_t>(PayloadBeacon::overcurrent_0_1) + static_cast<size_t>(duration_interval));
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
        Log.verboseln("Previous Payload communication activity lasted %u milliseconds (interval %d)", m_last_payload_duration, duration_interval);
        if (duration_interval >= DurationInterval::less_than_1_minute && duration_interval < DurationInterval::count)
        {
            return static_cast<PayloadBeacon>(static_cast<size_t>(PayloadBeacon::communicate_0_1) + static_cast<size_t>(duration_interval));
        }
        break;
    }

    // photo session
    case PayloadActivity::photo:
    {
        Log.verboseln("Previous Payload photo activity lasted %u milliseconds (interval %d)", m_last_payload_duration, duration_interval);
        if (duration_interval >= DurationInterval::less_than_1_minute && duration_interval < DurationInterval::count)
        {
            return static_cast<PayloadBeacon>(static_cast<size_t>(PayloadBeacon::photo_0_1) + static_cast<size_t>(duration_interval));
        }
        break;
    }

    // SSDV session
    case PayloadActivity::SSDV:
    {
        Log.verboseln("Previous Payload SSDV activity lasted %u milliseconds (interval %d)", m_last_payload_duration, duration_interval);
        if (duration_interval >= DurationInterval::less_than_1_minute && duration_interval < DurationInterval::count)
        {
            return static_cast<PayloadBeacon>(static_cast<size_t>(PayloadBeacon::SSDV_0_1) + static_cast<size_t>(duration_interval));
        }
        break;
    }

    // unknown beacon status
    default:
    {
    }
    }
    Log.errorln("Payload session beacon status error");
    return PayloadBeacon::unknown;
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
