/**
 * @file command.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat commands
 * @version 1.0.1
 * @date 2022-07-25
 *
 *
 */

#include "command.h"

/**
 * @brief create command object
 *
 * @param command string
 * @return operation
 */

Command *Command::create_type1(String command)
{
    if (command == "NoOperate")
    {
        return new CommandNoOperate();
    }
    else if (command == "Invalid")
    {
        return new CommandInvalid();
    }
    else if (command == "Unknown")
    {
        return new CommandUnknown();
    }
    else if (command == "PayComms")
    {
        return new CommandPayComms();
    }
    else if (command == "ReportT")
    {
        return new CommandReportT();
    }
    else if (command == "TweeSlee")
    {
        return new CommandTweeSlee();
    }
    else if (command == "Watchdog")
    {
        return new CommandWatchdog();
    }

    else
    {
        return new CommandInvalid();
    };
};

Command *Command::create_type2(String command, int parameter)
{
    if (command == "BeaconSp")
    {
        return new CommandBeaconSp(parameter);
    }
    else
    {
        return new CommandInvalid();
    };
};

Command *Command::create_type3(String command, time_value time)
{
    if (command == "PicTimes")
    {
        return new CommandPicTimes(time);
    }
    else if (command == "SetClock")
    {
        return new CommandSetClock(time);
    }
    else
    {
        return new CommandInvalid();
    }
};

Client::Client(){

};
Client::Client(String command)
{
    _command = Command::create_type1(command);
};
Client::Client(String command, int parameter)
{
    _command = Command::create_type2(command, parameter);
};
Client::Client(String command, time_value time)
{
    _command = Command::create_type3(command, time);
};
Client::~Client()
{
    if (_command)
    {
        delete _command;
        _command = NULL;
    };
};
Command *Client::get_command()
{
    return _command;
};

/**
 * @brief Construct a new Command with no parameters
 *
 * @param operation command
 * @param Content parameters
 */

Command::Command(){};

Command::operation Command::get_operation()
{
    return _action;
};

CommandUnknown::CommandUnknown()
{
    _action = Command::unknown;
};

CommandInvalid::CommandInvalid()
{
    _action = Command::invalid;
};

CommandNoOperate::CommandNoOperate()
{
    _action = Command::no_operate;
};

CommandPayComms::CommandPayComms()
{
    _action = Command::pay_comms;
};

CommandReportT::CommandReportT()
{
    _action = Command::report_t;
};

CommandTweeSlee::CommandTweeSlee()
{
    _action = Command::twee_slee;
};

CommandWatchdog::CommandWatchdog()
{
    _action = Command::watchdog;
};

CommandBeaconSp::CommandBeaconSp(int parameter)
{
    _action = Command::beacon_sp;
    _value = parameter;
};

CommandPicTimes::CommandPicTimes(time_value time)
{
    _action = Command::pic_times;
    _time = time;
};

CommandSetClock::CommandSetClock(time_value time)
{
    _action = Command::set_clock;
    _time = time;
};