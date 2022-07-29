/**
 * @file mock_radio_board.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Mock Radio Board for Avionics testing
 * @version 1.0.1
 * @date 2022-07-24
 *
 *
 */

#ifndef MOCK_RADIO_BOARD_H
#define MOCK_RADIO_BOARD_H

#include "beacon.h"
#include "CommandFactory.h"
#include <Arduino.h>

class MockRadioBoard
{
public:
    MockRadioBoard();
    ~MockRadioBoard();

    /**
     * @brief initialize the connection
     *
     * @return true connection established
     * @return false error
     */

    bool begin();

    /**
     * @brief Send beacon
     *
     */

    void send_beacon(Beacon beacon);

    /**
     * @brief Check for command
     *
     */

    bool command_received();

    /**
     * @brief Get command
     *
     */

    Command *get_command();

private:
    bool _command_ready{false};
    CommandFactory *_factory{};
};

#endif