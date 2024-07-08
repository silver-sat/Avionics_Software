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

constexpr size_t maximum_sequence_length{10};  /**< maximum digits in sequence number */
constexpr size_t maximum_command_length{256};  /**< maximum characters in command */
constexpr size_t command_parameter_limit{10};  /**< maximum command parameters */
constexpr size_t salt_size{16};                /**< salt size for HMAC */
constexpr size_t secret_size{16};              /**< secret size for HMAC */
constexpr size_t HMAC_size{32};                /**< HMAC size */

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