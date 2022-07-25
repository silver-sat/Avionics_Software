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
    else
    {
        return Command::operation::invalid;
    };
};

/**
 * @brief Construct a new Command:: Command object
 *
 * @param operation command
 * @param Content parameters
 */

Command::Command(

    String command,
    Value data) : _action{toOperation(command)},
                  _values{0}
{};
