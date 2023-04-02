/**
 * @file Message.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat Avionics outbound messages
 * @version 2.0.0
 * @date 2022-07-31
 *
 * This file implements the outbound message class
 *
 */

#pragma once

#include "log_utility.h"
#include "avionics_constants.h"
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
        acknowledgement = REMOTE_FRAME,
        negative_acknowledgement = REMOTE_FRAME,
        response = REMOTE_FRAME,
        invalid = REMOTE_FRAME,
        beacon = BEACON,
        antenna_release = DIGITALIO_RELEASE,
        get_status = GET_RADIO_STATUS,
        halt = HALT,
        modify_frequency = MODIFY_FREQUENCY,
        modify_mode = MODIFY_MODE,
        adjust_frequency = ADJUST_FREQUENCY,
        transmit_cw = TRANSMIT_CW,
        background_rssi = BACKGROUND_RSSI,
        current_rssi = CURRENT_RSSI,
        sweep_tranmitter = SWEEP_TRANMSMITTER,
        sweep_receiver = SWEEP_RECEIVER,
        query_register = QUERY_REGISTER,
        // ping = 0x33, // todo: validate source from radio documentation
    };

    /**
     * @brief Construct a new Message object
     *
     */

    Message() = default;
    Message(message_type command, String content) : m_command{command}, m_content{content}{}

    /**
     * @brief Send message to Radio Board
     *
     * @return true
     * @return false
     *
     */

    // todo: consider adding a send method and replacing multiple calls
    // to the Radio Board send method

    /**
     * @brief Get the command
     *
     */

    message_type get_command() const { return m_command; }

    /**
     * @brief Get the content
     *
     */

    String get_content() const { return m_content; }

protected:
    message_type m_command{};
    String m_content{};
};