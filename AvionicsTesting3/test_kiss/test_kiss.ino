/**
 * @file test_kiss.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test KISS conversion functions
 * @version 1.0.0
 * @date 2022-09-21
 *
 *
 */

#include <Arduino.h>

constexpr byte FEND{'\xC0'};
constexpr byte FESC{'\xDB'};
constexpr byte TFEND{'\xDC'};
constexpr byte TFESC{'\xDD'};

String buffer{};
bool received_start{false};
bool receiving_type{false};
bool received_escape{false};

/**
 * @brief Set up the serial ports
 *
 */

void setup()
{
    Serial.begin(115200);
    while (!Serial)
    {
    }
    Serial1.begin(115200);
    while (!Serial1)
    {
    }
    Serial.println("KISS testing");
}

/**
 * @brief Receive and print commands
 *
 */

void loop()
{
    while (Serial1.available())
    {
        char character = Serial1.read();
        Serial.print("Character: ");
        if (isPrintable(character))
        {
            Serial.print(character);
        }
        else
        {
            Serial.print(' ');
        }
        Serial.print(' ');
        if (character <= '\x0F')
        {
            Serial.print('0');
        }
        Serial.println(byte(character), HEX);

        if (received_start)
        {
            if (receiving_type)
            {
                receiving_type = false;
                if (character != 0)
                {
                    Serial.println("Error: type is not 0");
                }
            }

            else if (received_escape)
            {
                switch (character)
                {
                case TFEND:
                    buffer += FEND;
                    received_escape = false;
                    break;
                case TFESC:
                    buffer += FESC;
                    received_escape = false;
                    break;
                default:
                    Serial.println("Error: FESC followed by invalid character, ignored");
                    buffer += character;
                    received_escape = false;
                    break;
                }
            }

            else if (character == FESC)
            {
                received_escape = true;
            }

            else if (character == FEND)
            {
                Serial.print("Received command: ");
                Serial.println(buffer.c_str());
                buffer = "";
                received_start = false;
            }

            else
            {
                buffer += character;
            }
        }
        else if (character == FEND)
        {
            received_start = true;
            receiving_type = true;
        }
        else
        {
            Serial.println("Error: FEND is not first character of command");
        }
    }
}