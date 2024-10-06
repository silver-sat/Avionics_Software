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

#include "CommandWarehouse.h"

/**
 * @brief CommandProcessor constants
 *
 */

constexpr size_t command_parameter_limit{10}; /**< maximum command parameters */

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
     * @brief Get sequence
     *
     */

    String get_sequence();

private:
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

    /**
     * @brief Parse command parameters
     *
     */

    bool parse_parameters(const String &command_string, String command_tokens[], size_t &token_count);

    long m_command_sequence{1};
    CommandWarehouse command_warehouse{};
    long m_successful_commands{0};
    long m_failed_commands{0};
};