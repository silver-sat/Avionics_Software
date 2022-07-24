/**
 * @file mock_power_board.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test the Avionics Board mock Power Board
 * @version 1.0.0
 * @date 2022-07-24
 * 
 * 
 */

#include "mock_power_board.h"

MockPowerBoard::MockPowerBoard() {

}

MockPowerBoard::PowerStatus MockPowerBoard::get_power_status() {
    return MockPowerBoard::good;
}