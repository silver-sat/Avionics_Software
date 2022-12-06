/**
 * @file CollectCommand.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Collect command, validate signature, and parse parameters
 * @version 1.0.0
 * @date 2022-09-27
 *
 *
 */

#ifndef COLLECTCOMMAND_H
#define COLLECTCOMMAND_H

#include "BuildCommand.h"

/**
 * @brief CollectCommand constants
 *
 */

constexpr char command_message_separator{'|'}; /**< separator for signed command */
constexpr size_t buffer_token_limit{4};        /**< number of signed command sections */
constexpr size_t maximum_sequence_length{10};  /**< maximum digits in sequence number */
constexpr size_t maximum_command_length{200};  /**< maximum characters in command */
constexpr size_t command_token_limit{10};      /**< maximum command parameters */
constexpr size_t salt_size{16};                /**< salt size for HMAC */
constexpr size_t secret_size{16};              /**< secret size for HMAC */
constexpr size_t HMAC_size{32};                /**< HMAC size */

/**
 * @brief Collect command, validate signature, parse parameters
 * 
 */
class CollectCommand
{
public:
    /**
     * @brief Construct the CollectCommand::CollectCommand object
     *
     */

    CollectCommand() = default;

    /**
     * @brief Check for command
     *
     */

    bool check_for_command();

    /**
     * @brief Get command
     *
     */

    ExecuteCommand *get_command();

    /**
     * @brief Parse command parameters
     *
     */

    bool parse_parameters(const String &command_string, String command_tokens[], size_t &token_index);

    /**
     * @brief Validate the commmand signature
     *
     */

    bool validate_signature(String &buffer, String &command_string);

    /**
     * @brief Make a command
     *
     */

    bool make_command(String buffer);

    /**
     * @brief Delete the command and the factory
     *
     */
    bool delete_command();

private:
    char m_command_buffer[maximum_command_length + 1]{""};
    bool m_validation_required{false};
    BuildCommand *m_factory{};
    ExecuteCommand *m_command{};
    long m_successful_commands{0};
    long m_failed_commands{0};
    long m_command_sequence{1};
};

#endif // COLLECTCOMMAND_H