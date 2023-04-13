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
     * @brief Notify radio board to deploy antenna via DigitalIO
     *
     */

    bool deploy_antenna();

    /**
     * @brief Assemble command or response from Serial1 port
     *
     */

    bool receive_frame(char *buffer, const size_t length, char &source);

    /**
     * @brief Send message
     *
     */

    bool send_message(const Message message) const;

private:
    size_t m_buffer_index{0};
    bool m_received_start{false};
    bool m_received_type{false};
    bool m_received_escape{false};
    bool m_remote_data{};
    long m_commands_received{0};
};