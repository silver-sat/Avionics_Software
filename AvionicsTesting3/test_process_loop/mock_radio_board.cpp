/**
 * @file mock_radio_board.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Mock Radio Board for Avionics testing
 * @version 1.1.0
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
 * @brief Process commands
 *
 * @return true no command or successful
 * @return false error
 */

bool MockRadioBoard::check_command()
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
 * @brief Check for command
 *
 * @return true command available
 * @return false no command available
 */

bool MockRadioBoard::command_received()
{
    while (Serial.available())
    {
        char character = Serial.read();
        if (character == '\n')
        {
            _end_of_line = true;
            break;
        }
        else
        {
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
 * @brief Make command object
 *
 * @return next command to process
 *
 */

bool MockRadioBoard::make_command(String buffer)
{

    // destroy the last factory

    if (_factory)
    {
        delete _factory;
        _factory = NULL;
    }

    buffer.trim();
    String command_string{};
    size_t buffer_index = buffer.indexOf(_command_message_separator);

    if (buffer_index == -1)
    {
        Log.verboseln("Command is not signed");
        command_string = buffer;
    }
    else
    {
        Log.verboseln("Command has signature separator %c", _command_message_separator);

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
        Log.verboseln("tokens[0]: %s", buffer_tokens[0].c_str());
        Log.verboseln("tokens[1]: %s", buffer_tokens[1].c_str());
        Log.verboseln("tokens[2]: %s", buffer_tokens[2].c_str());
        Log.verboseln("tokens[3]: %s", buffer_tokens[3].c_str());

        // todo: check for validation requirement
        // todo: handle variable length sequence
        // todo: refactor lengths

        size_t sequence_length = buffer_tokens[0].length();
        Serial.print("sequence_length: "); Serial.println(sequence_length);
        byte sequence[1]{'1'};
        Serial.println("sequence");
        dumpByteArray(sequence, sequence_length);

        size_t salt_length = buffer_tokens[1].length();
        Serial.print("salt_length: "); Serial.println(salt_length);
        byte salt[16] = {0};
        hexCharacterStringToBytes(salt, buffer_tokens[1].c_str());
        Serial.println("salt");
        dumpByteArray(salt, salt_length / 2);

        size_t command_length = buffer_tokens[2].length();
        Serial.print("command_length: "); Serial.println(command_length);
        Serial.print("command: "); Serial.println(buffer_tokens[2]);
        
        size_t sourceHMAC_length = buffer_tokens[3].length();
        Serial.print("sourceHMAC_length: "); Serial.println(sourceHMAC_length);
        byte sourceHMAC[32] = {0};
        hexCharacterStringToBytes(sourceHMAC, buffer_tokens[3].c_str());
        Serial.println("sourceHMAC");
        dumpByteArray(sourceHMAC, (sourceHMAC_length + 1) / 2);

        const byte secret[]{SECRET_HASH_KEY};
        size_t secret_length = sizeof(secret);
        Serial.print("secret_length: "); Serial.println(secret_length);
        Serial.println("secret: ");
        dumpByteArray(secret, secret_length);

        byte hash[_hash_size];
        Serial.print("hash_size: "); Serial.println(_hash_size);
        
        BLAKE2s blake{};
        blake.resetHMAC(&secret, secret_length);
        blake.update(&sequence, sequence_length);
        // blake.update(&_command_message_separator, sizeof(_command_message_separator));
        // blake.update(&salt, salt_length);
        // blake.update(&_command_message_separator, sizeof(_command_message_separator));
        // blake.update(&command, command_length);
        blake.finalizeHMAC(secret, sizeof(secret), hash, _hash_size);
        String HMAC{};
        for (auto index = 0; index < _hash_size; index++)
        {
            if (hash[index]<0x10) {HMAC+="0";};
            HMAC += String(hash[index], HEX);
        }
        Log.verboseln("Computed HMAC: %s", HMAC.c_str());
        if (HMAC == buffer_tokens[3])
        {
            Log.traceln("Command signature validated");
        }
        else
        {
            if (_validation_required)
            {
                Log.errorln("Command signature invalid");
                command_string = "Invalid";
            }
            else
            {
                Log.warningln("Command signature invalid");
            }
        }
    }

    // tokenize the command string

    Log.verboseln("Parsing the command parameters");
    String command_tokens[_command_token_limit]{};
    size_t command_token_index{0};
    for (auto string_index = 0; string_index < command_string.length(); string_index++)
    {
        if (command_string.charAt(string_index) != ' ')
        {
            command_tokens[command_token_index] += command_string.charAt(string_index);
        }
        else
        {
            command_token_index++;
            if (command_token_index > _command_token_limit)
            {
                Log.warningln("Too many command parameters");
                break;
            }
        }
    }
    Log.traceln("Constructing new command");

    // Return the new command

    _command = (new CommandFactory(command_tokens, command_token_index))->get_command();
    return true;
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
