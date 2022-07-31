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

Message::Message(message_type header, String content) : _header{header}, _content{content} {};

/**
 * @brief Get the message
 *
 * @return String
 */

String Message::get_message()
{
    switch (_header)
    {
    case acknowledgement:
        return "A" + _content;

    case response:
        return "R" + _content;

    case local_command:
        return "L" + _content;

    case invalid:
        return "I" + _content;

    default:
        return "I" + _content;
    }
};