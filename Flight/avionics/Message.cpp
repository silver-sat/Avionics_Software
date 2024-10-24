/**
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat Avionics outbound messages
 *
 * This file implements the outbound message class
 *
 */

#include "RadioBoard.h"


    /**
     * @brief Send message via the Radio Board
     *
     * @return true success
     * @return false error
     *
     */

    bool Message::send() {
        extern RadioBoard radio;
        return radio.send_message(*this);
    }

    /**
     * @brief Get the command
     *
     */

    Message::Type Message::get_command() const { return m_command; }

    /**
     * @brief Get the content
     *
     */

    String Message::get_content() const { return m_content; }