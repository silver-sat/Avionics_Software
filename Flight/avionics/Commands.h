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
};

class CommandClearPayloadQueue final : public Command
{
public:
    CommandClearPayloadQueue() = default;
    bool acknowledge_receipt() const override;
    bool execute() const override;
};

class CommandReportT final : public Command
{
public:
    CommandReportT() = default;
    bool acknowledge_receipt() const override;
    bool execute() const override;
};

class CommandGetPayloadQueue final : public Command
{
public:
    CommandGetPayloadQueue() = default;
    bool acknowledge_receipt() const override;
    bool execute() const override;
};

class CommandGetTelemetry final : public Command
{
public:
    CommandGetTelemetry() = default;
    bool acknowledge_receipt() const override;
    bool execute() const override;
};

class CommandGetPower final : public Command
{
public:
    CommandGetPower() = default;
    bool acknowledge_receipt() const override;
    bool execute() const override;
};

class CommandGetComms final : public Command
{
public:
    CommandGetComms() = default;
    bool acknowledge_receipt() const override;
    bool execute() const override;
};

class CommandGetBeaconInterval final : public Command
{
public:
    CommandGetBeaconInterval() = default;
    bool acknowledge_receipt() const override;
    bool execute() const override;
};

class CommandPayComms final : public Command
{
public:
    CommandPayComms() = default;
    bool acknowledge_receipt() const override;
    bool execute() const override;
};

class CommandTweeSlee final : public Command
{
public:
    CommandTweeSlee() = default;
    bool acknowledge_receipt() const override;
    bool execute() const override;
};

class CommandWatchdog final : public Command
{
public:
    CommandWatchdog() = default;
    bool acknowledge_receipt() const override;
    bool execute() const override;
};

class CommandInvalid final : public Command
{
public:
    CommandInvalid() = default;
    bool acknowledge_receipt() const override;
    bool execute() const override;
};

class CommandUnknown final : public Command
{
public:
    CommandUnknown() = default;
    bool acknowledge_receipt() const override;
    bool execute() const override;
};

class CommandNoOperate final : public Command
{
public:
    CommandNoOperate() = default;
    bool acknowledge_receipt() const override;
    bool execute() const override;
};

class CommandSendTestPacket final : public Command
{
public:
    CommandSendTestPacket() = default;
    bool acknowledge_receipt() const override;
    bool execute() const override;
};

class CommandUnsetClock final : public Command
{
public:
    CommandUnsetClock() = default;
    bool acknowledge_receipt() const override;
    bool execute() const override;
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
};

class CommandCurrentRSSI final : public Command
{
public:
    CommandCurrentRSSI() = default;
    bool acknowledge_receipt() const override;
    bool execute() const override;
};
class CommandModifyCCA final : public Command
{
public:
    explicit CommandModifyCCA(const String threshold) : m_threshold{threshold} {};
    bool validate_arguments(const String tokens[], const size_t token_count) const override;
    bool load_data(const String tokens[], const size_t token_count);
    bool acknowledge_receipt() const override;
    bool execute() const override;

private:
    String m_threshold;
};