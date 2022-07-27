/**
 * @file command.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat commands
 * @version 1.0.0
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

Command::operation toOperation(String command)
{
    if (command == "NoOperate")
    {
        return Command::operation::no_operate;
    }
    else if (command == "Invalid")
    {
        return Command::operation::invalid;
    }
    else if (command == "Unknown")
    {
        return Command::operation::unknown;
    }
    else
    {
        return Command::operation::invalid;
    };
};

/**
 * @brief Construct a new Command with no parameters
 *
 * @param operation command
 * @param Content parameters
 */

Command::Command(String command)
{
    _action = toOperation(command);
};

Command::operation Command::get_operation()
{
    return _action;
}
