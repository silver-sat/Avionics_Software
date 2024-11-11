/**
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Device driver for SilverSat antenna
 *
 */

#include "Antenna.h"
#include "avionics_constants.h"
#include "log_utility.h"
#include "AvionicsBoard.h"

constexpr unsigned long bypass_separation_delay{3 * seconds_to_milliseconds}; /**< Separation delay prior to antenna deployment for testing */
constexpr unsigned long bypass_antenna_delay{3 * seconds_to_milliseconds};    /** Delay for each attempt at antenna deployment for testing */
constexpr unsigned long bypass_entry_timeout = 30 * seconds_to_milliseconds;  /**< Bypass entry delay */

/**
 * @brief Initialize the antenna
 *
 * @return true successful
 */

bool Antenna::begin()
{
    Log.traceln("Antenna initialzing");
    get_bypass();
    Log.verboseln("Opening antenna device");
    if (!m_i2c_dev.begin())
    {
        Log.errorln("Antenna I2C device not found");
        return false;
    }
    Log.verboseln("Antenna device found");
    Log.traceln("Antenna initialization complete");
    return true;
}

/**
 * @brief Test antenna state during startup
 *
 */

void Antenna::test_antenna()
{
    if (check_deployment_state() == AntennaStatus::closed)
    {
        Log.noticeln("Antenna is closed");
    }
    else
    {
        Log.warningln("Antenna is not closed");
    }
}

/**
 * @brief Check antenna
 *
 * @return true open
 * @return false closed or error
 */

bool Antenna::check_antenna()
{
    switch (m_state)
    {
    case AntennaState::startup:
    {
        Log.noticeln("Beginning satellite separation delay");
        Log.verboseln("Separation delay is %d seconds", separation_delay / seconds_to_milliseconds);
        m_state = AntennaState::in_delay;
        m_state_start_time = millis();
        break;
    }
    case AntennaState::in_delay:
    {
        if ((millis() - m_state_start_time) >= separation_delay)
        {
            Log.verboseln("Separation delay completed");
            Log.verboseln("Antenna delay is %d seconds for each cycle required", antenna_delay / seconds_to_milliseconds);
            Log.noticeln("Beginning antenna deployment with algorithm 1");
            constexpr uint8_t algorithm1_all{0x1F};
            m_i2c_dev.write(&algorithm1_all, 1);
            m_state = AntennaState::deploying_algorithm_1;
            m_state_start_time = millis();
        }
        break;
    }
    case AntennaState::deploying_algorithm_1:
    {
        if (millis() - m_state_start_time >= antenna_delay)
        {
            if (check_deployment_state() == AntennaStatus::open)
            {
                deployment_completed();
            }
            else
            {
                Log.warningln("Antenna is not open");
                Log.noticeln("Deploying antenna with algorithm 2");
                constexpr u_int8_t algorithm2_all{0x2F};
                m_i2c_dev.write(&algorithm2_all, 1);
                m_state = AntennaState::deploying_algorithm_2;
                m_state_start_time = millis();
            }
        }
        break;
    }
    case AntennaState::deploying_algorithm_2:
    {
        if (millis() - m_state_start_time >= antenna_delay)
        {
            if (check_deployment_state() == AntennaStatus::open)
            {
                deployment_completed();
            }
            else
            {
                Log.errorln("Antenna is not open");
                Log.noticeln("Issuing Radio Board command to deploy antenna via DigitalIO mode A");
                Message message{Message::antenna_release, "A"};
                message.send();
                m_state = AntennaState::deploying_radio_A;
                m_state_start_time = millis();
            }
        }
        break;
    }
    case AntennaState::deploying_radio_A:
    {
        if (millis() - m_state_start_time >= antenna_delay)
        {
            if (check_deployment_state() == AntennaStatus::open)
            {
                deployment_completed();
            }
            else
            {
                Log.errorln("Antenna is not open");
                Log.noticeln("Issuing Radio Board command to deploy antenna via DigitalIO mode B");
                Message message{Message::antenna_release, "B"};
                message.send();
                m_state = AntennaState::deploying_radio_B;
                m_state_start_time = millis();
            }
        }
        break;
    }
    case AntennaState::deploying_radio_B:
    {
        if (millis() - m_state_start_time >= antenna_delay)
        {
            if (check_deployment_state() == AntennaStatus::open)
            {
                deployment_completed();
            }
            else
            {
                Log.fatalln("Antenna deployment failed");
                Log.noticeln("Attempting to continue");
                m_state = AntennaState::completed;
                m_state_start_time = millis();
                m_antenna_deployed = false;
                m_antenna_cycle_completed = true;
            }
        }
        break;
    }
    case AntennaState::completed:
    {
        break;
    }
    default:
    {
        break;
    }
    }
    return m_antenna_deployed;
}

bool Antenna::get_bypass()
{
    unsigned long start_time{millis()};
    char incoming_char{};
    extern AvionicsBoard avionics;

    Serial.print("Press 'n' or 'N' to bypass separation and antenna delays: ");

    while (millis() - start_time < bypass_entry_timeout)
    {
        avionics.service_watchdog(); // service the watchdog while waiting
        if (Serial.available() > 0)
        {
            incoming_char = Serial.read();
            if (incoming_char != 'n' && incoming_char != 'N')
            {
                Serial.write(BELL);
                continue;
            }
            Serial.println(incoming_char);
            Log.noticeln("Bypassing separation and antenna delays");
            separation_delay = bypass_separation_delay;
            antenna_delay = bypass_antenna_delay;
            return true;
        }
    }
    Serial.println();
    Log.noticeln("Timeout during bypass entry, full separation and antenna delays will be used");
    // separation_delay = bypass_separation_delay;
    // antenna_delay = bypass_antenna_delay;
    return false;
}

/**
 * @brief deployment completed successfully
 *
 */

void Antenna::deployment_completed()
{
    Log.noticeln("Antenna deployment completed");
    m_state = AntennaState::completed;
    m_state_start_time = millis();
    m_antenna_deployed = true;
    m_antenna_cycle_completed = true;
}

/**
 * @brief Check antenna state
 *
 * @return Fourth byte of antenna state as defined in Antenna User Manual
 *
 */

AntennaStatus Antenna::check_deployment_state()
{
    Log.verboseln("Reading antenna state");
    byte antenna_state[4]{};
    m_i2c_dev.read(antenna_state, 4);
    for (size_t index{0}; index < 4; ++index)
        Log.verboseln("Antenna byte %d: %X", index, antenna_state[index]);
    return static_cast<AntennaStatus>(antenna_state[3]);
}
