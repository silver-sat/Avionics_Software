/**
 * @file CommandFactory.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Generate command object
 * @version 1.1.0
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

    CommandFactory(String tokens[], size_t token_count);

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
    // todo: single token limit for radio board and command factory
    const size_t _token_limit{10};
};

#endif // COMMANDFACTORY_H
