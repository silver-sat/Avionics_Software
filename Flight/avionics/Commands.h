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
    virtual bool validate_arguments(const String tokens[], const size_t token_count) const;
    virtual bool load_data(const String tokens[], const size_t token_count);
    virtual bool acknowledge_receipt() const;
    virtual bool negative_acknowledge_receipt() const;
    virtual bool execute() const;

protected:
    static const String m_action;
};

class CommandSetClock final : public Command
{
public:
    explicit CommandSetClock(const DateTime time) : m_time{time} {};
    bool validate_arguments(const String tokens[], const size_t token_count) const override;
    bool load_data(const String tokens[], const size_t token_count);
    bool acknowledge_receipt() const override;
    bool execute() const override;
    void time(const DateTime time) { m_time = time; }

private:
    DateTime m_time;
    static const String m_action;
};

class CommandBeaconSp final : public Command
{
public:
    explicit CommandBeaconSp(const int seconds) : m_seconds{seconds} {};
    bool validate_arguments(const String tokens[], const size_t token_count) const override;
    bool load_data(const String tokens[], const size_t token_count);
    bool acknowledge_receipt() const override;
    bool execute() const override;
    void seconds(const int seconds) { m_seconds = seconds; }

private:
    int m_seconds;
    static const String m_action;
};

class CommandPicTimes final : public Command
{
public:
    explicit CommandPicTimes(const DateTime time) : m_time{time} {};
    bool validate_arguments(const String tokens[], const size_t token_count) const override;
    bool load_data(const String tokens[], const size_t token_count);
    bool acknowledge_receipt() const override;
    bool execute() const override;
    void time(const DateTime time) { m_time = time; }

private:
    DateTime m_time;
    static const String m_action;
};

class CommandSSDVTimes final : public Command
{
public:
    explicit CommandSSDVTimes(const DateTime time) : m_time{time} {};
    bool validate_arguments(const String tokens[], const size_t token_count) const override;
    bool load_data(const String tokens[], const size_t token_count);
    bool acknowledge_receipt() const override;
    bool execute() const override;
    void time(const DateTime time) { m_time = time; }

private:
    DateTime m_time;
    static const String m_action;
};

class CommandClearPayloadQueue final : public Command
{
public:
    CommandClearPayloadQueue() = default;
    bool acknowledge_receipt() const override;
    bool execute() const override;

private:
    static const String m_action;
};

class CommandReportT final : public Command
{
public:
    CommandReportT() = default;
    bool acknowledge_receipt() const override;
    bool execute() const override;

private:
    static const String m_action;
};

class CommandGetPayloadQueue final : public Command
{
public:
    CommandGetPayloadQueue() = default;
    bool acknowledge_receipt() const override;
    bool execute() const override;

private:
    static const String m_action;
};

class CommandGetTelemetry final : public Command
{
public:
    CommandGetTelemetry() = default;
    bool acknowledge_receipt() const override;
    bool execute() const override;

private:
    static const String m_action;
};

class CommandGetPower final : public Command
{
public:
    CommandGetPower() = default;
    bool acknowledge_receipt() const override;
    bool execute() const override;

private:
    static const String m_action;
};

class CommandGetComms final : public Command
{
public:
    CommandGetComms() = default;
    bool acknowledge_receipt() const override;
    bool execute() const override;

private:
    static const String m_action;
};

class CommandGetBeaconInterval final : public Command
{
public:
    CommandGetBeaconInterval() = default;
    bool acknowledge_receipt() const override;
    bool execute() const override;

private:
    static const String m_action;
};

class CommandPayComms final : public Command
{
public:
    CommandPayComms() = default;
    bool acknowledge_receipt() const override;
    bool execute() const override;

private:
    static const String m_action;
};

class CommandTweeSlee final : public Command
{
public:
    CommandTweeSlee() = default;
    bool acknowledge_receipt() const override;
    bool execute() const override;

private:
    static const String m_action;
};

class CommandWatchdog final : public Command
{
public:
    CommandWatchdog() = default;
    bool acknowledge_receipt() const override;
    bool execute() const override;

private:
    static const String m_action;
};

class CommandInvalid final : public Command
{
public:
    CommandInvalid() = default;
    bool acknowledge_receipt() const override;
    bool execute() const override;

private:
    static const String m_action;
};

class CommandUnknown final : public Command
{
public:
    CommandUnknown() = default;
    bool acknowledge_receipt() const override;
    bool execute() const override;

private:
    static const String m_action;
};

class CommandNoOperate final : public Command
{
public:
    CommandNoOperate() = default;
    bool acknowledge_receipt() const override;
    bool execute() const override;

private:
    static const String m_action;
};

class CommandSendTestPacket final : public Command
{
public:
    CommandSendTestPacket() = default;
    bool acknowledge_receipt() const override;
    bool execute() const override;

private:
    static const String m_action;
};

class CommandUnsetClock final : public Command
{
public:
    CommandUnsetClock() = default;
    bool acknowledge_receipt() const override;
    bool execute() const override;

private:
    static const String m_action;
};

class CommandLogArguments final : public Command
{
public:
    explicit CommandLogArguments(const String arguments) : m_arguments{arguments} {};
    bool validate_arguments(const String tokens[], const size_t token_count) const override;
    bool load_data(const String tokens[], const size_t token_count);
    bool acknowledge_receipt() const override;
    bool execute() const override;

private:
    String m_arguments;
    static const String m_action;
};

class CommandBackgroundRSSI final : public Command
{
public:
    explicit CommandBackgroundRSSI(const String seconds) : m_seconds{seconds} {};
    bool validate_arguments(const String tokens[], const size_t token_count) const override;
    bool load_data(const String tokens[], const size_t token_count);
    bool acknowledge_receipt() const override;
    bool execute() const override;

private:
    String m_seconds;
    static const String m_action;
};

class CommandCurrentRSSI final : public Command
{
public:
    CommandCurrentRSSI() = default;
    bool acknowledge_receipt() const override;
    bool execute() const override;
private:
    static const String m_action;
};