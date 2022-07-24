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

#include <Arduino.h>

class MockRadioBoard
{
public:
    MockRadioBoard();

    /**
     * @brief command layout
     *
     */

    // todo: create structure for command layout
    using command = String;
    // struct command
    // {
    //     String content{"test command"};
    // };

    /**
     * @brief beacon layout
     *
     */

    // todo: create structure for beacon layout
    using beacon = String;
    // struct beacon
    // {
    //     String content{"test beacon"};
    // };

    /**
     * @brief Check for command
     *
     */

    bool command_received();

    /**
     * @brief Get command
     *
     */

    String get_command();

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