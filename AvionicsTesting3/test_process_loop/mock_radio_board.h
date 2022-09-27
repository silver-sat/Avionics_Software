/**
 * @file mock_radio_board.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Mock Radio Board for Avionics testing
 * @version 1.2.0
 * @date 2022-07-24
 *
 *
 */

#ifndef MOCK_RADIO_BOARD_H
#define MOCK_RADIO_BOARD_H

#include "Beacon.h"
#include "Message.h"

/**
 * @brief KISS defined constants
 *
 */
constexpr byte FEND{'\xC0'};       /**< frame end */
constexpr byte FESC{'\xDB'};       /**< frame escape */
constexpr byte TFEND{'\xDC'};      /**< transposed frame end */
constexpr byte TFESC{'\xDD'};      /**< transposed frame escape */
constexpr byte DATA_FRAME{'\x00'}; /**< data frame */

/**
 * @brief SilverSat defined KISS local command types
 *
 */
constexpr byte BEACON{'\x07'};           /**< send a beacon */
constexpr byte DEPLOY_ANTENNA{'\x08'};   /**< deploy antenna */
constexpr byte GET_RADIO_STATUS{'\x09'}; /**< return radio status */
constexpr byte HALT('\x0A');             /**< halt */

/**
 * @brief Dummy AX.25 header
 *
 */

constexpr byte HEADER[]{0x96, 0x86, 0x66, 0x86, 0xa2, 0x94, 0xe0, 0x96,
                        0x86, 0x66, 0x86, 0xa2, 0x94, 0xe5, 0x03, 0xf0}; /**< dummy AX.25 header */
constexpr size_t header_size{sizeof(HEADER)};                            /**< AX.25 header size */

/**
 * @brief Amateur radio call sign
 *
 */

const String _call_sign{"KC3CQJ-2"};

/**
 * @brief Mock Radio Board for testing the Avionics Board
 *
 */
class MockRadioBoard
{
public:
    /**
     * @brief Initialize the Radio Board
     *
     * @return true successful
     * @return false error
     */

    bool begin();

    /**
     * @brief Notify radio board to deploy antenna
     *
     * @return true successful
     * @return false error
     */

    bool deploy_antenna();

    /**
     * @brief Assemble command from Serial1 port
     *
     * @param buffer buffer to assemble command
     * @param length maximum length of command
     * 
     * @return true no command or successful
     * @return false error
     */

    bool receive_command(char *buffer, const size_t length);

    /**
     * @brief Send beacon
     *
     * @param beacon beacon data 
     */

    void send_beacon(Beacon beacon);

    /**
     * @brief Send message
     *
     * @return true successful
     * @return false error
     */

    bool send_message(Message message);

    /**
     * @brief Get Radio Board status
     *
     * @return Beacon::status status
     */

    String get_status();

private:
    size_t _buffer_index{0};
    bool _received_start{false};
    bool _receiving_type{false};
    bool _received_escape{false};
    long _commands_received{0};
};

#endif // MOCK_RADIO_BOARD_H