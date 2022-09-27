/**
 * @file BuildCommand.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Generate command object
 * @version 1.2.0
 * @date 2022-07-28
 *
 *
 */

#ifndef BUILDCOMMAND_H
#define BUILDCOMMAND_H

#include "Command.h"

/**
 * @brief Factory for Command objects
 *
 */

class BuildCommand
{
public:
    /**
     * @brief Construct a new BuildCommand object
     *
     */

    BuildCommand(String tokens[], size_t token_count);

    /**
     * @brief Destroy the BuildCommand object
     *
     */

    ~BuildCommand();

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

#endif // BUILDCOMMAND_H
