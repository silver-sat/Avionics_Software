/**
 * @file CommandFactory.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Generate command objects
 * @version 1.3.0
 * @date 2022-07-28
 *
 * This file declares the class used to build a new ground command.
 */

#pragma once

#include "Commands.h"

/**
 * @brief Factory for Command objects
 *
 */

class CommandFactory final
{
public:
    /**
     * @brief Construct a new Command object
     *
     */

    Command *BuildCommand(const String tokens[], const size_t token_count);
};