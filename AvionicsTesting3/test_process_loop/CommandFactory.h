/**
 * @file CommandFactory.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Generate the appropriate command object
 * @version 1.0.0
 * @date 2022-07-28
 *
 *
 */

#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

#include "Command.h"

/**
 * @brief Factory for Command objects
 *
 */
class CommandFactory
{
public:
    /**
     * @brief Construct a new Command Factory object
     *
     */

    CommandFactory();

    /**
     * @brief Construct a new Command Factory object
     *
     * @param command operation
     */

    CommandFactory(String command);

    /**
     * @brief Construct a new Command Factory object
     *
     * @param command operation
     * @param value integer parameter
     */

    CommandFactory(String command, int value);

    /**
     * @brief Construct a new Command Factory object
     *
     * @param command operation
     * @param time time value
     */

    CommandFactory(String command, time_value time);

    /**
     * @brief Destroy the Command Factory object
     *
     */

    ~CommandFactory();

    /**
     * @brief Get the command object
     *
     * @return Command*
     */

    Command *get_command();

private:
    Command *_command;
};

#endif
