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
 * @brief convert string to operation
 *
 * @param command string
 * @return operation
 */

Command* Command::create(String command)
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


    else
    {
        return new CommandInvalid();
    };
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
}

CommandPayComms::CommandPayComms()
{
    _action = Command::pay_comms;
};

CommandReportT::CommandReportT()
{
    _action = Command::report_t;
}

CommandTweeSlee::CommandTweeSlee()
{
    _action = Command::twee_slee;
}