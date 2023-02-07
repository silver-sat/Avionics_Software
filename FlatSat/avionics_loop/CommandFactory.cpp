/**
 * @file CommandFactory.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Generate command objects
 * @version 1.2.0
 * @date 2022-07-28
 *
 *
 */

#include "avionics_constants.h"
#include "CommandFactory.h"
#include "Commands.h"
#include "log_utility.h"

/**
 * @brief Construct a new  Command object
 *
 */

Command *CommandFactory::BuildCommand(const String tokens[], size_t token_count)
{
    if (tokens[0] == "SetClock")
    {
        if (token_count == 6)
        {
            auto tokens_are_digits = true;
            for (size_t token = 1; token <= token_count; token++)
            {
                for (size_t index = 0; index < tokens[token].length(); index++)
                {
                    if (!isDigit(tokens[token][index]))
                    {
                        tokens_are_digits = false;
                    }
                }
            }
            if (tokens_are_digits)
            {
                return new CommandSetClock(DateTime(
                    static_cast<uint16_t>(tokens[1].toInt()),
                    static_cast<uint8_t>(tokens[2].toInt()),
                    static_cast<uint8_t>(tokens[3].toInt()),
                    static_cast<uint8_t>(tokens[4].toInt()),
                    static_cast<uint8_t>(tokens[5].toInt()),
                    static_cast<uint8_t>(tokens[6].toInt())));
            }
        }
        return new CommandInvalid(); // Wrong number of parameters or bad parameter
    }
    else if (tokens[0] == "BeaconSp")
    {
        if (token_count == 1)
        {
            auto token_is_digits = true;
            for (size_t index = 0; index < tokens[1].length(); index++)
            {
                if (!isDigit(tokens[1][index]))
                {
                    token_is_digits = false;
                }
            }
            if (token_is_digits)
            {
                return new CommandBeaconSp(tokens[1].toInt());
            }
        }
        return new CommandInvalid(); // Wrong number of parameters or bad parameter
    }
    else if (tokens[0] == "PicTimes")
    {
        if (token_count == 6)
        {
            auto tokens_are_digits = true;
            for (size_t token = 1; token <= token_count; token++)
            {
                for (size_t index = 0; index < tokens[token].length(); index++)
                {
                    if (!isDigit(tokens[token][index]))
                    {
                        tokens_are_digits = false;
                    }
                }
            }
            if (tokens_are_digits)
            {

                return new CommandPicTimes(DateTime(
                    static_cast<uint16_t>(tokens[1].toInt()),
                    static_cast<uint8_t>(tokens[2].toInt()),
                    static_cast<uint8_t>(tokens[3].toInt()),
                    static_cast<uint8_t>(tokens[4].toInt()),
                    static_cast<uint8_t>(tokens[5].toInt()),
                    static_cast<uint8_t>(tokens[6].toInt())));
            }
        }
        return new CommandInvalid(); // Wrong number of parameters or bad parameter
    }
    else if (tokens[0] == "ClearPicTimes")
    {
        if (token_count == 0)
        {
            return new CommandClearPicTimes();
        }
        else
        {
            return new CommandInvalid(); // Wrong number of parameters
        }
    }
    else if (tokens[0] == "UnsetClock")
    {
        if (token_count == 0)
        {
            return new CommandUnsetClock();
        }
        else
        {
            return new CommandInvalid(); // Wrong number of parameters
        }
    }
    else if (tokens[0] == "ReportT")
    {
        if (token_count == 0)
        {
            return new CommandReportT();
        }
        else
        {
            return new CommandInvalid(); // Wrong number of parameters
        }
    }
    else if (tokens[0] == "GetPicTimes")
    {
        if (token_count == 0)
        {
            return new CommandGetPicTimes();
        }
        else
        {
            return new CommandInvalid(); // Wrong number of parameters
        }
    }
    else if (tokens[0] == "GetTelemetry")
    {
        if (token_count == 0)
        {
            return new CommandGetTelemetry();
        }
        else
        {
            return new CommandInvalid(); // Wrong number of parameters
        }
    }
    else if (tokens[0] == "GetPower")
    {
        if (token_count == 0)
        {
            return new CommandGetPower();
        }
        else
        {
            return new CommandInvalid(); // Wrong number of parameters
        }
    }
    else if (tokens[0] == "GetPhotos")
    {
        if (token_count == 0)
        {
            return new CommandGetPhotos();
        }
        else
        {
            return new CommandInvalid(); // Wrong number of parameters
        }
    }
    else if (tokens[0] == "GetComms")
    {
        if (token_count == 0)
        {
            return new CommandGetComms();
        }
        else
        {
            return new CommandInvalid(); // Wrong number of parameters
        }
    }
    else if (tokens[0] == "GetBeaconInterval")
    {
        if (token_count == 0)
        {
            return new CommandGetBeaconInterval();
        }
        else
        {
            return new CommandInvalid(); // Wrong number of parameters
        }
    }
    else if (tokens[0] == "NoOperate")
    {
        if (token_count == 0)
        {
            return new CommandNoOperate();
        }
        else
        {
            return new CommandInvalid(); // Wrong number of parameters
        }
    }
    else if (tokens[0] == "SendTestPacket")
    {
        if (token_count == 0)
        {
            return new CommandSendTestPacket();
        }
        else
        {
            return new CommandInvalid(); // Wrong number of parameters
        }
    }
    else if (tokens[0] == "PayComms")
    {
        if (token_count == 0)
        {
            return new CommandPayComms();
        }
        else
        {
            return new CommandInvalid(); // Wrong number of parameters
        }
    }
    else if (tokens[0] == "TweeSlee")
    {
        if (token_count == 0)

        {
            return new CommandTweeSlee();
        }
        else
        {
            return new CommandInvalid(); // Wrong number of parameters
        }
    }
    else if (tokens[0] == "ExternalWatchdog")
    {
        if (token_count == 0)
        {
            return new CommandWatchdog();
        }
        else
        {
            return new CommandInvalid(); // Wrong number of parameters
        }
    }
    else if (tokens[0] == "ModifyFrequency")
    {
        if (token_count == 1)
        {
            char frequency[frequency_length]{};
            for (auto i = 0; i < frequency_length; ++i)
            {
                frequency[i] = tokens[1][i];
            }
            return new CommandModifyFrequency(frequency);
        }
        else
        {
            return new CommandInvalid(); // Wrong number of parameters
        }
    }
    else if (tokens[0] == "ModifyMode")
    {
        if (token_count == 1)
        {
            char mode{tokens[1][0]};
            return new CommandModifyMode(mode);
        }
        else
        {
            return new CommandInvalid(); // Wrong number of parameters
        }
    }
    else if (tokens[0] == "AdjustFrequency")
    {
        if (token_count == 1)
        {
            char frequency[frequency_length]{};
            for (auto i = 0; i < frequency_length; ++i)
            {
                frequency[i] = tokens[1][i];
            }
            return new CommandAdjustFrequency(frequency);
        }
        else
        {
            return new CommandInvalid(); // Wrong number of parameters
        }
    }
    else if (tokens[0] == "TransmitCW")
    {
        if (token_count == 1)
        {
            char duration[duration_length]{};
            duration[0] = tokens[1][0];
            duration[1] = tokens[1][1];
            return new CommandTransmitCW(duration);
        }
        else
        {
            return new CommandInvalid(); // Wrong number of parameters
        }
    }
    else if (tokens[0] == "BackgroundRSSI")
    {
        if (token_count == 1)
        {
            char duration[duration_length]{};
            duration[0] = tokens[1][0];
            duration[1] = tokens[1][1];
            return new CommandBackgroundRSSI(duration);
        }
        else
        {
            return new CommandInvalid(); // Wrong number of parameters
        }
    }
    else if (tokens[0] == "CurrentRSSI")
    {
        if (token_count == 1)
        {
            return new CommandCurrentRSSI();
        }
        else
        {
            return new CommandInvalid(); // Wrong number of parameters
        }
    }
    else if (tokens[0] == "SweepTransmitter")
    {
        if (token_count == 1)
        {
            char start_frequency[frequency_length]{};
            char stop_frequency[frequency_length]{};
            char number_of_steps[steps_length]{};
            char dwell_time[dwell_length]{};
            for (auto i = 0; i < frequency_length; ++i)
            {
                start_frequency[i] = tokens[1][i];
                stop_frequency[i] = tokens[2][i];
            }
            for (auto i = 0; i < steps_length; ++i)
            {
                number_of_steps[i] = tokens[3][i];
            }
            for (auto i = 0; i < dwell_length; ++i)
            {
                dwell_time[i] = tokens[4][i];
            }
            return new CommandSweepTransmitter(start_frequency, stop_frequency, number_of_steps, dwell_time);
        }
        else
        {
            return new CommandInvalid(); // Wrong number of parameters
        }
    }
    else if (tokens[0] == "SweepReceiver")
    {
        if (token_count == 1)
        {
            char start_frequency[frequency_length]{};
            char stop_frequency[frequency_length]{};
            char number_of_steps[steps_length]{};
            char dwell_time[dwell_length]{};
            for (auto i = 0; i < frequency_length; ++i)
            {
                start_frequency[i] = tokens[1][i];
                stop_frequency[i] = tokens[2][i];
            }
            for (auto i = 0; i < steps_length; ++i)
            {
                number_of_steps[i] = tokens[3][i];
            }
            for (auto i = 0; i < dwell_length; ++i)
            {
                dwell_time[i] = tokens[4][i];
            }
            return new CommandSweepReceiver(start_frequency, stop_frequency, number_of_steps, dwell_time);
        }
        else
        {
            return new CommandInvalid(); // Wrong number of parameters
        }
    }
    else if (tokens[0] == "QueryRegister")
    {
        if (token_count == 1)
        {
            char radio_register[register_length]{};
            for (auto i = 0; i < register_length; ++i)
            {
                radio_register[i] = tokens[1][i];
            }
            return new CommandAdjustFrequency(radio_register);
        }
        else
        {
            return new CommandInvalid(); // Wrong number of parameters
        }
    }
    else
    {
        return new CommandUnknown(); // Unknown command
    }
};
