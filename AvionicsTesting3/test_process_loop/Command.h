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

struct TimeValue
{
    int year;   /**< year */
    int month;  /**< month */
    int day;    /**< day */
    int hour;   /**< hour */
    int minute; /**< minute */
    int second; /**< second */
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
        beacon_sp, /*< BeaconSP: set beacon spacing */
        /* s_call_sig, deprecated */
        pay_comms,  /*< PayComms, subsumes Begin tweet : start payload in comms mode */
        pic_times,  /*< PicTimes: set times for photos */
        report_t,   /*< ReportT, subsumes GetTime: reply with realtime clock setting */
        no_operate, /*< NoOperate, subsumes Ping: acknowlege */
        set_clock,  /*< SetClock, subsumes SetTime: set realtime clock */
        twee_slee,  /*< TweeSlee, subsumes Halt: stop tweeting */
        watchdog,   /*< Watchdog: force watchdog timeout (reset SAMD21) */
        /* g_call_sig, deprecated */
        /* halt, see TweeSlee */
        get_pic_times,       /*< GetPicTimes: reply with picture schedule */
        get_telemetry,       /*< GetTelemetry: reply with telemetry */
        get_power,           /*< GetPower: reply with power status */
        get_photos,          /*< GetPhotos: reply with number of photos */
        get_comms,           /*< GetComms: reply with Radio Board status */
        get_beacon_interval, /*< GetBeaconInternal: reply with beacon interval */
        send_test_packet,    /*< SendTestPacket: reply with test message */
        unknown,             /*< Unknown: unknown command, error */
        invalid,             /*< Invalid: invalid command, error */
        /* testing commands */
        unset_clock, /*< UnsetClock: change the realtime clock status to unset for testing */
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
    /**
     * @brief Command operation
     *
     */
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
    bool acknowledge_command() override;
    bool execute_command() override;
};

/**
 * @brief watchdog command
 *
 */

class CommandWatchdog : public Command
{
public:
    CommandWatchdog();
    bool acknowledge_command() override;
    bool execute_command() override;
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
    CommandPicTimes(TimeValue time);
    bool acknowledge_command() override;
    bool execute_command() override;

private:
    TimeValue _time;
};

/**
 * @brief set_clock command
 *
 */

class CommandSetClock : public Command
{
public:
    CommandSetClock(TimeValue time);
    bool acknowledge_command() override;
    bool execute_command() override;

private:
    TimeValue _time;
};

/**
 * @brief get_pic_times command
 *
 */

class CommandGetPicTimes : public Command
{
public:
    CommandGetPicTimes();
    bool acknowledge_command() override;
    bool execute_command() override;
};

/**
 * @brief get_telemetry command
 *
 */

class CommandGetTelemetry : public Command
{
public:
    CommandGetTelemetry();
    bool acknowledge_command() override;
    bool execute_command() override;
};

/**
 * @brief get_power command
 *
 */

class CommandGetPower : public Command
{
public:
    CommandGetPower();
    bool acknowledge_command() override;
    bool execute_command() override;
};

/**
 * @brief get_photos command
 *
 */

class CommandGetPhotos : public Command
{
public:
    CommandGetPhotos();
    bool acknowledge_command() override;
    bool execute_command() override;
};

/**
 * @brief get_comms command
 *
 */

class CommandGetComms : public Command
{
public:
    CommandGetComms();
    bool acknowledge_command() override;
    bool execute_command() override;
};

/**
 * @brief get_beacon_interval command
 *
 */

class CommandGetBeaconInterval : public Command
{
public:
    CommandGetBeaconInterval();
    bool acknowledge_command() override;
    bool execute_command() override;
};

/**
 * @brief send_test_packet command
 *
 */

class CommandSendTestPacket : public Command
{
public:
    CommandSendTestPacket();
    bool acknowledge_command() override;
    bool execute_command() override;
};

/**
 * @brief unset_clock command
 *
 */

class CommandUnsetClock : public Command
{
public:
    CommandUnsetClock();
    bool acknowledge_command() override;
    bool execute_command() override;
};

#endif // COMMAND_H