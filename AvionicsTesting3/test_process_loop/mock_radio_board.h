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
     * @brief command
     * 
     */
    struct command {
        byte content[256];
    };

    /**
     * @brief beacon
     * 
     */
    
    struct beacon {
        byte content[256];
    };
    
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
};

#endif