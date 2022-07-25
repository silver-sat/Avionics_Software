/**
 * @file command.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat commands
 * @version 1.0.0
 * @date 2022-07-25
 *
 *
 */

#ifndef COMMAND_H
#define COMMAND_H

#include <Arduino.h>

class Command
{
public:
    /**
     * @brief command syntax
     *
     */
    enum operation
    {
        beacon_sp,
        s_call_sig,
        pay_comms,
        pic_times,
        report_t,
        no_operate,
        set_clock,
        twee_slee,
        watchdog,
        g_call_sig,
        invalid
    };

    union Value
    {
        int data;
        String string;
        int time[6];
        ~Value(){};
    };

    /**
     * @brief Construct a new Command object
     *
     * @param command operation
     * @param data parameters
     */

    Command(
        String command,
        Value parameter);

    /**
     * @brief Get the operation
     *
     * @return operation
     */

    operation get_operation();

    /**
     * @brief Get the parameters of the command
     *
     * @return the values sent by the ground station
     */

    Value get_values();

private:
    operation _action{invalid};
    Value _values{};
};

#endif