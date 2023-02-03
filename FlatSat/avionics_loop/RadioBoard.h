/**
 * @file RadioBoard.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat Radio Board
 * @version 1.2.0
 * @date 2022-07-24
 *
 *
 */

#pragma once

#include "Message.h"

/**
 * @brief KISS defined constants
 *
 */
// todo: consider changing case of constants
constexpr byte FEND{'\xC0'};       /**< frame end */
constexpr byte FESC{'\xDB'};       /**< frame escape */
constexpr byte TFEND{'\xDC'};      /**< transposed frame end */
constexpr byte TFESC{'\xDD'};      /**< transposed frame escape */
constexpr byte DATA_FRAME{'\x00'}; /**< data frame */

/**
 * @brief SilverSat defined KISS local command types
 *
 */
// todo: consider changing case of constants
constexpr byte DEPLOY_ANTENNA{'\x08'};    /**< deploy antenna */
constexpr byte GET_RADIO_STATUS{'\x09'};  /**< request radio status */
constexpr byte HALT('\x0A');              /**< halt */
constexpr byte SEND_RADIO_STATUS{'\x0B'}; /**< return radio status */

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
     * @brief Notify radio board to deploy antenna
     *
     */

    bool deploy_antenna();

    /**
     * @brief Assemble command from Serial1 port
     *
     */

    bool receive_command(char *buffer, const size_t length);

    /**
     * @brief Send message
     *
     */

    bool send_message(Message message);

    /**
     * @brief Get Radio Board status
     *
     */

    String get_status();

private:
    size_t m_buffer_index{0};
    bool m_received_start{false};
    bool m_receiving_type{false};
    bool m_received_escape{false};
    long m_commands_received{0};
};