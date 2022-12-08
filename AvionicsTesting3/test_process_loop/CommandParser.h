/**
 * @file CommandParser.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Collect command, validate signature, and parse parameters
 * @version 1.2.0
 * @date 2022-09-27
 *
 *
 */

#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <Arduino.h>

/**
 * @brief CommandParser constants
 *
 */

constexpr char command_message_separator{'|'}; /**< separator for signed command */
constexpr size_t buffer_token_limit{4};        /**< number of signed command sections */
constexpr size_t maximum_sequence_length{10};  /**< maximum digits in sequence number */
constexpr size_t maximum_command_length{200};  /**< maximum characters in command */
constexpr size_t command_parameter_limit{10};  /**< maximum command parameters */
constexpr size_t salt_size{16};                /**< salt size for HMAC */
constexpr size_t secret_size{16};              /**< secret size for HMAC */
constexpr size_t HMAC_size{32};                /**< HMAC size */

/**
 * @brief Collect command, validate signature, parse parameters
 *
 */
class CommandParser
{
public:
    /**
     * @brief Parse command parameters
     *
     */

    bool parse_parameters(const String &command_string, String command_tokens[], size_t &token_index);

    /**
     * @brief Validate the commmand signature
     *
     */

    bool validate_signature(String &buffer, String &command_string, const bool validation_required, long &command_sequence);
};

#endif // COMMANDPARSER_H