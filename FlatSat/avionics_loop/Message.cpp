/**
 * @file Message.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Avionics outbound messages
 * @version 1.0.0
 * @date 2022-07-31
 *
 *
 */

#include "Message.h"

/**
 * @brief Construct a new Message object
 *
 * @param header message type
 * @param content message body
 */

Message::Message(message_type header, String content) : m_header{header}, m_content{content} {};

/**
 * @brief Get the message
 *
 * @return String
 */

String Message::get_message()
{
    switch (m_header)
    {
    case acknowledgement:
        return "ACK" + m_content;

    case negative_acknowledgement:
        return "NACK" + m_content;

    case response:
        return "RES" + m_content;

    case invalid:
        return "INV" + m_content;

    default:
        return "INV" + m_content;
    }
};