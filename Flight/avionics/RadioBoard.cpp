/**
 * @author Lee A. Congdon (lee@silversat.org)
 * @author Benjamin S. Cohen (ben@silversat.org)
 * @brief SilverSat Radio
 *
 * This file implements the class that interfaces to the Radio Board
 *
 */

#include "RadioBoard.h"
#include "avionics_constants.h"
#include "log_utility.h"
#include "AvionicsBoard.h"
#include "Antenna.h"

/**
 * @brief Radio Board constants
 *
 */

constexpr uint32_t serial1_baud_rate{19200};                                                        /**< speed of serial1 connection @hideinitializer */
constexpr unsigned long radio_delay{2 * seconds_to_milliseconds};                                   /**< Radio Board startup delay */
constexpr long ground_contact_interval{7};                                                          /**< maximum days without ground contact for beacon @hideinitializer */
constexpr unsigned long frequency_entry_timeout = 30 * seconds_to_milliseconds; /**< User frequency entry delay */

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

    // Optionally set the frequency for the Radio Board

    get_frequency();

    // Send invalid command to Radio Board to determine if it is responding

    Log.verboseln("Sending invalid command to Radio Board");
    Message message(Message::local_command, "Invalid");
    message.send();

    // Read radio response

    auto response_length{Serial1.readBytes(m_buffer, maximum_command_length)};
    for (auto i{0}; i < static_cast<int>(response_length); ++i)
    {
        Log.verboseln("Radio response: %C", m_buffer[i]);
    }
    if (response_length > 0)
    {
        Log.verboseln("Command port initialized");
        return true;
    }
    Log.errorln("Radio Board did not respond");
    return false;
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
        Log.verboseln("Character received on Serial1 port: %C", character);
        switch (character)
        {
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
    m_buffer[m_buffer_index] = '\0';
    Frame frame{};
    frame.type = m_buffer[0];
    frame.command = String{m_buffer + 1};
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
    {
        Log.noticeln("Sending message: KISS command %X", command);
    }
    else
    {
        Log.noticeln("Sending message: KISS command %X, content: %s", command, content.c_str());
    }
    extern Antenna antenna;

    // supress message to ground if antenna deployment cycle not complete

    if (command == REMOTE_FRAME && !antenna.antenna_cycle_completed())
    {
        Log.warningln("Antenna deployment cycle not complete, remote message not sent");
        return false;
    }

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

/**
 * @brief Get frequency for the Radio Board
 *
 */

bool RadioBoard::get_frequency()
{
    unsigned long start_time = millis();
    char incoming_char = 0;
    String frequency_string_1 = "";
    String frequency_string = "";
    extern AvionicsBoard avionics;

    Serial.print("Enter the 9-digit frequency string (e.g., 123456789): ");

    while (millis() - start_time < frequency_entry_timeout)
    {
        avionics.service_watchdog(); // service the watchdog while waiting
        if (Serial.available() > 0)
        {
            incoming_char = Serial.read();
            if (!isDigit(incoming_char))
            {
                Serial.write(BELL);
                continue;
            }
            Serial.write(incoming_char);
            frequency_string += incoming_char;
            if (frequency_string.length() == 9)
            {
                Serial.println();
                Message message(Message::modify_frequency, frequency_string);
                message.send();
                message.send(); // send twice to make permanent change
                String display_frequency{};
                display_frequency += frequency_string.substring(0, 6);
                display_frequency += ".";
                display_frequency += frequency_string.substring(6, 9);
                Log.noticeln("Frequency set to %s", display_frequency.c_str());
                return true;
            }
        }
    }
    Serial.println();
    Log.noticeln("Timeout during frequency entry");
    return false;
}

/**
 * @brief Test Radio Board
 *
 */

bool RadioBoard::test_radio()
{
    Log.noticeln("Testing Radio Board");
    Message message(Message::get_status, "");
    message.send();
    return true;
}
