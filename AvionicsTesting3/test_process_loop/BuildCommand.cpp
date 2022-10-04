/**
 * @file BuildCommand.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Generate command object
 * @version 1.1.0
 * @date 2022-07-28
 *
 *
 */

#include "BuildCommand.h"
#include "log_utility.h"
#include <Arduino.h>

/**
 * @brief Construct a new  BuildCommand::BuildCommand object
 *
 */

BuildCommand::BuildCommand(String tokens[], size_t token_count)
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
                m_command = new CommandBeaconSp(tokens[1].toInt());
                return;
            }
        }
        m_command = new CommandInvalid(); // Wrong number of parameters or bad parameter
        return;
    }
    else if (tokens[0] == "PayComms")
    {
        if (token_count == 0)
        {
            m_command = new CommandPayComms();
            return;
        }
        else
        {
            m_command = new CommandInvalid(); // Wrong number of parameters
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

                m_command = new CommandPicTimes({tokens[1].toInt(),
                                                tokens[2].toInt(),
                                                tokens[3].toInt(),
                                                tokens[4].toInt(),
                                                tokens[5].toInt(),
                                                tokens[6].toInt()});
                return;
            }
        }
        m_command = new CommandInvalid(); // Wrong number of parameters or bad parameter
        return;
    }
    else if (tokens[0] == "ReportT")
    {
        if (token_count == 0)
        {
            m_command = new CommandReportT();
            return;
        }
        else
        {
            m_command = new CommandInvalid(); // Wrong number of parameters
            return;
        }
    }
    else if (tokens[0] == "NoOperate")
    {
        if (token_count == 0)
        {
            m_command = new CommandNoOperate();
            return;
        }
        else
        {
            m_command = new CommandInvalid(); // Wrong number of parameters
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
                m_command = new CommandSetClock({tokens[1].toInt(),
                                                tokens[2].toInt(),
                                                tokens[3].toInt(),
                                                tokens[4].toInt(),
                                                tokens[5].toInt(),
                                                tokens[6].toInt()});
                return;
            }
        }
        m_command = new CommandInvalid(); // Wrong number of parameters or bad parameter
        return;
    }
    else if (tokens[0] == "TweeSlee")
    {
        if (token_count == 0)

        {
            m_command = new CommandTweeSlee();
            return;
        }
        else
        {
            m_command = new CommandInvalid(); // Wrong number of parameters
            return;
        }
    }
    else if (tokens[0] == "Watchdog")
    {
        if (token_count == 0)
        {
            m_command = new CommandWatchdog();
            return;
        }
        else
        {
            m_command = new CommandInvalid(); // Wrong number of parameters
            return;
        }
    }
    else if (tokens[0] == "GetPicTimes")
    {
        if (token_count == 0)
        {
            m_command = new CommandGetPicTimes();
            return;
        }
        else
        {
            m_command = new CommandInvalid(); // Wrong number of parameters
            return;
        }
    }
    else if (tokens[0] == "GetTelemetry")
    {
        if (token_count == 0)
        {
            m_command = new CommandGetTelemetry();
            return;
        }
        else
        {
            m_command = new CommandInvalid(); // Wrong number of parameters
            return;
        }
    }
    else if (tokens[0] == "GetPower")
    {
        if (token_count == 0)
        {
            m_command = new CommandGetPower();
            return;
        }
        else
        {
            m_command = new CommandInvalid(); // Wrong number of parameters
            return;
        }
    }
    else if (tokens[0] == "GetPhotos")
    {
        if (token_count == 0)
        {
            m_command = new CommandGetPhotos();
            return;
        }
        else
        {
            m_command = new CommandInvalid(); // Wrong number of parameters
            return;
        }
    }
    else if (tokens[0] == "GetComms")
    {
        if (token_count == 0)
        {
            m_command = new CommandGetComms();
            return;
        }
        else
        {
            m_command = new CommandInvalid(); // Wrong number of parameters
            return;
        }
    }
    else if (tokens[0] == "GetBeaconInterval")
    {
        if (token_count == 0)
        {
            m_command = new CommandGetBeaconInterval();
            return;
        }
        else
        {
            m_command = new CommandInvalid(); // Wrong number of parameters
            return;
        }
    }
    else if (tokens[0] == "SendTestPacket")
    {
        if (token_count == 0)
        {
            m_command = new CommandSendTestPacket();
            return;
        }
        else
        {
            m_command = new CommandInvalid(); // Wrong number of parameters
            return;
        }
    }
    else if (tokens[0] == "ClearPicTimes")
    {
        if (token_count == 0)
        {
            m_command = new CommandClearPicTimes();
            return;
        }
        else
        {
            m_command = new CommandInvalid(); // Wrong number of parameters
            return;
        }
    }
    else if (tokens[0] == "UnsetClock")
    {
        if (token_count == 0)
        {
            m_command = new CommandUnsetClock();
            return;
        }
        else
        {
            m_command = new CommandInvalid(); // Wrong number of parameters
            return;
        }
    }
    else if (tokens[0] == "Unknown")
    {
        if (token_count == 0)
        {
            m_command = new CommandUnknown();
            return;
        }
        else
        {
            m_command = new CommandInvalid(); // Wrong number of parameters
            return;
        }
    }
    else
    {
        m_command = new CommandUnknown();
        return;
    }
};

/**
 * @brief Destroy the BuildCommand::BuildCommand object and the associated command
 *
 */

BuildCommand::~BuildCommand()
{
    if (m_command)
    {
        delete m_command;
        m_command = NULL;
    };
};

/**
 * @brief return the command
 *
 * @return Command*
 */

ExecuteCommand *BuildCommand::get_command()
{
    return m_command;
};
