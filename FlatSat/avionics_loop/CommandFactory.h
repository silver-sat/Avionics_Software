/**
 * @file CommandFactory.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Generate command objects
 * @version 1.3.0
 * @date 2022-07-28
 *
 *
 */

#pragma once

#include "Commands.h"

/**
 * @brief Factory for Command objects
 *
 */

class CommandFactory
{
public:
    /**
     * @brief Construct a new Command object
     *
     */

    Command *BuildCommand(const String tokens[], size_t token_count);
};