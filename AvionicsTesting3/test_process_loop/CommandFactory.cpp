/**
 * @file CommandFactory.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Generate command object
 * @version 1.0.0
 * @date 2022-07-28
 *
 *
 */

#include "CommandFactory.h"
#include "log_utility.h"
#include <Arduino.h>

/**
 * @brief Construct a new Command Factory:: Command Factory object
 *
 */

CommandFactory::CommandFactory(String tokens[], size_t token_count)
{
    if (tokens[0] == "BeaconSp")
    {
        if (token_count == 1)
        {
            auto token_is_digits = true;
            for (auto index = 0; index < tokens[1].length(); index++)
            {
                if (!isDigit(tokens[1][index]))
                {
                    token_is_digits = false;
                }
            }
            if (token_is_digits)
            {
                _command = new CommandBeaconSp(tokens[1].toInt());
                return;
            }
        }
        _command = new CommandInvalid(); // Wrong number of parameters or bad parameter
        return;
    }
    else if (tokens[0] == "PayComms")
    {
        if (token_count == 0)
        {
            _command = new CommandPayComms();
            return;
        }
        else
        {
            _command = new CommandInvalid(); // Wrong number of parameters
            return;
        }
    }
    else if (tokens[0] == "PicTimes")
    {
        if (token_count == 6)
        {
            auto tokens_are_digits = true;
            for (auto token = 1; token <= token_count; token++)
            {
                for (auto index = 0; index < tokens[token].length(); index++)
                {
                    if (!isDigit(tokens[token][index]))
                    {
                        tokens_are_digits = false;
                    }
                }
            }
            if (tokens_are_digits)
            {

                _command = new CommandPicTimes({tokens[1].toInt(),
                                                tokens[2].toInt(),
                                                tokens[3].toInt(),
                                                tokens[4].toInt(),
                                                tokens[5].toInt(),
                                                tokens[6].toInt()});
                return;
            }
        }
        _command = new CommandInvalid(); // Wrong number of parameters or bad parameter
        return;
    }
    else if (tokens[0] == "ReportT")
    {
        if (token_count == 0)
        {
            _command = new CommandReportT();
            return;
        }
        else
        {
            _command = new CommandInvalid(); // Wrong number of parameters
            return;
        }
    }
    else if (tokens[0] == "NoOperate")
    {
        if (token_count == 0)
        {
            _command = new CommandNoOperate();
            return;
        }
        else
        {
            _command = new CommandInvalid(); // Wrong number of parameters
            return;
        }
    }
    else if (tokens[0] == "SetClock")
    {
        if (token_count == 6)
        {
            auto tokens_are_digits = true;
            for (auto token = 1; token <= token_count; token++)
            {
                for (auto index = 0; index < tokens[token].length(); index++)
                {
                    if (!isDigit(tokens[token][index]))
                    {
                        tokens_are_digits = false;
                    }
                }
            }
            if (tokens_are_digits)
            {
                _command = new CommandSetClock({tokens[1].toInt(),
                                                tokens[2].toInt(),
                                                tokens[3].toInt(),
                                                tokens[4].toInt(),
                                                tokens[5].toInt(),
                                                tokens[6].toInt()});
                return;
            }
        }
        _command = new CommandInvalid(); // Wrong number of parameters or bad parameter
        return;
    }
    else if (tokens[0] == "TweeSlee")
    {
        if (token_count == 0)

        {
            _command = new CommandTweeSlee();
            return;
        }
        else
        {
            _command = new CommandInvalid(); // Wrong number of parameters
            return;
        }
    }
    else if (tokens[0] == "Watchdog")
    {
        if (token_count == 0)
        {
            _command = new CommandWatchdog();
            return;
        }
        else
        {
            _command = new CommandInvalid(); // Wrong number of parameters
            return;
        }
    }
    else if (tokens[0] == "GetPicTimes")
    {
        if (token_count == 0)
        {
            _command = new CommandGetPicTimes();
            return;
        }
        else
        {
            _command = new CommandInvalid(); // Wrong number of parameters
            return;
        }
    }
    else if (tokens[0] == "GetTelemetry")
    {
        if (token_count == 0)
        {
            _command = new CommandGetTelemetry();
            return;
        }
        else
        {
            _command = new CommandInvalid(); // Wrong number of parameters
            return;
        }
    }
    else if (tokens[0] == "GetPower")
    {
        if (token_count == 0)
        {
            _command = new CommandGetPower();
            return;
        }
        else
        {
            _command = new CommandInvalid(); // Wrong number of parameters
            return;
        }
    }
    else if (tokens[0] == "GetPhotos")
    {
        if (token_count == 0)
        {
            _command = new CommandGetPhotos();
            return;
        }
        else
        {
            _command = new CommandInvalid(); // Wrong number of parameters
            return;
        }
    }
    else if (tokens[0] == "GetComms")
    {
        if (token_count == 0)
        {
            _command = new CommandGetComms();
            return;
        }
        else
        {
            _command = new CommandInvalid(); // Wrong number of parameters
            return;
        }
    }
    else if (tokens[0] == "GetBeaconInterval")
    {
        if (token_count == 0)
        {
            _command = new CommandGetBeaconInterval();
            return;
        }
        else
        {
            _command = new CommandInvalid(); // Wrong number of parameters
            return;
        }
    }
    else if (tokens[0] == "SendTestPacket")
    {
        if (token_count == 0)
        {
            _command = new CommandSendTestPacket();
            return;
        }
        else
        {
            _command = new CommandInvalid(); // Wrong number of parameters
            return;
        }
    }
    else if (tokens[0] == "UnsetClock")
    {
        if (token_count == 0)
        {
            _command = new CommandUnsetClock();
            return;
        }
        else
        {
            _command = new CommandInvalid(); // Wrong number of parameters
            return;
        }
    }
    else if (tokens[0] == "Unknown")
    {
        if (token_count == 0)
        {
            _command = new CommandUnknown();
            return;
        }
        else
        {
            _command = new CommandInvalid(); // Wrong number of parameters
            return;
        }
    }
    else
    {
        _command = new CommandUnknown();
        return;
    }
};

/**
 * @brief Destroy the Command Factory:: Command Factory object and the associated command
 *
 */

CommandFactory::~CommandFactory()
{
    if (_command)
    {
        delete _command;
        _command = NULL;
    };
};

/**
 * @brief return the command
 *
 * @return Command*
 */

Command *CommandFactory::get_command()
{
    return _command;
};
