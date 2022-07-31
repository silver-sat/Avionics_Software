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
 * @brief date structure: UTC year, month, day, hour, minute, second
 *
 */

struct time_value
{
    int year;
    int month;
    int day;
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
        invalid
    };

    /**
     * @brief Construct a new Command object
     *
     */

    Command();

    /**
     * @brief Get the operation
     *
     * @return operation
     */

    virtual operation get_operation();

    /**
     * @brief Acknowlege the command
     *
     */

    virtual bool acknowledge_command();

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
    bool acknowledge_command() override;
    bool execute_command() override;
};

/**
 * @brief invalid command
 *
 */

class CommandInvalid : public Command
{
public:
    CommandInvalid();
    bool acknowledge_command() override;
    bool execute_command() override;
};

/**
 * @brief no_operate command
 *
 */

class CommandNoOperate : public Command
{
public:
    CommandNoOperate();
    bool acknowledge_command() override;
    bool execute_command() override;
};

/**
 * @brief pay_comms command
 *
 */

class CommandPayComms : public Command
{
public:
    CommandPayComms();
    bool acknowledge_command() override;
    bool execute_command() override;
};

/**
 * @brief report_t command
 *
 */

class CommandReportT : public Command
{
public:
    CommandReportT();
    bool acknowledge_command() override;
    bool execute_command() override;
};

/**
 * @brief twee_slee command
 *
 */

class CommandTweeSlee : public Command
{
public:
    CommandTweeSlee();
};

/**
 * @brief watchdog command
 *
 */

class CommandWatchdog : public Command
{
public:
    CommandWatchdog();
};

/**
 * @brief beacon_sp command
 *
 */

class CommandBeaconSp : public Command
{
public:
    CommandBeaconSp(int seconds);
    bool acknowledge_command() override;
    bool execute_command() override;

private:
    int _seconds;
};

/**
 * @brief pic_times command
 *
 */

class CommandPicTimes : public Command
{
public:
    CommandPicTimes(time_value time);
    bool acknowledge_command() override;
    bool execute_command() override;

private:
    time_value _time;
};

/**
 * @brief set_clock command
 *
 */

class CommandSetClock : public Command
{
public:
    CommandSetClock(time_value time);
    bool acknowledge_command() override;
    bool execute_command() override;

private:
    time_value _time;
};

#endif