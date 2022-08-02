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

MockPowerBoard::MockPowerBoard()
{
}

String MockPowerBoard::get_power_status()
{

    // todo: open non-critical I2C bus, access power data from Power Board

    switch (_power_status)
    {
    case excellent:
        return "E";
    case good:
        return "G";
    case fair:
        return "F";
    case poor:
        return "P";
    case critical:
        return "C";
    default:
        return "?";
    };
}