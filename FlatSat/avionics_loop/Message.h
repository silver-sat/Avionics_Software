/**
 * @file Message.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat Avionics outbound messages
 * @version 1.0.0
 * @date 2022-07-31
 *
 *
 */

#pragma once

#include <Arduino.h>

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

    enum message_type
    {
        acknowledgement,
        negative_acknowledgement,
        response,
        invalid,
    };

    /**
     * @brief Construct a new Message object
     *
     */

    Message(message_type header, String content);

    /**
     * @brief Get the message
     *
     */

    String get_message();

private:
    message_type m_header{};
    String m_content{};
};