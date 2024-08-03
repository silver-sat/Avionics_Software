/**
 * @file RadioBoard.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat Radio Board
 * @version 1.2.0
 * @date 2022-07-24
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

struct Frame {
    char *data{};
    size_t length{};
};

/**
 * @brief SilverSat Radio Board
 *
 */
class RadioBoard final
{
public:
    /**
     * @brief Initialize the Radio Board
     *
     */

    bool begin();

    /**
     * @brief Start new frame
     *
     */

    bool receive_frame();

    /**
     * @brief Get frame
     *
     */

    Frame get_frame();

    /**
     * @brief Send message
     *
     */

    bool send_message(const Message message) const;

    /**
     * @brief Check for recent ground contact
     *
     */

    bool recent_ground_contact() const;

private:
    void start_frame();

    /**
     * @brief End frame
     *
     */

    void end_frame();

    /**
     * @brief Enter escape mode
     *
     */

    void enter_escape_mode();

    /**
     * @brief Exit escape mode
     *
     */

    void exit_escape_mode();

    /**
     * @brief Add character to buffer
     *
     */

    bool add_character_to_buffer(char character);

    /**
     * @brief Gather frame from Serial1 port
     *
     */

    size_t m_buffer_index{0};
    char m_buffer[maximum_command_length]{""};
    bool m_in_frame{false};
    bool m_received_escape{false};
    unsigned long m_milliseconds_since_last_ground_contact_day{0};
    long m_days_since_last_ground_contact{0};
};