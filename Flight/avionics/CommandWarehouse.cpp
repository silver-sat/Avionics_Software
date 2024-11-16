/**
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Supply command objects
 *
 * This file implements the class used to warehouse ground commands.
 *
 */

#include "avionics_constants.h"
#include "CommandWarehouse.h"
#include "Commands.h"
#include "log_utility.h"

CommandSetClock CommandWarehouse::m_set_clock{DateTime(0, 0, 0, 0, 0, 0)};
CommandBeaconSp CommandWarehouse::m_beacon_sp{0};
CommandPicTimes CommandWarehouse::m_pic_times{DateTime(0, 0, 0, 0, 0, 0)};
CommandSSDVTimes CommandWarehouse::m_SSDV_times{DateTime(0, 0, 0, 0, 0, 0)};
CommandClearPayloadQueue CommandWarehouse::m_clear_payload_queue{};
CommandReportT CommandWarehouse::m_report_t{};
CommandGetPayloadQueue CommandWarehouse::m_get_payload_queue{};
CommandGetTelemetry CommandWarehouse::m_get_telemetry{};
CommandGetPower CommandWarehouse::m_get_power{};
CommandGetComms CommandWarehouse::m_get_comms{};
CommandGetBeaconInterval CommandWarehouse::m_get_beacon_interval{};
CommandPayComms CommandWarehouse::m_pay_comms{};
CommandTweeSlee CommandWarehouse::m_twee_slee{};
CommandWatchdog CommandWarehouse::m_watchdog{};
CommandInvalid CommandWarehouse::m_command_invalid{};
CommandUnknown CommandWarehouse::m_command_unknown{};
CommandNoOperate CommandWarehouse::m_no_operate{};
CommandSendTestPacket CommandWarehouse::m_send_test_packet{};
CommandUnsetClock CommandWarehouse::m_unset_clock{};
CommandLogArguments CommandWarehouse::m_log_arguments{""};
CommandBackgroundRSSI CommandWarehouse::m_background_RSSI{"00"};
CommandCurrentRSSI CommandWarehouse::m_current_RSSI{};
CommandModifyCCA CommandWarehouse::m_modify_CCA{"00"};

CommandWarehouse::CommandMap CommandWarehouse::command_description[]{
    {"SetClock", &m_set_clock},
    {"BeaconSp", &m_beacon_sp},
    {"PicTimes", &m_pic_times},
    {"SSDVTimes", &m_SSDV_times},
    {"ClearPayloadQueue", &m_clear_payload_queue},
    {"ReportT", &m_report_t},
    {"GetPayloadQueue", &m_get_payload_queue},
    {"GetTelemetry", &m_get_telemetry},
    {"GetPower", &m_get_power},
    {"GetComms", &m_get_comms},
    {"GetBeaconInterval", &m_get_beacon_interval},
    {"PayComms", &m_pay_comms},
    {"TweeSlee", &m_twee_slee},
    {"Watchdog", &m_watchdog},
    {"Invalid", &m_command_invalid},
    {"Unknown", &m_command_unknown},
    {"NoOperate", &m_no_operate},
    {"SendTestPacket", &m_send_test_packet},
    {"UnsetClock", &m_unset_clock},
    {"LogArguments", &m_log_arguments},
    {"BackgroundRSSI", &m_background_RSSI},
    {"CurrentRSSI", &m_current_RSSI},
    {"ModifyCCA", &m_modify_CCA}
};

/**
 * @brief Return a command object
 *
 * @param[in] tokens command and arguments
 * @param token_count number of tokens including command
 * @return Command* command object to be executed
 *
 */

Command *CommandWarehouse::RetrieveCommand(const String tokens[], const size_t token_count)
{
    for (const auto &entry : command_description)
    {
        if (tokens[0] == entry.command_name)
        {
            if (entry.command_pointer->validate_arguments(tokens, token_count))
            {
                entry.command_pointer->load_data(tokens, token_count);
                return entry.command_pointer;
            }
            else
            {
                return &m_command_invalid;
            }
        }
    }
    return &m_command_unknown;
}
