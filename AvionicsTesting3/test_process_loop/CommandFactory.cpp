/**
 * @file ComandFactory.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Generate the appropriate command object
 * @version 1.0.0
 * @date 2022-07-28
 *
 *
 */

#include "CommandFactory.h"
#include <Arduino.h>

/**
 * @brief Construct a new Command Factory:: Command Factory object
 *
 */

CommandFactory::CommandFactory(String tokens[], size_t token_count)
{

    switch (token_count)
    {

    case 0:

    {
        if (tokens[0] == "NoOperate")
        {
            _command = new CommandNoOperate();
        }
        else if (tokens[0] == "Invalid")
        {
            _command = new CommandInvalid();
        }
        else if (tokens[0] == "Unknown")
        {
            _command = new CommandUnknown();
        }
        else if (tokens[0] == "PayComms")
        {
            _command = new CommandPayComms();
        }
        else if (tokens[0] == "ReportT")
        {
            _command = new CommandReportT();
        }
        else if (tokens[0] == "TweeSlee")
        {
            _command = new CommandTweeSlee();
        }
        else if (tokens[0] == "Watchdog")
        {
            _command = new CommandWatchdog();
        }
        else if (tokens[0] == "GetPicTimes")
        {
            _command = new CommandGetPicTimes();
        }
        else if (tokens[0] == "GetTelemetry")
        {
            _command = new CommandGetTelemetry();
        }
        else if (tokens[0] == "GetPower")
        {
            _command = new CommandGetPower();
        }
        else if (tokens[0] == "GetPhotos")
        {
            _command = new CommandGetPhotos();
        }
        else if (tokens[0] == "GetComms")
        {
            _command = new CommandGetComms();
        }
        else if (tokens[0] == "GetBeaconInterval")
        {
            _command = new CommandGetBeaconInterval();
        }
        else
        {
            _command = new CommandUnknown();
        };
        break;
    }
    case 1:
    {

        if (tokens[0] == "BeaconSp")
        {
            _command = new CommandBeaconSp(tokens[1].toInt());
        }
        else
        {
            _command = new CommandUnknown();
        };
        break;
    }

    case 2:
    case 3:
    case 4:
    case 5:

        _command = new CommandInvalid();
        break;

    case 6:

        if (tokens[0] == "PicTimes")
        {

            _command = new CommandPicTimes({tokens[1].toInt(),
                                            tokens[2].toInt(),
                                            tokens[3].toInt(),
                                            tokens[4].toInt(),
                                            tokens[5].toInt(),
                                            tokens[6].toInt()});
        }
        else if (tokens[0] == "SetClock")
        {
            _command = new CommandSetClock({tokens[1].toInt(),
                                            tokens[2].toInt(),
                                            tokens[3].toInt(),
                                            tokens[4].toInt(),
                                            tokens[5].toInt(),
                                            tokens[6].toInt()});
        }
        else
        {
            _command = new CommandUnknown();
        }
        break;

    default:

        _command = new CommandInvalid();
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
