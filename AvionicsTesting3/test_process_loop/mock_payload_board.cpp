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

MockPayloadBoard::MockPayloadBoard(){

};

/**
 * @brief Power down payload
 *
 */
void MockPayloadBoard::power_down(){
    // pinMode(PLD_ON_A, OUTPUT);
    // pinMode(PLD_ON_B, OUTPUT);
    // pinMode(PLD_ON_C, OUTPUT);
    // digitalWrite(PLD_ON_A, HIGH); // HIGH is off per Preliminary Design Package
    // digitalWrite(PLD_ON_B, HIGH);
    // digitalWrite(PLD_ON_C, HIGH);
};

/**
 * @brief Power up payload and take photo
 *
 */
void MockPayloadBoard::photo(){

};

/**
 * @brief Power up payload and tweet
 *
 */
void MockPayloadBoard::tweet(){

};

/**
 * @brief Check shutdown signal
 *
 */
bool MockPayloadBoard::power_down_signal()
{
    return false;
};
