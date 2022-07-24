/**
 * @file mock_payload_board.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test the Avionics Board mock Payload Board
 * @version 1.0.0
 * @date 2022-07-24
 * 
 * 
 */

#include "mock_payload_board.h"

class MockPayloadBoard
{
public:
    MockPayloadBoard::MockPayloadBoard() {

    };
    
    /**
     * @brief Power down payload
     * 
     */
    void MockPayloadBoard::power_down();

    /**
     * @brief Power up payload and take photo
     * 
     */
    void MockPayloadBoard::photo();

    /**
     * @brief Power up payload and tweet
     * 
     */
    void MockPayloadBoard::tweet();

    /**
     * @brief Check shutdown signal
     * 
     */
    bool MockPayloadBoard::power_down_signal();

};

#endif