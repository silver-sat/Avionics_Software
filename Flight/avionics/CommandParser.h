/**
 * @file CommandParser.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Collect command and parse parameters
 * @version 1.2.0
 * @date 2022-09-27
 *
 * This file declares the class which parses command parameters
 */

#pragma once

#include <Arduino.h>

/**
 * @brief CommandParser constants
 *
 */

constexpr size_t command_parameter_limit{10};  /**< maximum command parameters */

/**
 * @brief Collect command and parse parameters
 *
 */
class CommandParser final
{
public:

    /**
     * @brief Parse command parameters
     *
     */

    bool parse_parameters(const String &command_string, String command_tokens[], size_t &token_count);
};