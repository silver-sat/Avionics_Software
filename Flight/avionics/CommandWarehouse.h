/**
 * @file CommandWarehouse.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Supply command objects
 * @version 1.3.0
 * @date 2022-07-28
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
    /**
     * @brief Return a Command object
     *
     */

    Command *RetrieveCommand(const String tokens[], const size_t token_count);

private:

    CommandSetClock m_set_clock{DateTime(0, 0, 0, 0, 0, 0)};
    CommandBeaconSp m_beacon_sp{0};
    CommandPicTimes m_pic_times{DateTime(0, 0, 0, 0, 0, 0)};
    CommandSSDVTimes m_SSDV_times{DateTime(0, 0, 0, 0, 0, 0)};
    CommandClearPayloadQueue m_clear_payload_queue{};
    CommandUnsetClock m_unset_clock{};
    CommandReportT m_report_t{};
    CommandGetPayloadQueue m_get_payload_queue{};
    CommandGetTelemetry m_get_telemetry{};
    CommandGetPower m_get_power{};
    CommandGetComms m_get_comms{};
    CommandGetBeaconInterval m_get_beacon_interval{};
    CommandNoOperate m_no_operate{};
    CommandSendTestPacket m_send_test_packet{};
    CommandPayComms m_pay_comms{};
    CommandTweeSlee m_twee_slee{};
    CommandWatchdog m_watchdog{};
    CommandModifyMode m_modify_mode{0};
    CommandInvalid m_command_invalid{};
    CommandUnknown m_command_unknown{};
};
