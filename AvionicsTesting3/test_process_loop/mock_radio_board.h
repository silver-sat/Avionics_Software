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
 * @brief Mock Radio Board for testing the Avionics Board
 * 
 */
class MockRadioBoard
{
public:
    MockRadioBoard();
    ~MockRadioBoard();

    /**
     * @brief initialize the Radio Board
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
     * @brief Process commands
     *
     * @return true no command or successful
     * @return false error
     */

    bool check_command();

    /**
     * @brief Check for command
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

private:
    String _buffer{};
    bool _end_of_line{false};
    const size_t _token_limit{10};
    CommandFactory *_factory{};
    Command *_command{};
    String _call_sign {"?????"}; // todo: replace with call sign
};

#endif // MOCK_RADIO_BOARD_H