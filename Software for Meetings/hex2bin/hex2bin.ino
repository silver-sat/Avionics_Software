/**
 * @file hex2bin.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Convert hexadecimal text to binary representation
 * @version 1.0.0
 * @date 2022-09-24
 *
 */

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

void setup()
{
    Serial.begin(115200);
    while (!Serial)
    {
    }

// C string

    char data[]{"F0E010"};

    Serial.println(data);

//    for (auto index = 0; index < sizeof(data); index++)
//    {
//        Serial.print(data[index], HEX);
//        Serial.print(' ');
//    }
//    Serial.println();

    byte target[20]{0};
    hex2bin(data, target);
//    for (auto index = 0; index < 20; index++)
//    {
//        Serial.print(target[index], HEX);
//    }
//    Serial.println();

// Arduino String class

    String string_data{"F0E010"};
    
//    Serial.println(string_data);
//
//    for (auto index = 0; index < sizeof(data); index++)
//    {
//        Serial.print(string_data.charAt(index), HEX);
//        Serial.print(' ');
//    }
//    Serial.println();

    hex2bin(string_data.c_str(), target);
//    for (auto index = 0; index < 20; index++)
//    {
//        Serial.print(target[index], HEX);
//    }
    
}

void loop() {}
