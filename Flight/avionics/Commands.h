/**
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat commands
 *
 * This file declares all Command objects. Each ground command object is derived
 * from the Command class.
 *
 */

#pragma once

#include "avionics_constants.h"
#include "RTClib.h"

class Command
{
public:
    virtual ~Command() = default;
    virtual bool acknowledge_command();
    virtual bool negative_acknowledge_command();
    virtual bool execute_command();
};

class CommandSetClock final : public Command
{
public:
    explicit CommandSetClock(const DateTime time) : m_time{time} {};
    bool acknowledge_command() override;
    bool execute_command() override;
    void time(const DateTime time) { m_time = time; }
private:
    DateTime m_time;
};

class CommandBeaconSp final : public Command
{
public:
    explicit CommandBeaconSp(const int seconds) : m_seconds{seconds} {};
    bool acknowledge_command() override;
    bool execute_command() override;
    void seconds(const int seconds) { m_seconds = seconds; }
private:
    int m_seconds;
};

class CommandPicTimes final : public Command
{
public:
    explicit CommandPicTimes(const DateTime time) : m_time{time} {};
    bool acknowledge_command() override;
    bool execute_command() override;
    void time(const DateTime time) { m_time = time; }
private:
    DateTime m_time;
};

class CommandSSDVTimes final : public Command
{
public:
    explicit CommandSSDVTimes(const DateTime time) : m_time{time} {};
    bool acknowledge_command() override;
    bool execute_command() override;
    void time(const DateTime time) { m_time = time; }
private:
    DateTime m_time;
};

class CommandClearPayloadQueue final : public Command
{
public:
    CommandClearPayloadQueue() = default;
    bool acknowledge_command() override;
    bool execute_command() override;
};

class CommandUnsetClock final : public Command
{
public:
    CommandUnsetClock() = default;
    bool acknowledge_command() override;
    bool execute_command() override;
};

class CommandReportT final : public Command
{
public:
    CommandReportT() = default;
    bool acknowledge_command() override;
    bool execute_command() override;
};

class CommandGetPayloadQueue final : public Command
{
public:
    CommandGetPayloadQueue() = default;
    bool acknowledge_command() override;
    bool execute_command() override;
};

class CommandGetTelemetry final : public Command
{
public:
    CommandGetTelemetry() = default;
    bool acknowledge_command() override;
    bool execute_command() override;
};

class CommandGetPower final : public Command
{
public:
    CommandGetPower() = default;
    bool acknowledge_command() override;
    bool execute_command() override;
};

class CommandGetComms final : public Command
{
public:
    CommandGetComms() = default;
    bool acknowledge_command() override;
    bool execute_command() override;
};

class CommandGetBeaconInterval final : public Command
{
public:
    CommandGetBeaconInterval() = default;
    bool acknowledge_command() override;
    bool execute_command() override;
};

class CommandNoOperate final : public Command
{
public:
    CommandNoOperate() = default;
    bool acknowledge_command() override;
    bool execute_command() override;
};

class CommandSendTestPacket final : public Command
{
public:
    CommandSendTestPacket() = default;
    bool acknowledge_command() override;
    bool execute_command() override;
};

class CommandPayComms final : public Command
{
public:
    CommandPayComms() = default;
    bool acknowledge_command() override;
    bool execute_command() override;
};

class CommandTweeSlee final : public Command
{
public:
    CommandTweeSlee() = default;
    bool acknowledge_command() override;
    bool execute_command() override;
};

class CommandWatchdog final : public Command
{
public:
    CommandWatchdog() = default;
    bool acknowledge_command() override;
    bool execute_command() override;
};

class CommandInvalid final : public Command
{
public:
    CommandInvalid() = default;
    bool acknowledge_command() override;
    bool execute_command() override;
};

class CommandUnknown final : public Command
{
public:
    CommandUnknown() = default;
    bool acknowledge_command() override;
    bool execute_command() override;
};

class CommandModifyMode final : public Command
{
public:
    explicit CommandModifyMode(const char mode)
    {
        m_mode[0] = mode;
        m_mode[1] = '\0';
    };
    bool acknowledge_command() override;
    bool execute_command() override;
    void mode(const char mode) { m_mode[0] = mode; }
private:
    char m_mode[2]{};
};
