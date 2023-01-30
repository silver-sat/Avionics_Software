/**
 * @file Commands.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat commands
 * @version 1.2.0
 * @date 2022-07-25
 *
 * Commands
 * 
 * BeaconSP: set beacon spacing
 * s_call_sig deprecated
 * PayComms: subsumes Begin tweet : start payload in comms mode
 * PicTimes: set times for photos
 * ReportT: subsumes GetTime: reply with realtime clock setting
 * NoOperate: subsumes Ping: acknowlege
 * SetClock: subsumes SetTime: set realtime clock
 * TweeSlee: subsumes Halt: stop tweeting
 * Watchdog: force watchdog timeout (reset SAMD21)
 * g_call_sig, deprecated
 * halt, see TweeSlee
 * GetPicTimes: reply with picture schedule
 * GetTelemetry: reply with telemetry
 * GetPower: reply with power status
 * GetPhotos: reply with number of photos
 * GetComms: reply with Radio Board status
 * GetBeaconInternal: reply with beacon interval
 * SendTestPacket: reply with test message
 * ClearPicTimes: empty PicTimes queue
 * UnsetClock: change the realtime clock status to unset for testing
 */

#pragma once

#include "RTClib.h"

/**
 * @brief Command implementation and processing
 *
 */

class Command
{
public:
    
    /**
     * @brief Destroy the Command object
     *
     */

    virtual ~Command() = default;

    /**
     * @brief Acknowlege the command
     *
     */

    virtual bool acknowledge_command();

    /**
     * @brief Negative acknowlege the command
     *
     */

    virtual bool negative_acknowledge_command();
    
    /**
     * @brief Execute the command
     *
     */

    virtual bool execute_command();

};

/**
 * @brief unknown command
 *
 */

class CommandUnknown final : public Command
{
public:
    CommandUnknown() = default;
    bool acknowledge_command() override;
    bool execute_command() override;
};

/**
 * @brief invalid command
 *
 */

class CommandInvalid final : public Command
{
public:
    CommandInvalid() = default;
    bool acknowledge_command() override;
    bool execute_command() override;
};

/**
 * @brief no_operate command
 *
 */

class CommandNoOperate final : public Command
{
public:
    CommandNoOperate() = default;
    bool acknowledge_command() override;
    bool execute_command() override;
};

/**
 * @brief pay_comms command
 *
 */

class CommandPayComms final : public Command
{
public:
    CommandPayComms() = default;
    bool acknowledge_command() override;
    bool execute_command() override;
};

/**
 * @brief report_t command
 *
 */

class CommandReportT final : public Command
{
public:
    CommandReportT() = default;
    bool acknowledge_command() override;
    bool execute_command() override;
};

/**
 * @brief twee_slee command
 *
 */

class CommandTweeSlee final : public Command
{
public:
    CommandTweeSlee() = default;
    bool acknowledge_command() override;
    bool execute_command() override;
};

/**
 * @brief watchdog command
 *
 */

class CommandWatchdog final : public Command
{
public:
    CommandWatchdog() = default;
    bool acknowledge_command() override;
    bool execute_command() override;
};

/**
 * @brief beacon_sp command
 *
 * @param seconds interval between beacons
 */

class CommandBeaconSp final : public Command
{
public:
    CommandBeaconSp(int seconds): m_seconds{seconds}{};
    bool acknowledge_command() override;
    bool execute_command() override;

private:
    int m_seconds;
};

/**
 * @brief pic_times command
 *
 * @param time photo time
 */

class CommandPicTimes final : public Command
{
public:
    CommandPicTimes(DateTime time): m_time{time}{};
    bool acknowledge_command() override;
    bool execute_command() override;

private:
    DateTime m_time;
};

/**
 * @brief set_clock command
 *
 * @param time UTC for real time clock
 */

class CommandSetClock final : public Command
{
public:
    CommandSetClock(DateTime time): m_time{time}{};
    bool acknowledge_command() override;
    bool execute_command() override;

private:
    DateTime m_time;
};

/**
 * @brief get_pic_times command
 *
 */

class CommandGetPicTimes final : public Command
{
public:
    CommandGetPicTimes() = default;
    bool acknowledge_command() override;
    bool execute_command() override;
};

/**
 * @brief get_telemetry command
 *
 */

class CommandGetTelemetry final : public Command
{
public:
    CommandGetTelemetry() = default;
    bool acknowledge_command() override;
    bool execute_command() override;
};

/**
 * @brief get_power command
 *
 */

class CommandGetPower final : public Command
{
public:
    CommandGetPower() = default;
    bool acknowledge_command() override;
    bool execute_command() override;
};

/**
 * @brief get_photos command
 *
 */

class CommandGetPhotos final : public Command
{
public:
    CommandGetPhotos() = default;
    bool acknowledge_command() override;
    bool execute_command() override;
};

/**
 * @brief get_comms command
 *
 */

class CommandGetComms final : public Command
{
public:
    CommandGetComms() = default;
    bool acknowledge_command() override;
    bool execute_command() override;
};

/**
 * @brief get_beacon_interval command
 *
 */

class CommandGetBeaconInterval final : public Command
{
public:
    CommandGetBeaconInterval() = default;
    bool acknowledge_command() override;
    bool execute_command() override;
};

/**
 * @brief send_test_packet command
 *
 */

class CommandSendTestPacket final : public Command
{
public:
    CommandSendTestPacket() = default;
    bool acknowledge_command() override;
    bool execute_command() override;
};

/**
 * @brief clear_pic_times command
 *
 */

class CommandClearPicTimes final : public Command
{
public:
    CommandClearPicTimes() = default;
    bool acknowledge_command() override;
    bool execute_command() override;
};

/**
 * @brief unset_clock command
 *
 */

class CommandUnsetClock final : public Command
{
public:
    CommandUnsetClock() = default;
    bool acknowledge_command() override;
    bool execute_command() override;
};