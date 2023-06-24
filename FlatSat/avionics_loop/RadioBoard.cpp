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
constexpr byte FEND{'\xC0'};                 /**< frame end */
constexpr byte FESC{'\xDB'};                 /**< frame escape */
constexpr byte TFEND{'\xDC'};                /**< transposed frame end */
constexpr byte TFESC{'\xDD'};                /**< transposed frame escape */

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
    Serial1.write(FEND); // send initial sync to recover from incomplete message after board reset
    Serial1.write(FEND);
    return true;
}

/**
 * @brief Local command to deploy antenna
 *
 * @return true successful
 * @return false error
 *
 */

bool RadioBoard::deploy_antenna()
{
    Log.traceln("Sending local command: deploy antenna");
    Serial1.write(FEND);
    Serial1.write(DIGITALIO_RELEASE);
    Serial1.write(FEND);
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
    while (Serial1.available())
    {
        char character{static_cast<char>(Serial1.read())};
        // Caution: enabling character logging will cause non-printable characters to interfere with automated tests
        // Log.verboseln("Character received: 0x%x", character);
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
                if (m_buffer_index > 0)
                {
                    buffer[m_buffer_index++] = '\0';
                    if (source == REMOTE_FRAME)
                        Log.infoln("Command received (count %l): %s", ++m_commands_received, buffer);
                    else
                    {
                        char reply[RES.length() + 1]; // allow space for reply plus null
                        memcpy(reply, buffer, RES.length());
                        reply[RES.length()] = '\0';
                        byte command{buffer[RES.length()]};
                        // todo: consider logging additional data if it exists
                        Log.infoln("Local message received: %s %X", reply, command);
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