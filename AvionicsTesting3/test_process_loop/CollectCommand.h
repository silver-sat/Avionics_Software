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
 * @brief Command parameters
 *
 */

constexpr char _command_message_separator{'|'}; /**< separator for signed command */
constexpr size_t _buffer_token_limit{4};        /**< number of signed command sections */
constexpr size_t _maximum_sequence_length{10};  /**< maximum digits in sequence number */
constexpr size_t _maximum_command_length{200};  /**< maximum characters in command */
constexpr size_t _command_token_limit{10};      /**< maximum command parameters */
constexpr size_t _salt_size{16};                /**< salt size for HMAC */
constexpr size_t _secret_size{16};              /**< secret size for HMAC */
constexpr size_t _HMAC_size{32};                /**< HMAC size */

class CollectCommand
{
public:
    /**
     * @brief Construct a new CollectCommand::CollectCommand object
     *
     */

    CollectCommand();

    /**
     * @brief Destroy the CollectCommand::CollectCommand object
     *
     */

    ~CollectCommand();

    /**
     * @brief Check for command
     *
     * @return true no command or successful
     * @return false error
     */

    bool check_for_command();

    /**
     * @brief Get command
     *
     * @return next command to process
     */

    ExecuteCommand *get_command();

    /**
     * @brief Parse command parameters
     *
     * @param command_string command string
     * @param command_tokens output: tokens
     * @param token_index output: number of tokens
     * @return true successful
     * @return false failure
     */

    bool parse_parameters(const String &command_string, String command_tokens[], size_t &token_index);

    /**
     * @brief Validate the commmand signature
     *
     * @param buffer sequence, salt, command and HMAC
     * @param command_string output: command and parameters
     * @return true if valid
     * @return false if invalid
     */

    bool validate_signature(String &buffer, String &command_string);

    /**
     * @brief Make a command
     *
     * @param buffer input string
     * @return true successful
     * @return false error
     */

    bool make_command(String buffer);

    /**
     * @brief Delete the command and the factory
     *
     * @return true successful
     * @return false erroe
     */
    bool delete_command();

private:
    char _command_buffer[_maximum_command_length + 1]{""};
    bool _validation_required{false};
    BuildCommand *_factory{};
    ExecuteCommand *_command{};
    long _successful_commands{0};
    long _failed_commands{0};
    long _command_sequence{1};
};

#endif // COLLECTCOMMAND_H