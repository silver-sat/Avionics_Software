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
    size_t _command_index{10};
    CommandSetClock sc1 = CommandSetClock({2023, 1, 1, 10, 10, 0});
    CommandSetClock sc2 = CommandSetClock({2024, 1, 1, 10, 10, 0});
    CommandNoOperate no{};
    CommandBeaconSp bs1{10};
    CommandBeaconSp bs2{20};
    CommandUnknown un{};
    CommandInvalid in{};
    Command *_command_queue[10] = {&sc1, &no, &bs1, &no, &sc2, &no, &bs2, &no, &un, &in};

    // auto factory = new CommandFactory("BeaconSp", 10);
    // _factory = factory;
    // _command_ready = true;
    // return true;

    Command *_command1;
    Command *_command2;
};

#endif