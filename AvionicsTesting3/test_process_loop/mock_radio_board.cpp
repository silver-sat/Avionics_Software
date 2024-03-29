/**
 * @file mock_radio_board.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Mock Radio Board for Avionics testing
 * @version 1.3.0
 * @date 2022-07-24
 *
 *
 */

#include "mock_radio_board.h"
#include "board_configuration.h"
#include "log_utility.h"
#include "AvionicsBoard.h"

/**
 * @brief Serial interface constant
 *
 */
constexpr uint32_t serial1_baud_rate{115200}; /**< speed of serial1 connection @hideinitializer */

/**
 * @brief initialize the Radio Board
 *
 * @return true successful
 * @return false error
 */

bool MockRadioBoard::begin()
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
    Log.traceln("Command port initialized");
    Serial1.write(FEND); // send initial sync to recover from incomplete message after board reset
    Serial1.write(FEND);
    return true;
}

/**
 * @brief Local command to deploy antenna
 *
 * @return true successful
 * @return false error
 */

bool MockRadioBoard::deploy_antenna()
{
    Log.traceln("Sending local command: deploy antenna");
    Serial1.write(FEND);
    Serial1.write(DEPLOY_ANTENNA);
    Serial1.write(FEND);
    return true;
}

/**
 * @brief Assemble command from Serial1 port
 *
 * @param buffer buffer to assemble command
 * @param length maximum length of command
 *
 * @return true no command or successful
 * @return false error
 */

bool MockRadioBoard::receive_command(char *buffer, const size_t length)
{

    while (Serial1.available())
    {
        char character = Serial1.read();
        if (m_received_start)
        {
            if (m_receiving_type)
            {
                if (character == FEND)
                {
                    Log.warningln("Unexpected FEND");
                    continue; // ignore additional FENDs
                }
                // todo: receive Radio Board status
                // todo: receive Radio Board "ACK + command"
                // todo: receive Radio Board "NACK + command"
                // todo: receive Radio Board "RES + data", success and fail
                m_receiving_type = false;

                if (character != DATA_FRAME)
                {
                    Log.errorln("Type is not 0: 0x%x", character);
                }
            }

            else if (m_received_escape)
            {
                m_received_escape = false;
                if (m_buffer_index < length)
                {
                    switch (character)
                    {
                    case TFEND:
                        buffer[m_buffer_index++] = FEND;
                        break;
                    case TFESC:
                        buffer[m_buffer_index++] = FESC;
                        break;
                    default:
                        Log.errorln("FESC followed by invalid character, ignored: 0x%x", character);
                        break;
                    }
                }
                else
                {
                    Log.errorln("Buffer overflow, ignored: 0x%x", character);
                }
            }

            else if (character == FESC)
            {
                m_received_escape = true;
            }

            else if (character == FEND)
            {
                // todo: receive radio board status
                if (m_buffer_index > header_size + 1)
                {
                    buffer[m_buffer_index++] = '\0';
                    memmove(buffer, buffer + header_size, m_buffer_index - header_size);
                    Log.infoln("Command received (count %l): %s", ++m_commands_received, buffer);
                    m_received_start = false;
                    return true;
                }
                else
                {
                    Log.errorln("No command received");
                }
            }

            else
            {
                if (m_buffer_index < length)
                {
                    buffer[m_buffer_index++] = character;
                }
                else
                {
                    Log.errorln("Buffer overflow, ignored: 0x%x", character);
                }
            }
        }
        else if (character == FEND)
        {
            m_buffer_index = 0;
            m_received_start = true;
            m_receiving_type = true;
        }
        else
        {
            Log.errorln("FEND is not first character of command: 0x%x", character);
        }
    }
    return false;
}

/**
 * @brief Send beacon
 *
 * @param beacon beacon data
 */

void MockRadioBoard::send_beacon(Beacon beacon)
{
    String beacon_data = call_sign + beacon.get_message();
    Log.noticeln("Sending local command: beacon %s", beacon.get_message().c_str());
    Serial1.write(FEND);
    Serial1.write(BEACON);
    Serial1.write(beacon_data.c_str());
    Serial1.write(FEND);
}

/**
 * @brief Send message
 *
 * @return true successful
 * @return false error
 */

bool MockRadioBoard::send_message(Message message)
{
    String message_data = message.get_message();
    Log.noticeln("Sending message: %s", message_data.c_str());
    Serial1.write(FEND);
    Serial1.write(DATA_FRAME);
    Serial1.write(HEADER, 16);
    Serial1.write(message_data.c_str());
    Serial1.write(FEND);
    return true;
}

/**
 * @brief Get Radio Board status
 *
 * @return String status
 */

String MockRadioBoard::get_status()
{
    Log.traceln("Sending local command: requesting Radio Board status");
    Serial1.write(FEND);
    Serial1.write(GET_RADIO_STATUS);
    Serial1.write(FEND);
    // todo: retrieve and store Radio Board status
    return "unknown";
}

/**
 * @brief Send halt local command
 *
 * @return true successful
 * @return false error
 */

bool MockRadioBoard::send_halt()
{
    Serial1.write(FEND);
    Serial1.write(HALT);
    Serial1.write(FEND);
    Log.traceln("Halt local command sent");
    return true;
}
