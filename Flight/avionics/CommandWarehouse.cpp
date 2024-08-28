/**
 * @file CommandWarehouse.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Supply command objects
 * @version 1.2.1
 * @date 2022-07-28
 *
 * This file implements the class used to warehouse ground commands.
 *
 */

#include "avionics_constants.h"
#include "CommandWarehouse.h"
#include "Commands.h"
#include "log_utility.h"

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
    auto argument_count{token_count - 1};
    if (tokens[0] == "SetClock")
    {
        if (argument_count == 6)
        {
            auto tokens_are_digits = true;
            for (size_t token = 1; token <= argument_count; ++token)
                for (size_t index = 0; index < tokens[token].length(); ++index)
                    if (!isDigit(tokens[token][index]))
                        tokens_are_digits = false;
            if (tokens_are_digits)
            {
                m_set_clock.time(DateTime(
                    static_cast<uint16_t>(tokens[1].toInt()),
                    static_cast<uint8_t>(tokens[2].toInt()),
                    static_cast<uint8_t>(tokens[3].toInt()),
                    static_cast<uint8_t>(tokens[4].toInt()),
                    static_cast<uint8_t>(tokens[5].toInt()),
                    static_cast<uint8_t>(tokens[6].toInt())));
                return &m_set_clock;
            }
        }
        return &m_command_invalid; // Wrong number of parameters or bad parameter
    }
    else if (tokens[0] == "BeaconSp")
    {
        if (argument_count == 1)
        {
            auto token_is_digits = true;
            for (size_t index = 0; index < tokens[1].length(); ++index)
                if (!isDigit(tokens[1][index]))
                    token_is_digits = false;
            if (token_is_digits)
                m_beacon_sp.seconds(tokens[1].toInt());
                return &m_beacon_sp;
        }
        return &m_command_invalid; // Wrong number of parameters or bad parameter
    }
    else if (tokens[0] == "PicTimes")
    {
        if (argument_count == 6)
        {
            auto tokens_are_digits = true;
            for (size_t token = 1; token <= argument_count; ++token)
                for (size_t index = 0; index < tokens[token].length(); ++index)
                    if (!isDigit(tokens[token][index]))
                        tokens_are_digits = false;
            if (tokens_are_digits)
                m_pic_times.time(DateTime(
                    static_cast<uint16_t>(tokens[1].toInt()),
                    static_cast<uint8_t>(tokens[2].toInt()),
                    static_cast<uint8_t>(tokens[3].toInt()),
                    static_cast<uint8_t>(tokens[4].toInt()),
                    static_cast<uint8_t>(tokens[5].toInt()),
                    static_cast<uint8_t>(tokens[6].toInt())));
                return &m_pic_times;
        }
        return &m_command_invalid; // Wrong number of parameters or bad parameter
    }
    else if (tokens[0] == "ClearPicTimes")
    {
        if (argument_count == 0)
            return &m_clear_pic_times;
        else
            return &m_command_invalid; // Wrong number of parameters
    }
    else if (tokens[0] == "UnsetClock")
    {
        if (argument_count == 0)
            return &m_unset_clock;
        else
            return &m_command_invalid; // Wrong number of parameters
    }
    else if (tokens[0] == "ReportT")
    {
        if (argument_count == 0)
            return &m_report_t;
        else
            return &m_command_invalid; // Wrong number of parameters
    }
    else if (tokens[0] == "GetPicTimes")
    {
        if (argument_count == 0)
            return &m_get_pic_times;
        else
            return &m_command_invalid; // Wrong number of parameters
    }
    else if (tokens[0] == "GetTelemetry")
    {
        if (argument_count == 0)
            return &m_get_telemetry;
        else
            return &m_command_invalid; // Wrong number of parameters
    }
    else if (tokens[0] == "GetPower")
    {
        if (argument_count == 0)
            return &m_get_power;
        else
            return &m_command_invalid; // Wrong number of parameters
    }
    else if (tokens[0] == "GetComms")
    {
        if (argument_count == 0)
            return &m_get_comms;
        else
            return &m_command_invalid; // Wrong number of parameters
    }
    else if (tokens[0] == "GetBeaconInterval")
    {
        if (argument_count == 0)
            return &m_get_beacon_interval;
        else
            return &m_command_invalid; // Wrong number of parameters
    }
    else if (tokens[0] == "NoOperate")
    {
        if (argument_count == 0)
            return &m_no_operate;
        else
            return &m_command_invalid; // Wrong number of parameters
    }
    else if (tokens[0] == "SendTestPacket")
    {
        if (argument_count == 0)
            return &m_send_test_packet;
        else
            return &m_command_invalid; // Wrong number of parameters
    }
    else if (tokens[0] == "PayComms")
    {
        if (argument_count == 0)
            return &m_pay_comms;
        else
            return &m_command_invalid; // Wrong number of parameters
    }
    else if (tokens[0] == "TweeSlee")
    {
        if (argument_count == 0)
            return &m_twee_slee;
        else
            return &m_command_invalid; // Wrong number of parameters
    }
    else if (tokens[0] == "Watchdog")
    {
        if (argument_count == 0)
            return &m_watchdog;
        else
            return &m_command_invalid; // Wrong number of parameters
    }
    else if (tokens[0] == "ModifyMode")
    {
        if ((argument_count == 1) && (tokens[1].length() == mode_length))
        {
            m_modify_mode.mode(tokens[1][0]);
            return &m_modify_mode;
        }
        else
            return &m_command_invalid; // Wrong number of parameters
    }
    return &m_command_unknown; // Unknown command
}
