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
#include "arduino_secrets.h"    /**< shared secret with ground station */
#include "log_utility.h"
#include <CRC32.h>
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
    Log.traceln("Sending local command: deploy antenna");
    Serial1.write(FEND);
    Serial1.write(DEPLOY_ANTENNA);
    Serial1.write(FEND);
    return true;
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
        _command->acknowledge_command();
        Log.traceln("Command acknowledged");
        if (_command->execute_command())
        {
            Log.traceln("Executed (%l executed, %l failed, next sequence %l)", ++_successful_commands, _failed_commands, _command_sequence);
            return true;
        }
        else
        {
            Log.errorln("Failed (%l executed, %l failed, next sequence %i)", _successful_commands, ++_failed_commands, _command_sequence);
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
        if (_received_start)
        {
            if (_receiving_type)
            {
                _receiving_type = false;
                if (character != DATA_FRAME)
                {
                    Log.errorln("Type is not 0: 0x%x", character);
                }
            }

            else if (_received_escape)
            {
                switch (character)
                {
                case TFEND:
                    _buffer += FEND;
                    _received_escape = false;
                    break;
                case TFESC:
                    _buffer += FESC;
                    _received_escape = false;
                    break;
                default:
                    Log.errorln("FESC followed by invalid character, ignored: 0x%x", character);
                    _buffer += character;
                    _received_escape = false;
                    break;
                }
            }

            else if (character == FESC)
            {
                _received_escape = true;
            }

            else if (character == FEND)
            {
                _buffer.remove(0, header_size);
                Log.infoln("Command received (count %l): %s", ++_commands_received, _buffer.c_str());
                make_command(_buffer);
                _buffer = "";
                _received_start = false;
                return true;
            }

            else
            {
                _buffer += character;
            }
        }
        else if (character == FEND)
        {
            _received_start = true;
            _receiving_type = true;
        }
        else
        {
            Log.errorln("FEND is not first character of command: 0x%x", character);
        }
    }
    return false;
};

/**
 * @brief Helper function for hexadecimal text to binary conversion
 *
 * @param input a character in one of the ranges 0-9, a-f, or A-F
 * @return int value of the hexadecimal representation (e.g. "A" == 0x0A, decimal 10)
 */

int char2int(const char input)
{
    if (input >= '0' && input <= '9')
        return input - '0';
    if (input >= 'A' && input <= 'F')
        return input - 'A' + 10;
    if (input >= 'a' && input <= 'f')
        return input - 'a' + 10;
    return 0; // invalid data
};

/**
 * @brief Convert hexadecimal text representation to binary values
 *
 * @param src hexadecimal representation
 * @param target binary values
 */

// This function assumes src to be a zero terminated sanitized string with
// an even number of [0-9a-f] characters, and target to be sufficiently large

void hex2bin(const char *src, byte *target)
{
    while (*src && src[1])
    {
        *(target++) = (char2int(*src) << 4) + char2int(src[1]);
        src += 2;
    }
};

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
                Log.infoln("Command sequence invalid");
            }
        }
        else
        {
            Log.verboseln("Command sequence is valid");
            _command_sequence++;
        }

        // todo: check for validation requirement
        // todo: check for valid lengths

        const size_t sequence_length{buffer_tokens[0].length()};
        byte sequence[_maximum_sequence_length]{};
        buffer_tokens[0].getBytes(sequence, _maximum_sequence_length);

        const size_t salt_length{buffer_tokens[1].length()};
        byte salt[_salt_size]{};
        hex2bin(buffer_tokens[1].c_str(), salt);

        const size_t command_length{buffer_tokens[2].length()};
        byte command[_maximum_command_length]{};
        buffer_tokens[2].getBytes(command, _maximum_command_length);

        const size_t sourceHMAC_length = buffer_tokens[3].length();
        byte sourceHMAC[_HMAC_size]{};
        hex2bin(buffer_tokens[3].c_str(), sourceHMAC);

        const size_t secret_length = 16;
        const byte secret[]{SECRET_HASH_KEY};

        byte HMAC[_HMAC_size];
        String hexHMAC{};

        BLAKE2s blake{};
        blake.resetHMAC(&secret, _secret_size);
        blake.update(&sequence, sequence_length);
        blake.update(&_command_message_separator, 1);
        blake.update(&salt, _salt_size);
        blake.update(&_command_message_separator, 1);
        blake.update(&command, command_length);
        blake.finalizeHMAC(secret, _secret_size, HMAC, _HMAC_size);
        for (auto index = 0; index < _HMAC_size; index++)
        {
            if (HMAC[index] < 0x10)
            {
                hexHMAC += "0";
            };
            hexHMAC += String(HMAC[index], HEX);
        }

        Log.verboseln("Computed HMAC: %s", hexHMAC.c_str());
        if (hexHMAC == buffer_tokens[3])
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
 * @brief Parse command parameters
 *
 * @param command_string command string
 * @param command_tokens output: tokens
 * @param token_index output: number of tokens
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
    String beacon_data = _call_sign + beacon.get_message();
    size_t beacon_length = beacon_data.length();
    Log.noticeln("Sending local command: beacon %s %s", _call_sign.c_str(), beacon.get_message().c_str());
    Serial1.write(FEND);
    Serial1.write(BEACON);
    Serial1.write(beacon_data.c_str());
    Serial1.write(FEND);
};

/**
 * @brief Send message
 *
 * @return true successful
 * @return false error
 */

bool MockRadioBoard::send_message(Message message)
{
    String message_data = message.get_message();
    size_t message_length = message_data.length();
    uint32_t checksum = CRC32::calculate(message_data.c_str(), message_length);
    Log.noticeln("Sending message: %s", message_data.c_str());
    Log.verboseln("Checksum: 0x%x", checksum);
    Serial1.write(FEND);
    Serial1.write(DATA_FRAME);
    Serial1.write(HEADER, 16);
    Serial1.write(message_data.c_str());
    Serial1.print(checksum, HEX);
    Serial1.write(FEND);
    return true;
};

/**
 * @brief Get Radio Board status
 *
 * @return String status
 */

String MockRadioBoard::get_status()
{
    Log.traceln("Sending local command: requesting Radio Board status");
    Serial1.write(FEND);
    Serial1.write(GET_RADIO_STATUS);
    Serial1.write(FEND);
    // todo: retrieve and store Radio Board status
    return "unknown";
};
