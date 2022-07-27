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
    union Value {
        int int_value;
        char char_value[10];
        double double_value;
    };

    enum operation
    {
        beacon_sp,
        // s_call_sig, deprecated
        pay_comms, // also begin tweet
        pic_times, // one time to start
        report_t, // also GetTime
        no_operate, // also Ping
        set_clock, // also SetTime
        twee_slee,
        watchdog,
        // g_call_sig, deprecated
        halt, // formerly TweeSlee
        get_pic_times, 
        get_telemetry,
        get_power,
        get_photos, // count
        get_comms,
        get_beacon_interval,
        sent_test_packet,
        unknown,
        invalid,
    };

    /**
     * @brief Construct a new default Command object
     * 
     */
    Command();

    /**
     * @brief Construct a new Command object with no parameters
     *
     * @param command operation
     * @param data parameters
     */

    Command(
        String command);

    /**
     * @brief Get the operation
     *
     * @return operation
     */

    operation get_operation();

    /**
     * @brief Get the parameters
     *
     * @return the parameters sent by the ground station
     */

    Value get_values();

private:
    operation _action{invalid};
    Value _value{};
};

#endif