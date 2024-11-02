/**
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat Radio Board
 *
 * The file declares the class that interfaces to the Radio Board
 *
 */

#pragma once

#include "avionics_constants.h"
#include "Message.h"

/**
 * @brief Frame data and length
 *
 */

struct Frame
{
    byte type{};
    String command{};
};

/**
 * @brief SilverSat Radio Board
 *
 */
class RadioBoard final
{
public:
    bool begin();
    bool receive_frame();
    Frame get_frame();
    bool send_message(const Message message) const;
    bool recent_ground_contact() const;
    bool test_radio();
private:
    void start_frame();
    void end_frame();
    void enter_escape_mode();
    void exit_escape_mode();
    bool add_character_to_buffer(char character);
    void ground_contact();
    bool get_frequency();
    size_t m_buffer_index{0};
    char m_buffer[maximum_command_length+1]{""};
    bool m_in_frame{false};
    bool m_received_escape{false};
    unsigned long m_milliseconds_since_last_ground_contact_day{0};
    long m_days_since_last_ground_contact{0};
};