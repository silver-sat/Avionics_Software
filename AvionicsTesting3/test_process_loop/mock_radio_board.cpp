/**
 * @file mock_radio_board.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Mock Radio Board for Avionics testing
 * @version 1.2.0
 * @date 2022-07-24
 *
 *
 */

#include "mock_radio_board.h"
#include "arduino_secrets.h"
#include "log_utility.h"
#include "hexToByteArray.h"
#include <BLAKE2s.h>

/**
 * @brief Construct a new Mock Radio Board:: Mock Radio Board object
 *
 */

MockRadioBoard::MockRadioBoard(){};

/**
 * @brief Mock Radio Board Destructor
 *
 */

MockRadioBoard::~MockRadioBoard()
{
    // Free storage for command
    if (_factory)
    {
        delete _factory;
        _factory = NULL;
    }
};

/**
 * @brief initialize the Radio Board
 *
 * @return true successful
 * @return false error
 */

bool MockRadioBoard::begin()
{
    Log.traceln("Radio Board initializing");
    return true;
};

/**
 * @brief Notify radio board to deploy antenna
 *
 * @return true successful
 * @return false error
 */

bool MockRadioBoard::deploy_antenna()
{
    auto message = Message(Message::local_command, "DeployAntenna");
    return send_message(message);
};

/**
 * @brief Check for command
 *
 * @return true no command or successful
 * @return false error
 */

bool MockRadioBoard::check_for_command()
{
    if (command_received())
    {
        Log.verboseln("Command code: %d", _command->get_operation());
        _command->acknowledge_command();
        Log.traceln("Command acknowledged");
        if (_command->execute_command())
        {
            Log.traceln("Executed (%l executed, %l failed)", ++_successful_commands, _failed_commands);
            return true;
        }
        else
        {
            Log.errorln("Failed (%l executed, %l failed)", _successful_commands, ++_failed_commands);
            return false;
        };
    };
    return true;
};

/**
 * @brief Assemble command from Serial1 port
 *
 * @return true command available
 * @return false no command available
 */

bool MockRadioBoard::command_received()
{
    while (Serial1.available())
    {
        char character = Serial1.read();
        if (character == '\n')
        {
            _end_of_line = true;
            break;
        }
        else
        {
            // todo: check for buffer overflow
            _buffer += character;
        }
    };

    if (_end_of_line)
    {
        Log.infoln("Command received (sequence %l): %s", ++_commands_received, _buffer.c_str());
        make_command(_buffer);
        _buffer = "";
        _end_of_line = false;
        return true;
    };

    return false;
};

/**
 * @brief Parse command parameters
 *
 * @param command_string command string
 * @param command_tokens output: tokens
 * @param token_count output: number of tokens
 * @return true successful
 * @return false failure
 */

bool MockRadioBoard::parse_parameters(const String &command_string, String command_tokens[], size_t &token_index)
{

    Log.verboseln("Parsing command");
    token_index = 0;
    for (auto string_index = 0; string_index < command_string.length(); string_index++)
    {
        if (command_string.charAt(string_index) != ' ')
        {
            // todo: check for buffer overflow
            command_tokens[token_index] += command_string.charAt(string_index);
        }
        else
        {
            Log.verboseln("Token processed: %s", command_tokens[token_index].c_str());
            if (token_index++ > _command_token_limit)
            {
                Log.warningln("Too many command parameters");
                return false;
            }
        }
    }

    Log.verboseln("Token processed: %s", command_tokens[token_index].c_str());
    if (token_index > _command_token_limit)
    {
        Log.warningln("Too many command parameters");
        return false;
    }
    return true;
}

/**
 * @brief Validate the commmand signature
 *
 * @param buffer sequence, salt, command and HMAC
 * @param command_string output: command and parameters
 * @return true if valid
 * @return false if invalid
 */

bool MockRadioBoard::validate_signature(String &buffer, String &command_string)
{
    buffer.trim();
    size_t buffer_index = buffer.indexOf(_command_message_separator);

    if (buffer_index == -1)
    {
        Log.verboseln("Command is not signed");
        command_string = buffer;
    }
    else
    {

        Log.verboseln("Command is signed", _command_message_separator);

        // tokenize the buffer

        String buffer_tokens[_buffer_token_limit]{};
        size_t buffer_token_index{0};
        size_t token_start_index{0};
        for (auto buffer_token_index = 0; buffer_token_index < _buffer_token_limit; buffer_token_index++)
        {
            auto token_end_index = buffer.indexOf(_command_message_separator, token_start_index);
            buffer_tokens[buffer_token_index] = buffer.substring(token_start_index, token_end_index++);
            token_start_index = token_end_index;
        }
        command_string = buffer_tokens[2];

        // validate sequence number

        for (auto index = 0; index < buffer_tokens[0].length(); index++)
        {
            if (!isDigit(buffer_tokens[0].charAt(index)))
            {
                if (_validation_required)
                {
                    Log.errorln("Sequence is not a digit");
                    return false;
                }
                else
                {
                    Log.warningln("Sequence is not a digit");
                    break;
                }
            }
        }

        long command_sequence{buffer_tokens[0].toInt()};
        if (command_sequence != _command_sequence)
        {
            if (_validation_required)
            {

                Log.errorln("Command sequence invalid");
                return false;
            }
            else
            {
                Log.warningln("Command sequence invalid");
            }
        }
        else
        {
            Log.verboseln("Command sequence is valid");
            _command_sequence++;
        }

        // todo: check for validation requirement
        // todo: handle variable length sequence
        // todo: refactor lengths
        // todo: check for valid lengths

        const size_t sequence_length{buffer_tokens[0].length()};
        byte sequence[10]{};
        buffer_tokens[0].getBytes(sequence, 10);

        const size_t salt_length{buffer_tokens[1].length()};
        byte salt[17]{};
        hexCharacterStringToBytes(salt, buffer_tokens[1].c_str());

        const size_t command_length{buffer_tokens[2].length()};
        byte command[50]{};
        buffer_tokens[2].getBytes(command, 50);

        const size_t sourceHMAC_length = buffer_tokens[3].length();
        byte sourceHMAC[33]{};
        hexCharacterStringToBytes(sourceHMAC, buffer_tokens[3].c_str());

        const size_t secret_length = 16;
        const byte secret[]{SECRET_HASH_KEY};

        byte hash[_hash_size];

        BLAKE2s blake{};
        blake.resetHMAC(&secret, 16);
        blake.update(&sequence, sequence_length);
        blake.update(&_command_message_separator, 1);
        blake.update(&salt, 16);
        blake.update(&_command_message_separator, 1);
        blake.update(&command, command_length);
        blake.finalizeHMAC(secret, 16, hash, _hash_size);
        String HMAC{};
        for (auto index = 0; index < _hash_size; index++)
        {
            if (hash[index] < 0x10)
            {
                HMAC += "0";
            };
            HMAC += String(hash[index], HEX);
        }

        Log.verboseln("Computed HMAC: %s", HMAC.c_str());
        if (HMAC == buffer_tokens[3])
        {
            Log.traceln("Command signature valid");
            return true;
        }
        else
        {
            if (_validation_required)
            {
                Log.errorln("Command signature invalid");
                return false;
            }
            else
            {
                Log.warningln("Command signature invalid");
                return true;
            }
        }
    }
    return true;
};

/**
 * @brief Make command object
 *
 * @return next command to process
 *
 */

bool MockRadioBoard::make_command(String buffer)
{

    // destroy the previous factory

    if (_factory)
    {
        delete _factory;
        _factory = NULL;
    }

    // validate signature

    String command_string;
    validate_signature(buffer, command_string);

    // tokenize the command string and create the command object

    String command_tokens[_command_token_limit]{};
    size_t token_count{0};
    if (parse_parameters(command_string, command_tokens, token_count))
    {
        Log.traceln("Constructing command object");
        _command = (new CommandFactory(command_tokens, token_count))->get_command();
        return true;
    }
    else
    {
        return false;
    }
};

/**
 * @brief Send beacon
 *
 * @return true successful
 * @return false error
 */

void MockRadioBoard::send_beacon(Beacon beacon)
{
    Log.noticeln("Transmitting beacon %s %s", _call_sign.c_str(), beacon.get_message().c_str());
};

/**
 * @brief Send message
 *
 * @return true successful
 * @return false error
 */

bool MockRadioBoard::send_message(Message message)
{
    Log.noticeln("Sending message: %s", message.get_message().c_str());
    return true;
};
