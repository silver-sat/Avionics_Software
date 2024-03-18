/**
 * @file RadioBoard.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat Radio
 * @version 1.3.0
 * @date 2022-07-24
 *
 * This file implements the class that interfaces to the Radio Board
 *
 */

#include "RadioBoard.h"
#include "avionics_constants.h"
#include "log_utility.h"
#include "AvionicsBoard.h"

constexpr uint32_t serial1_baud_rate{57600}; /**< speed of serial1 connection @hideinitializer */

constexpr long ground_contact_interval {7}; /**< maximum days without ground contact for beacon @hideinitializer */

/**
 * @brief Initialize the Radio Board
 *
 * @return true successful
 * @return false error
 *
 */

bool RadioBoard::begin()
{
    Log.traceln("Radio Board initializing");
    Log.verboseln("Enabling serial driver to Radio Board");
    pinMode(EN_RADIO_SERIAL, OUTPUT);
    digitalWrite(EN_RADIO_SERIAL, HIGH);
    Log.verboseln("Initializing command port");
    Serial1.begin(serial1_baud_rate);
    while (!Serial1)
    {
        extern AvionicsBoard avionics;
        avionics.trigger_watchdog();
    }
    Log.verboseln("Command port initialized");
    Serial1.write(FESC);
    Serial1.write(FESC);
    return true;
}

/**
 * @brief Assemble command or response from Serial1 port
 *
 * @param buffer buffer to assemble command
 * @param length maximum length of command
 * @param[out] source local or remote command
 *
 * @return true no command or successful
 * @return false error
 *
 */

bool RadioBoard::receive_frame(char *buffer, const size_t length, char &source)
{
    // Increment days since last ground contact if a day has passed
    if (millis() - m_milliseconds_since_last_ground_contact_day > days_to_hours * hours_to_minutes * minutes_to_seconds * seconds_to_milliseconds)
    {
        ++m_days_since_last_ground_contact;
        m_milliseconds_since_last_ground_contact_day = millis();
    }

    // if data available, process it
    while (Serial1.available())
    {
        char character{static_cast<char>(Serial1.read())};
        // Log.verboseln("Character received: %X", character);
        if (m_received_start)
        {
            if (!m_received_type)
            {
                source = character;
                switch (character)
                {
                case LOCAL_FRAME:
                    m_received_type = true;
                    m_remote_data = false;
                    Log.verboseln("Receiving local data");
                    break;
                case REMOTE_FRAME:
                    m_received_type = true;
                    m_remote_data = true;
                    Log.verboseln("Receiving remote data");
                    break;
                case FEND:
                    break; // drop additional FENDs
                default:
                    Log.errorln("Invalid type");
                    m_received_start = false;
                    break; // restart command
                }
                continue; // drop command type
            }
            else if (character == FEND)
            {
                m_milliseconds_since_last_ground_contact_day = millis();
                m_days_since_last_ground_contact = 0;
                if (m_buffer_index > 0)
                {
                    buffer[m_buffer_index++] = '\0';
                    if (source == REMOTE_FRAME)
                        Log.infoln("Command received (count %l): %s", ++m_commands_received, buffer);
                    else
                    {
                        Log.infoln("Local message received: %s", buffer);
                    }
                    m_received_start = false;
                    return true; // command or response received
                }
                else
                    Log.errorln("No command received");
            }
            if (m_received_escape)
            {
                m_received_escape = false;
                switch (character)
                {
                case TFEND:
                    character = FEND;
                    break;
                case TFESC:
                    character = FESC;
                    break;
                default:
                    Log.errorln("FESC followed by invalid character, command ignored");
                    m_received_start = false;
                    break; // restart command
                }
            }
            else if (character == FESC)
            {
                m_received_escape = true;
                continue; // drop escape character
            }
            if (m_buffer_index < length)
                buffer[m_buffer_index++] = character;
            else
            {
                Log.errorln("Buffer overflow, ignored: %X", character);
                m_received_start = false;
                break; // restart command
            }
        }
        else if (character == FEND)
        {
            Log.verboseln("Starting command collection");
            m_buffer_index = 0;
            m_received_start = true;
            m_received_type = false;
        }
        else
            Log.errorln("FEND is not first character of command");
    }
    return false;
}

/**
 * @brief Send message
 *
 * @return true successful
 * @return false error
 *
 */

bool RadioBoard::send_message(Message message) const
{
    auto command = message.get_command();
    auto content = message.get_content();
    if (content.length() == 0)
        Log.noticeln("Sending message: KISS command %X", command);
    else
        Log.noticeln("Sending message: KISS command %X, content: %s", command, content.c_str());
    Serial1.write(FEND);
    Serial1.write(command);
    Serial1.write(content.c_str());
    Serial1.write(FEND);
    return true;
}

/**
 * @brief Check for recent ground contact
 *
 */

bool RadioBoard::recent_ground_contact() const {
    return m_days_since_last_ground_contact <= ground_contact_interval;
}
