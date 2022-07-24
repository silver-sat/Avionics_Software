/**
 * @file mock_payload_board.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test the Avionics Board mock Payload Board
 * @version 1.0.0
 * @date 2022-07-24
 * 
 * 
 */

#ifndef MOCK_PAYLOAD_BOARD_H
#define MOCK_PAYLOAD_BOARD_H

class MockPayloadBoard
{
public:
    MockPayloadBoard();
    
    /**
     * @brief Power down payload
     * 
     */
    void power_down();

    /**
     * @brief Power up payload and take photo
     * 
     */
    void photo();

    /**
     * @brief Power up payload and tweet
     * 
     */
    void tweet();

    /**
     * @brief Check shutdown signal
     * 
     */
    bool power_down_signal();

};

#endif