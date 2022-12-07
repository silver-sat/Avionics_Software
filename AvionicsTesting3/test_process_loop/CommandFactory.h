/**
 * @file CommandFactory.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Generate command objects
 * @version 1.3.0
 * @date 2022-07-28
 *
 *
 */

#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

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

    Command *BuildCommand(String tokens[], size_t token_count);
};

#endif // COMMANDFACTORY_H
