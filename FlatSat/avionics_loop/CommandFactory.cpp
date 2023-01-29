/**
 * @file CommandFactory.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Generate command objects
 * @version 1.2.0
 * @date 2022-07-28
 *
 *
 */

#include "CommandFactory.h"
#include "Commands.h"
#include "log_utility.h"

/**
 * @brief Construct a new  Command object
 *
 */

Command* CommandFactory::BuildCommand(const String tokens[], size_t token_count)
{
    if (tokens[0] == "BeaconSp")
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
    else if (tokens[0] == "SetClock")
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
    else
    {
        return new CommandUnknown(); // Unknown command
    }
};
