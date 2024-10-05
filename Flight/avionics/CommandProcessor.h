/**
 * @file CommandProcessor.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Manage command processing
 * @version 1.0.0
 * @date 2022-12-07
 *
 * This file declares the class that checks for ground commands, validates
 * and retrieves them and checks for local responses and commands and processes them
 *
 */

#pragma once

#include "CommandParser.h"
#include "CommandWarehouse.h"

/**
 * @brief Check for command from Radio Board, retrieve a Command object
 *
 */

class CommandProcessor final
{
public:
    /**
     * @brief Check for command
     *
     */

    bool check_for_command();

    /**
     * @brief Make a command
     *
     */

    Command *get_command(const String &buffer);

    /**
     * @brief Validate command signature
     *
     */

    bool validate_signature(const String &buffer);

private : 
    CommandParser command_parser {};
    CommandWarehouse command_warehouse{};
    long m_successful_commands{0};
    long m_failed_commands{0};
};