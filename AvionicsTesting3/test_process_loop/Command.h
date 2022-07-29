/**
 * @file Command.h
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

/**
 * @brief date structure: month, day, year, hour, minute, second
 *
 */
struct time_value
{
    int month;
    int day;
    int year;
    int hour;
    int minute;
    int second;
};

/**
 * @brief Command structure and processing
 *
 */

class Command
{
public:
    /**
     * @brief Command operation
     *
     */

    enum operation
    {
        beacon_sp,
        // s_call_sig, deprecated
        pay_comms, // also Begin tweet
        pic_times,
        report_t,   // also GetTime
        no_operate, // also Ping
        set_clock,  // also SetTime
        twee_slee,  // also Halt
        watchdog,
        // g_call_sig, deprecated
        // halt, see TweeSlee
        get_pic_times,
        get_telemetry,
        get_power,
        get_photos,
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

    virtual operation get_operation();

    /**
     * @brief Print the data
     *
     */

    virtual void acknowledge_command();

    /**
     * @brief Execute the command
     *
     */

    virtual bool execute_command();

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
    virtual void acknowledge_command();
    virtual bool execute_command();
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

class CommandWatchdog : public Command
{
public:
    CommandWatchdog();
};

class CommandBeaconSp : public Command
{
public:
    CommandBeaconSp(int parameter);

private:
    int _value;
};

class CommandPicTimes : public Command
{
public:
    CommandPicTimes(time_value time);

private:
    time_value _time;
};

class CommandSetClock : public Command
{
public:
    CommandSetClock(time_value time);

private:
    time_value _time;
};

#endif