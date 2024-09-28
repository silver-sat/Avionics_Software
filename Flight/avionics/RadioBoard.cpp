/**
 * @file RadioBoard.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @author Benjamin S. Cohen (ben@silversat.org)
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

constexpr uint32_t serial1_baud_rate{19200}; /**< speed of serial1 connection @hideinitializer */
constexpr unsigned long radio_delay{2 * seconds_to_milliseconds};
constexpr long ground_contact_interval{7}; /**< maximum days without ground contact for beacon @hideinitializer */

/**
 * @brief Initialize the Radio Board
 *
 * @return true successful
 * @return false error
 *
 */

bool RadioBoard::begin()
{
    // Enable serial driver to Radio Board
    Log.traceln("Radio Board initializing");
    Log.verboseln("Enabling serial driver to Radio Board at %d baud", serial1_baud_rate);
    pinMode(EN_RADIO_SERIAL, OUTPUT);
    digitalWrite(EN_RADIO_SERIAL, HIGH);
    // Initialize command port
    Log.verboseln("Initializing command port");
    Serial1.begin(serial1_baud_rate);
    extern AvionicsBoard avionics;
    while (!Serial1)
    {
        avionics.service_watchdog();
    }
    // Send abort transaction to Radio Board to clear buffer
    Log.verboseln("Sending abort transaction to Radio Board");
    Serial1.write(FESC);
    Serial1.write(FESC);
    // Wait for Radio Board to initialize
    Log.verboseln("Waiting for Radio Board to initialize");
    unsigned long serial_delay_start{millis()};
    while ((millis() - serial_delay_start) < radio_delay)
    {
        avionics.service_watchdog();
    }
    // Send invalid command to Radio Board to determine if it is responding
    Log.verboseln("Sending invalid command to Radio Board");
    Serial1.write(FEND);
    Serial1.write(LOCAL_FRAME);
    Serial1.write("Invalid");
    Serial1.write(FEND);
    // Read radio response
    auto response_length{Serial1.readBytes(m_buffer, maximum_command_length)};
    for (auto i{0}; i < response_length; ++i)
    {
        Log.verboseln("Radio response: %X", m_buffer[i]);
    }
    if (response_length > 0)
    {
        Log.verboseln("Command port initialized");
        return true;
    }
    else
    {
        Log.errorln("Radio Board did not respond");
        return false;
    }
}

/**
 * @brief Gather frame from Serial1 port
 *
 * @return true frame received
 * @return false no frame or error
 *
 */

bool RadioBoard::receive_frame()
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
        auto character{static_cast<char>(Serial1.read())};
        Log.verboseln("Character received on Serial1 port: %X", character);
        switch (character)
        {
        // case FEND
        case FEND:
            // Not in frame, start frame
            if (!m_in_frame)
            {
                start_frame();
            }
            // In frame and data captured, process end of frame
            else if (m_buffer_index > 0)
            {
                end_frame();
                ground_contact();
                return true;
            }
            // In frame and no data captured, ignore subsequent FEND
            else
            {
                Log.noticeln("Additional FEND received, ignored");
            }
            break;
        // case FESC
        case FESC:
            // Not in frame, error
            if (!m_in_frame)
            {
                Log.warningln("FESC received outside of frame, ignored");
            }
            // Two sequential FESCs, abort frame
            else if (m_received_escape)
            {
                Log.errorln("Two FESCs in sequence, frame ignored");
                end_frame();
            }
            // Process escape character
            else
            {
                enter_escape_mode();
            }
            break;
        // case TFEND
        case TFEND:
            // Not in frame, error
            if (!m_in_frame)
            {
                Log.warningln("TFEND received outside of frame, ignored");
            }
            // Not in escape mode, add to buffer
            else if (!m_received_escape)
            {
                add_character_to_buffer(TFEND);
            }
            // In escape mode, add escaped character to buffer
            else
            {
                add_character_to_buffer(FEND);
                exit_escape_mode();
            }
            break;
        // case TFESC
        case TFESC:
            // Not in frame, error
            if (!m_in_frame)
            {
                Log.warningln("TFESC received outside of frame, ignored");
            }
            // Not in escape mode, add to buffer
            else if (!m_received_escape)
            {
                add_character_to_buffer(TFESC);
            }
            // In escape mode, process escape character
            else
            {
                add_character_to_buffer(FESC);
                exit_escape_mode();
            }
            break;
            // case other
        default:
            // Not in frame, error
            if (!m_in_frame)
            {
                Log.errorln("Data received outside of frame, ignored: %X", character);
            }
            // Escape received, must be TFEND or TFESC case, else error
            else if (m_received_escape)
            {
                Log.errorln("Invalid escaped character, character ignored: %X", character);
                exit_escape_mode();
            }
            // if in frame, add character to buffer and increment index
            else
            {
                add_character_to_buffer(character);
            }
            break;
        }
    }
    return false;
}
/**
 * @brief Get frame
 *
 * @return data from last radio frame
 *
 * @note must be called after receive_frame() returns true and before next receive_frame() call
 *
 */

Frame RadioBoard::get_frame()
{
    // Log.verboseln("Received frame has length: %l", m_buffer_index);
    Frame frame;
    frame.data = m_buffer;
    frame.length = m_buffer_index;
    // Log.verboseln("Frame data[0]: %X", frame.data[0]);
    // Log.verboseln("Returning frame with length: %l", frame.length);
    return frame;
}

/**
 * @brief Send message
 *
 * @return true successful
 * @return false error
 *
 */

bool RadioBoard::send_message(const Message message) const
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
 * @return true recent ground contact
 * @return false no recent ground contact
 *
 */

bool RadioBoard::recent_ground_contact() const
{
    return m_days_since_last_ground_contact <= ground_contact_interval;
}

/**
 * @brief Start new frame
 *
 */

void RadioBoard::start_frame()
{
    m_in_frame = true;
    m_buffer_index = 0;
}

/**
 * @brief End frame
 *
 */

void RadioBoard::end_frame()
{
    m_in_frame = false;
}

/**
 * @brief Enter escape mode
 *
 */

void RadioBoard::enter_escape_mode()
{
    m_received_escape = true;
}

/**
 * @brief Exit escape mode
 *
 */

void RadioBoard::exit_escape_mode()
{
    m_received_escape = false;
}

/**
 * @brief Add character to buffer
 *
 * @param character character to add
 * @return true character added
 * @return false error
 *
 */

bool RadioBoard::add_character_to_buffer(char character)
{
    if (m_buffer_index < maximum_command_length)
    {
        m_buffer[m_buffer_index++] = character;
        return true;
    }
    else
    {
        Log.errorln("Overflow character in radio frame: %X, ignored", character);
        return false;
    }
}

/**
 * @brief Record ground contact
 *
 */

void RadioBoard::ground_contact()
{
    m_milliseconds_since_last_ground_contact_day = millis();
    m_days_since_last_ground_contact = 0;
}