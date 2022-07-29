/**
 * @file Command.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat commands
 * @version 1.0.1
 * @date 2022-07-25
 *
 *
 */

#include "Command.h"

/**
 * @brief Acknowledge the command
 *
 */

void Command::acknowledge_command()
{
    Serial.println("Acknowledging command");
};

/**
 * @brief Execute the command
 *
 * @return true successful
 * @return false error
 */

bool Command::execute_command()
{
    Serial.println("Executing command");
    return true;
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

/**
 * @brief Construct a new Command No Operate:: Command No Operate object
 *
 */

CommandNoOperate::CommandNoOperate()
{
    _action = Command::no_operate;
};

/**
 * @brief Acknowledge NoOperate command
 * 
 */

void CommandNoOperate::acknowledge_command()
{
    Serial.println("Acknowledging NoOperate");
};

/**
 * @brief Execute NoOperate command
 * 
 * @return true successful
 */

bool CommandNoOperate::execute_command()
{
    Serial.println("Executing NoOperate");
    return true;
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