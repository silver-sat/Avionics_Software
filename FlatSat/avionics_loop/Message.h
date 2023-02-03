/**
 * @file Message.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat Avionics outbound messages
 * @version 2.0.0
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
        acknowledgement = 0xAA,
        negative_acknowledgement = 0xAA,
        response = 0xAA,
        invalid = 0xAA,
        beacon = 0x07,
        antenna_release = 0x08,
        get_status = 0x09,
        halt = 0x0A,
        modify_frequency = 0x0B,
        modify_mode = 0x0C,
        adjust_frequency = 0x0D,
        transmit_cw = 0x17,
        background_rssi = 0x18,
        current_rssi = 0x19,
        sweep_tranmitter = 0x1A,
        sweep_receiver = 0x1B,
        query_register = 0x1C,
        ping = 0x33,
    };

    /**
     * @brief Construct a new Message object
     *
     */

    Message() = default;
    Message(message_type command, String content) : m_command{command}, m_content{content} {}

    /**
     * @brief Get the command
     *
     */

    message_type get_command() const {return m_command;}

    /**
     * @brief Get the content
     *
     */


    String get_content() const { return m_content; }

protected:
    message_type m_command{};
    String m_content{};
};