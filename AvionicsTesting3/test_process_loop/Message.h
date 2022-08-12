/**
 * @file Message.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Avionics outbound messages
 * @version 1.0.0
 * @date 2022-07-31
 *
 *
 */

#ifndef MESSAGE_H
#define MESSAGE_H

#include <Arduino.h>

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
        response,
        local_command,
        beacon, // reserved
        invalid,
    };

    /**
     * @brief Construct a new Message object
     *
     * @param header message type
     * @param content message body
     */

    Message(message_type header, String content);

    /**
     * @brief Get the message
     *
     * @return String
     */

    String get_message();

private:
    message_type _header{};
    String _content{};
};

#endif // MESSAGE_H