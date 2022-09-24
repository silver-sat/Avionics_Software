/**
 * @file mock_radio_board.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Mock Radio Board for Avionics testing
 * @version 1.1.0
 * @date 2022-07-24
 *
 *
 */

#ifndef MOCK_RADIO_BOARD_H
#define MOCK_RADIO_BOARD_H

#include "Beacon.h"
#include "Message.h"
#include "CommandFactory.h"

/**
 * @brief KISS defined constants
 *
 */
constexpr byte FEND{'\xC0'};
constexpr byte FESC{'\xDB'};
constexpr byte TFEND{'\xDC'};
constexpr byte TFESC{'\xDD'};
constexpr byte DATA_FRAME{'\x00'};

/**
 * @brief SilverSat defined KISS local command types
 *
 */
constexpr byte BEACON{'\x07'};
constexpr byte DEPLOY_ANTENNA{'\x08'};
constexpr byte GET_RADIO_STATUS{'\x09'};
constexpr byte HALT('\x0A');

/**
 * @brief Dummy AX.25 header
 *
 */

constexpr byte HEADER[]{0x88, 0x40, 0x40, 0x40, 0x40, 0x40, 0xE0, 0xA6,
                        0x40, 0x40, 0x40, 0x40, 0x40, 0xE1, 0x30, 0xF0};
constexpr size_t header_size{sizeof(HEADER)};

/**
 * @brief Command parameters
 *
 */

constexpr char _command_message_separator{'|'};
constexpr size_t _buffer_token_limit{4};
constexpr size_t _maximum_sequence_length{10};
constexpr size_t _maximum_command_length{200};
constexpr size_t _command_token_limit{10};
constexpr size_t _salt_size{16};
constexpr size_t _secret_size{16};
constexpr size_t _HMAC_size{32};

/**
 * @brief Amateur radio call sign
 *
 */

const String _call_sign{"KC3CQJ"};

/**
 * @brief Mock Radio Board for testing the Avionics Board
 *
 */
class MockRadioBoard
{
public:
    MockRadioBoard();
    ~MockRadioBoard();

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
     * @brief Check for command
     *
     * @return true no command or successful
     * @return false error
     */

    bool check_for_command();

    /**
     * @brief Assemble command from Serial1 port
     *
     * @return true no command or successful
     * @return false error
     */

    bool command_received();

    /**
     * @brief Get command
     *
     * @return next command to process
     */

    Command *get_command();

    /**
     * @brief Parse command parameters
     *
     * @param command_string command string
     * @param command_tokens output: tokens
     * @param token_count output: number of tokens
     * @return true successful
     * @return false failure
     */

    bool parse_parameters(const String &command_string, String command_tokens[], size_t &token_index);

    /**
     * @brief Validate the commmand signature
     *
     * @param buffer sequence, salt, command and HMAC
     * @param command_string output: command and parameters
     * @return true if valid
     * @return false if invalid
     */

    bool validate_signature(String &buffer, String &command_string);

    /**
     * @brief Make a command
     *
     * @param buffer input string
     * @return true successful
     * @return false error
     */

    bool make_command(String buffer);

    /**
     * @brief Send beacon
     *
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
    String _buffer{};
    bool _received_start{false};
    bool _receiving_type{false};
    bool _received_escape{false};
    bool _validation_required{false};
    CommandFactory *_factory{};
    Command *_command{};
    long _commands_received{0};
    long _successful_commands{0};
    long _failed_commands{0};
    long _command_sequence{1};
};

#endif // MOCK_RADIO_BOARD_H