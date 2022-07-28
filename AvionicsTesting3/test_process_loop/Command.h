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

struct time_value
{
    int month;
    int day;
    int year;
    int hour;
    int minute;
    int second;
};

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

    operation get_operation();

    /**
     * @brief Create a command object with no parameters
     *
     * @param command action
     * @return Command* the new command
     */

    static Command *create_type1(String command);

    /**
     * @brief Create a command object with an integer parameter
     *
     * @param command action
     * @param parameter value
     * @return Command* the new command
     */

    static Command *create_type2(String command, int parameter);

    /**
     * @brief Create a type3 object
     *
     * @param command action
     * @param time value
     * @return Command* the new command
     */

    static Command *create_type3(String command, time_value time);

    /**
     * @brief Print the data
     * 
     */

    void acknowledge_command();

    /**
     * @brief Execute the command
     * 
     */

    bool execute_command();

protected:
    operation _action{invalid};
};

class Client
{
public:
    Client();
    Client(String command);
    Client(String command, int parameter);
    Client(String command, time_value time);
    ~Client();
    Command *get_command();

private:
    Command *_command;
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