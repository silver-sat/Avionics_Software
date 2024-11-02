/**
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Manage command processing
 *
 * This file declares the class that checks for ground commands, validates
 * and retrieves them and checks for local responses and commands and processes them
 *
 */

#pragma once

#include "CommandWarehouse.h"

constexpr size_t command_parameter_limit{10}; /**< maximum command parameters */

class CommandProcessor final
{
public:
    bool check_for_command();
    String get_sequence();
    bool get_validation();

private:
    Command *get_command(const String &buffer);
    bool validate_signature(const String &buffer);
    bool parse_parameters(const String &command_string, String command_tokens[], size_t &token_count);
    long m_command_sequence{1};
    CommandWarehouse command_warehouse{};
    long m_successful_commands{0};
    long m_failed_commands{0};
    bool m_validate_sequence{true};
};