/**
 * @file CommandFactory.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Generate command objects
 * @version 1.2.1
 * @date 2022-07-28
 *
 * This file implements the class used to build a new ground command.
 *
 */

#include "avionics_constants.h"
#include "CommandFactory.h"
#include "Commands.h"
#include "log_utility.h"

/**
 * @brief Construct a new Command object
 *
 */

// todo: consider additional log messages for invalid commands

/**
 * @brief Construct a new command object
 *
 * @param[in] tokens command and arguments
 * @param token_count number of tokens including command
 * @return Command* command object to be executed
 *
 */

Command *CommandFactory::BuildCommand(const String tokens[], const size_t token_count)
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
                return new CommandSetClock(DateTime(
                    static_cast<uint16_t>(tokens[1].toInt()),
                    static_cast<uint8_t>(tokens[2].toInt()),
                    static_cast<uint8_t>(tokens[3].toInt()),
                    static_cast<uint8_t>(tokens[4].toInt()),
                    static_cast<uint8_t>(tokens[5].toInt()),
                    static_cast<uint8_t>(tokens[6].toInt())));
        }
        return new CommandInvalid(); // Wrong number of parameters or bad parameter
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
                return new CommandBeaconSp(tokens[1].toInt());
        }
        return new CommandInvalid(); // Wrong number of parameters or bad parameter
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
                return new CommandPicTimes(DateTime(
                    static_cast<uint16_t>(tokens[1].toInt()),
                    static_cast<uint8_t>(tokens[2].toInt()),
                    static_cast<uint8_t>(tokens[3].toInt()),
                    static_cast<uint8_t>(tokens[4].toInt()),
                    static_cast<uint8_t>(tokens[5].toInt()),
                    static_cast<uint8_t>(tokens[6].toInt())));
        }
        return new CommandInvalid(); // Wrong number of parameters or bad parameter
    }
    else if (tokens[0] == "ClearPicTimes")
        if (argument_count == 0)
            return new CommandClearPicTimes();
        else
            return new CommandInvalid(); // Wrong number of parameters
    else if (tokens[0] == "UnsetClock")
        if (argument_count == 0)
            return new CommandUnsetClock();
        else
            return new CommandInvalid(); // Wrong number of parameters
    else if (tokens[0] == "ReportT")
        if (argument_count == 0)
            return new CommandReportT();
        else
            return new CommandInvalid(); // Wrong number of parameters
    else if (tokens[0] == "GetPicTimes")
        if (argument_count == 0)
            return new CommandGetPicTimes();
        else
            return new CommandInvalid(); // Wrong number of parameters
    else if (tokens[0] == "GetTelemetry")
        if (argument_count == 0)
            return new CommandGetTelemetry();
        else
            return new CommandInvalid(); // Wrong number of parameters
    else if (tokens[0] == "GetPower")
        if (argument_count == 0)
            return new CommandGetPower();
        else
            return new CommandInvalid(); // Wrong number of parameters
    else if (tokens[0] == "GetComms")
        if (argument_count == 0)
            return new CommandGetComms();
        else
            return new CommandInvalid(); // Wrong number of parameters
    else if (tokens[0] == "GetBeaconInterval")
        if (argument_count == 0)
            return new CommandGetBeaconInterval();
        else
            return new CommandInvalid(); // Wrong number of parameters
    else if (tokens[0] == "NoOperate")
        if (argument_count == 0)
            return new CommandNoOperate();
        else
            return new CommandInvalid(); // Wrong number of parameters
    else if (tokens[0] == "SendTestPacket")
        if (argument_count == 0)
            return new CommandSendTestPacket();
        else
            return new CommandInvalid(); // Wrong number of parameters
    else if (tokens[0] == "PayComms")
        if (argument_count == 0)
            return new CommandPayComms();
        else
            return new CommandInvalid(); // Wrong number of parameters
    else if (tokens[0] == "TweeSlee")
        if (argument_count == 0)
            return new CommandTweeSlee();
        else
            return new CommandInvalid(); // Wrong number of parameters
    else if (tokens[0] == "Watchdog")
        if (argument_count == 0)
            return new CommandWatchdog();
        else
            return new CommandInvalid(); // Wrong number of parameters
    else if (tokens[0] == "ModifyFrequency")
        if ((argument_count == 1) && (tokens[1].length() == frequency_length))
        {
            char frequency[frequency_length]{};
            memcpy(frequency, tokens[1].c_str(), frequency_length);
            return new CommandModifyFrequency(frequency);
        }
        else
            return new CommandInvalid(); // Wrong number of parameters or wrong parameter length
    else if (tokens[0] == "ModifyMode")
        if ((argument_count == 1) && (tokens[1].length() == mode_length))
        {
            char mode{tokens[1][0]};
            return new CommandModifyMode(mode);
        }
        else
            return new CommandInvalid(); // Wrong number of parameters
    else if (tokens[0] == "AdjustFrequency")
        if ((argument_count == 1) && tokens[1].length() == frequency_length)
        {
            char frequency[frequency_length]{};
            memcpy(frequency, tokens[1].c_str(), frequency_length);
            return new CommandAdjustFrequency(frequency);
        }
        else
            return new CommandInvalid(); // Wrong number of parameters
    else if (tokens[0] == "TransmitCW")
        if ((argument_count == 1) && tokens[1].length() == duration_length)
        {
            char duration[duration_length]{};
            memcpy(duration, tokens[1].c_str(), duration_length);
            return new CommandTransmitCW(duration);
        }
        else
            return new CommandInvalid(); // Wrong number of parameters
    else if (tokens[0] == "BackgroundRSSI")
        if ((argument_count == 1) && tokens[1].length() == duration_length)
        {
            char duration[duration_length]{};
            memcpy(duration, tokens[1].c_str(), duration_length);
            return new CommandBackgroundRSSI(duration);
        }
        else
            return new CommandInvalid(); // Wrong number of parameters
    else if (tokens[0] == "CurrentRSSI")
        if (argument_count == 0)
            return new CommandCurrentRSSI();
        else
            return new CommandInvalid(); // Wrong number of parameters
    else if (tokens[0] == "SweepTransmitter")
        if ((argument_count == 4) && (tokens[1].length() == frequency_length) && (tokens[2].length() == frequency_length) && (tokens[3].length() == steps_length) && (tokens[4].length() == dwell_length))
        {
            // todo: assess other copying options
            char start_frequency[frequency_length]{};
            char stop_frequency[frequency_length]{};
            char number_of_steps[steps_length]{};
            char dwell_time[dwell_length]{};
            memcpy(start_frequency, tokens[1].c_str(), frequency_length);
            memcpy(stop_frequency, tokens[2].c_str(), frequency_length);
            memcpy(number_of_steps, tokens[3].c_str(), steps_length);
            memcpy(dwell_time, tokens[4].c_str(), dwell_length);
            return new CommandSweepTransmitter(start_frequency, stop_frequency, number_of_steps, dwell_time);
        }
        else
            return new CommandInvalid(); // Wrong number of parameters
    else if (tokens[0] == "SweepReceiver")
        if ((argument_count == 4) && (tokens[1].length() == frequency_length) && (tokens[2].length() == frequency_length) && (tokens[3].length() == steps_length) && (tokens[4].length() == dwell_length))
        {
            // todo: assess other copying options
            char start_frequency[frequency_length]{};
            char stop_frequency[frequency_length]{};
            char number_of_steps[steps_length]{};
            char dwell_time[dwell_length]{};
            memcpy(start_frequency, tokens[1].c_str(), frequency_length);
            memcpy(stop_frequency, tokens[2].c_str(), frequency_length);
            memcpy(number_of_steps, tokens[3].c_str(), steps_length);
            memcpy(dwell_time, tokens[4].c_str(), dwell_length);

            return new CommandSweepReceiver(start_frequency, stop_frequency, number_of_steps, dwell_time);
        }
        else
            return new CommandInvalid(); // Wrong number of parameters
    else if (tokens[0] == "QueryRegister")
        if ((argument_count == 1) && (tokens[1].length() == register_length))
        {
            // todo: assess other copying options
            char radio_register[register_length]{};
            memcpy(radio_register, tokens[1].c_str(), register_length);
            return new CommandQueryRegister(radio_register);
        }
        else
            return new CommandInvalid(); // Wrong number of parameters
    else
        return new CommandUnknown(); // Unknown command
}
