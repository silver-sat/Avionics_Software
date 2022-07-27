/**
 * @file command.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat commands
 * @version 1.0.1
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
        // s_call_sig, deprecated
        pay_comms,  // also begin tweet
        pic_times,  // one time to start
        report_t,   // also GetTime
        no_operate, // also Ping
        set_clock,  // also SetTime
        twee_slee,  // also halt
        watchdog,
        // g_call_sig, deprecated
        // halt, see TweeSlee
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
     * @brief Construct a new Command object
     *
     */

    Command();

    /**
     * @brief Construct a new Command object with no parameters
     *
     * @param command operation
     *
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
     * @brief Construct a command object
     *
     * @param command
     */

    static Command *create(String command);

protected:
    operation _action{invalid};
};

/**
 * @brief unknown command
 *
 */

class CommandUnknown : public Command
{
public:
    CommandUnknown();
};

class CommandInvalid : public Command
{
public:
    CommandInvalid();
};

class CommandNoOperate : public Command
{
public:
    CommandNoOperate();
};

class CommandPayComms : public Command
{
public:
    CommandPayComms();
};

class CommandReportT : public Command
{
public:
    CommandReportT();
};

class CommandTweeSlee : public Command
{
public:
    CommandTweeSlee();
};

#endif