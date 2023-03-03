/**
 * @file Commands.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat commands
 * @version 1.2.0
 * @date 2022-07-25
 *
 * This file declares and constructs all Command objects. Each ground command is derived
 * from the Command class. Abbreviations listed are used in command responses.
 *
 * Commands
 *
 * Change satellite state:
 *
 * SRC: SetClock: subsumes SetTime: set realtime clock
 * SBI: BeaconSP: set beacon spacing
 * SPT: PicTimes: set times for photos
 * CPT: ClearPicTimes: empty PicTimes queue
 * URC: UnsetClock: change the realtime clock status to unset for testing
 *
 * Get satellite state:
 *
 * GRC: ReportT: subsumes GetTime: reply with realtime clock setting
 * GPT: GetPicTimes: reply with picture schedule
 * GTY: GetTelemetry: reply with telemetry
 * GPW: GetPower: reply with power status
 * GPC: GetPhotos: reply with number of photos
 * GRS: GetComms: reply with Radio Board status
 * GBI: GetBeaconInterval: reply with beacon interval
 *
 * Invoke satellite operation:
 *
 * NOP: NoOperate: subsumes Ping: acknowledge
 * STP: SendTestPacket: reply with test message
 * PYC: PayComms: subsumes Begin tweet : start payload in communications mode
 * TSL: TweeSlee: subsumes Halt: stop communicating
 * WDG: ExternalWatchdog: force watchdog timeout (reset SAMD21)
 *
 * Invalid and unknown commands
 *
 * INV: invalid
 * UNK: unknown
 *
 * Radio commands:
 *
 * RMF: ModifyFrequency: modify radio frequency
 * RMM: ModifyMode: modify radio mode
 * RAF: AdjustFrequency: adjust radio frequency temporarily
 * RTC: TransmitCW: transmit carrier wave
 * RBR: BackgroundRSSI: radio background rssi
 * RCR: CurrentRSSI: radio current rssi
 * RST: SweepTransmitter: radio sweep transmitter
 * RSR: SweepReceiver: radio sweep receiver
 * RQR: QueryRegister: radio query register
 *
 * Deprecated commands:
 *
 * halt, see TweeSlee
 * s_call_sig deprecated
 * g_call_sig, deprecated
 *
 */

#pragma once

#include "avionics_constants.h"
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
 * @brief set_clock command
 *
 * @param time UTC for real time clock
 */

class CommandSetClock final : public Command
{
public:
    CommandSetClock(DateTime time) : m_time{time} {};
    bool acknowledge_command() override;
    bool execute_command() override;

private:
    DateTime m_time;
};

/**
 * @brief beacon_sp command
 *
 * @param seconds interval between beacons
 */

class CommandBeaconSp final : public Command
{
public:
    CommandBeaconSp(int seconds) : m_seconds{seconds} {};
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
    CommandPicTimes(DateTime time) : m_time{time} {};
    bool acknowledge_command() override;
    bool execute_command() override;

private:
    DateTime m_time;
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
 * @brief modify frequency command
 *
 */

class CommandModifyFrequency final : public Command
{
public:
    CommandModifyFrequency(const char frequency[frequency_length])
    {
        memcpy(m_frequency, frequency, frequency_length);
        m_frequency[frequency_length] = '\0';
    }
    bool acknowledge_command() override;
    bool execute_command() override;

private:
    char m_frequency[frequency_length + 1]{};
};

/**
 * @brief modify mode command
 *
 */

class CommandModifyMode final : public Command
{
public:
    CommandModifyMode(const char mode) {
        m_mode[0] = mode;
        m_mode[1] = '\0';
    };
    bool acknowledge_command() override;
    bool execute_command() override;

private:
    char m_mode[2]{};
};

/**
 * @brief adjust frequency command
 *
 */

class CommandAdjustFrequency final : public Command
{
public:
    CommandAdjustFrequency(const char *frequency)
    {
        memcpy(m_frequency, frequency, frequency_length);
        m_frequency[frequency_length] = '\0';
    }
    bool acknowledge_command() override;
    bool execute_command() override;

private:
    char m_frequency[frequency_length + 1]{};
};

/**
 * @brief transmit carrier wave command
 *
 */

class CommandTransmitCW final : public Command
{
public:
    CommandTransmitCW(const char *duration)
    {
        m_duration[0] = duration[0];
        m_duration[1] = duration[1];
        m_duration[2] = '\0';
    }
    bool acknowledge_command() override;
    bool execute_command() override;

private:
    char m_duration[duration_length + 1]{};
};

/**
 * @brief background rssi command
 *
 */

class CommandBackgroundRSSI final : public Command
{
public:
    CommandBackgroundRSSI() = default;
    bool acknowledge_command() override;
    bool execute_command() override;
};

/**
 * @brief current rssi command
 *
 */

class CommandCurrentRSSI final : public Command
{
public:
    CommandCurrentRSSI() = default;
    bool acknowledge_command() override;
    bool execute_command() override;
};

/**
 * @brief sweep transmitter command
 *
 */

class CommandSweepTransmitter final : public Command
{
public:
    CommandSweepTransmitter(const char *start_frequency, const char *stop_frequency, const char *number_of_steps, const char *dwell_time)
    {
        memcpy(m_start_frequency, start_frequency, frequency_length);
        m_start_frequency[frequency_length] = '\0';
        memcpy(m_stop_frequency, stop_frequency, frequency_length);
        m_stop_frequency[frequency_length] = '\0';
        memcpy(m_number_of_steps, number_of_steps, steps_length);
        m_number_of_steps[steps_length] = '\0';
        memcpy(m_dwell_time, dwell_time, dwell_length);
        m_dwell_time[dwell_length] = '\0';
    }
    bool acknowledge_command() override;
    bool execute_command() override;

private:
    char m_start_frequency[frequency_length + 1]{};
    char m_stop_frequency[frequency_length + 1]{};
    char m_number_of_steps[steps_length + 1]{};
    char m_dwell_time[dwell_length + 1]{};
};

/**
 * @brief sweep receiver command
 *
 */

class CommandSweepReceiver final : public Command
{
public:
    CommandSweepReceiver(const char *start_frequency, const char *stop_frequency, const char *number_of_steps, const char *dwell_time)
    {
        memcpy(m_start_frequency, start_frequency, frequency_length);
        m_start_frequency[frequency_length] = '\0';
        memcpy(m_stop_frequency, stop_frequency, frequency_length);
        m_stop_frequency[frequency_length] = '\0';
        memcpy(m_number_of_steps, number_of_steps, steps_length);
        m_number_of_steps[steps_length] = '\0';
        memcpy(m_dwell_time, dwell_time, dwell_length);
        m_dwell_time[dwell_length] = '\0';
    }
    bool acknowledge_command() override;
    bool execute_command() override;

private:
    char m_start_frequency[frequency_length + 1]{};
    char m_stop_frequency[frequency_length + 1]{};
    char m_number_of_steps[steps_length + 1]{};
    char m_dwell_time[dwell_length + 1]{};
};

/**
 * @brief query register command
 *
 */

class CommandQueryRegister final : public Command
{
public:
    CommandQueryRegister(const char *radio_register)
    {
        memcpy(m_radio_register, radio_register, register_length);
        m_radio_register[register_length] = '\0';
    }
    bool acknowledge_command() override;
    bool execute_command() override;

private:
    char m_radio_register[register_length + 1]{};
};
