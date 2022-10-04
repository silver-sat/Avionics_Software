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

#include "ExecuteCommand.h"

/**
 * @brief BuildCommand constants
 *
 */

// todo: single token limit for radio board and command factory
constexpr size_t m_token_limit{10};

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
     * @return ExecuteCommand*
     */

    ExecuteCommand *get_command();

private:
    ExecuteCommand *m_command;
};

#endif // BUILDCOMMAND_H
