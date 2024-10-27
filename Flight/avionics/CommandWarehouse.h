/**
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Supply command objects
 *
 * This file declares the class used to return a ground command.
 */

#pragma once

#include "Commands.h"

/**
 * @brief Warehouse for Command objects
 *
 */

class CommandWarehouse final
{
public:
    Command *RetrieveCommand(const String tokens[], const size_t token_count);

private:
    static CommandSetClock m_set_clock;
    static CommandBeaconSp m_beacon_sp;
    static CommandPicTimes m_pic_times;
    static CommandSSDVTimes m_SSDV_times;
    static CommandClearPayloadQueue m_clear_payload_queue;
    static CommandReportT m_report_t;
    static CommandGetPayloadQueue m_get_payload_queue;
    static CommandGetTelemetry m_get_telemetry;
    static CommandGetPower m_get_power;
    static CommandGetComms m_get_comms;
    static CommandGetBeaconInterval m_get_beacon_interval;
    static CommandPayComms m_pay_comms;
    static CommandTweeSlee m_twee_slee;
    static CommandWatchdog m_watchdog;
    static CommandInvalid m_command_invalid;
    static CommandUnknown m_command_unknown;
    static CommandNoOperate m_no_operate;
    static CommandSendTestPacket m_send_test_packet;
    static CommandUnsetClock m_unset_clock;
    static CommandLogArguments m_log_arguments;

    struct CommandMap
    {
        const String command_name;
        Command *const command_pointer;
    };

    static CommandMap command_description[];
};