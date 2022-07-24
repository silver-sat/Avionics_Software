/**
 * @file mock_radio_board.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test the Avionics Board mock Radio Board
 * @version 1.0.0
 * @date 2022-07-24
 *
 *
 */

#ifndef MOCK_RADIO_BOARD_H
#define MOCK_RADIO_BOARD_H

class MockRadioBoard
{
public:
    MockRadioBoard();

    /**
     * @brief command layout
     *
     */
    struct command
    {
        byte content[256];
    };

    /**
     * @brief beacon layout
     *
     */

    struct beacon
    {
        byte content[256];
    };

    /**
     * @brief Check for command
     *
     */

    bool command_received();

    /**
     * @brief Get command
     *
     */

    command get_command();

    /**
     * @brief Send beacon
     *
     */

    void send_beacon(beacon);

private:
    bool _is_command{false};
    command _command{"test command"};
};

#endif