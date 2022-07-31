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

#define COMMAND_QUEUE_SIZE 15

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
    unsigned long _last_command_time{0};
    unsigned long _command_interval{10 * 1000 * 1000};
    CommandSetClock sc1 = CommandSetClock({2023, 1, 1, 10, 10, 0});
    CommandSetClock sc2 = CommandSetClock({2024, 1, 1, 10, 10, 0});
    CommandNoOperate no{};
    CommandBeaconSp bs1{10};
    CommandBeaconSp bs2{20};
    CommandUnknown un{};
    CommandInvalid in{};
    CommandPayComms pc{};
    CommandPicTimes pt1 = CommandPicTimes({2023, 1, 1, 10, 10, 30});
    CommandPicTimes pt2 = CommandPicTimes({2023, 1, 1, 10, 15, 30});
    size_t _command_index{COMMAND_QUEUE_SIZE};
    Command *_command_queue[COMMAND_QUEUE_SIZE] = {
        &sc1,
        &pt1,
        &bs2,
        &no,
        &no,
        &no,
        &no,
        &pc,
        &pt2,
        &no,
        &no,
        &no,
        &pc,
        &no,
        &no,
    };
};

#endif