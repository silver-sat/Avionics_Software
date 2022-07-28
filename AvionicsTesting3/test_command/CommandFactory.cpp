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

/**
 * @brief Construct a new Command Factory:: Command Factory object
 *
 */
CommandFactory::CommandFactory(){

};

/**
 * @brief Construct a new Command Factory:: Command Factory object with only an operation
 *
 * @param command
 */
CommandFactory::CommandFactory(String command)
{
    if (command == "NoOperate")
    {
        _command = new CommandNoOperate();
    }
    else if (command == "Invalid")
    {
        _command = new CommandInvalid();
    }
    else if (command == "Unknown")
    {
        _command = new CommandUnknown();
    }
    else if (command == "PayComms")
    {
        _command = new CommandPayComms();
    }
    else if (command == "ReportT")
    {
        _command = new CommandReportT();
    }
    else if (command == "TweeSlee")
    {
        _command = new CommandTweeSlee();
    }
    else if (command == "Watchdog")
    {
        _command = new CommandWatchdog();
    }
    else
    {
        _command = new CommandInvalid();
    };
};

/**
 * @brief Construct a new Command Factory:: Command Factory object with an operation and integer parameter
 *
 * @param command
 * @param parameter
 */
CommandFactory::CommandFactory(String command, int parameter)
{
    if (command == "BeaconSp")
    {
        _command = new CommandBeaconSp(parameter);
    }
    else
    {
        _command = new CommandInvalid();
    };
};
/**
 * @brief Construct a new Command Factory:: Command Factory object with an operation and a time value parameter
 *
 * @param command
 * @param time time value
 */
CommandFactory::CommandFactory(String command, time_value time)
{
    if (command == "PicTimes")
    {
        _command = new CommandPicTimes(time);
    }
    else if (command == "SetClock")
    {
        _command = new CommandSetClock(time);
    }
    else
    {
        _command = new CommandInvalid();
    }
};
CommandFactory::~CommandFactory()
{
    if (_command)
    {
        delete _command;
        _command = NULL;
    };
};
Command *CommandFactory::get_command()
{
    return _command;
};
