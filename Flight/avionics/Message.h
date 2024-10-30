/**
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat Avionics outbound messages
 *
 * This file implements the outbound message class
 *
 */

#pragma once

#include "avionics_constants.h"

/**
 * @brief Messages sent by the Avionics Board
 *
 */

class Message
{
public:

    /**
     * @brief message types
     *
     */
    enum Type
    {
        local_command = LOCAL_FRAME,
        acknowledgement = REMOTE_FRAME,
        negative_acknowledgement = REMOTE_FRAME,
        response = REMOTE_FRAME,
        invalid = REMOTE_FRAME,
        beacon = BEACON,
        antenna_release = DIGITALIO_RELEASE,
        get_status = GET_RADIO_STATUS,
        halt = HALT,
        modify_frequency = MODIFY_FREQUENCY,
        background_rssi = BACKGROUND_RSSI,
        current_rssi = CURRENT_RSSI,
    };

    /**
     * @brief Construct a new Message object
     *
     */

    Message() = default;
    Message(Type command, String content) : m_command{command}, m_content{content} {}

    /**
     * @brief Send message via the Radio Board
     *
     * @return true success
     * @return false error
     *
     */

    bool send();

    /**
     * @brief Get the command
     *
     */

    Type get_command() const;

    /**
     * @brief Get the content
     *
     */

    String get_content() const;

protected:
    Type m_command{};
    String m_content{};
};