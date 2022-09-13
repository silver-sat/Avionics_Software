/**
 * @file test_signing.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test the command signature function
 * @version 1.0.0
 * @date 2022-09-03
 *
 *
 */

#include "arduino_secrets.h"
#include <BLAKE2s.h>
#include <Arduino.h>

void setup()
{
    Serial.begin(115200);
    while (!Serial)
    {
    };
    const size_t _key_size{16};
    const byte secret[]{SECRET_HASH_KEY};
    const size_t _hash_size{32};
    const byte sequence{'1'};
    const byte _command_message_separator{'|'};
    const char salt[]{"ece4473b9e87597d459ab4d34097f5d0"};
    const char command[]{"NoOperate"};
    const byte SourceHMAC[]{"f5f6984dbdf2280f3503a792267f344140de4689ad7c7a390b42b8f5163e2c05"};
    byte hash[_hash_size];
    BLAKE2s blake{};
    blake.resetHMAC(&secret, sizeof(secret));
    blake.update(&sequence, sizeof(sequence));
    blake.update(&_command_message_separator, sizeof(_command_message_separator));
    blake.update(&salt, sizeof(salt)-1);
    blake.update(&_command_message_separator, sizeof(_command_message_separator));
    blake.update(&command, sizeof(command)-1);
    blake.finalizeHMAC(&secret, sizeof(secret), hash, _hash_size);
    String ComputedHMAC{};
    Serial.print("Computed HMAC: ");
    for (auto index = 0; index < _hash_size; index++)
    {
        if (hash[index]<0x10) {Serial.print("0");}
        Serial.print(String(hash[index], HEX));
        ComputedHMAC += String(hash[index], HEX);
    }
    Serial.println();
    // Serial.print("Source   HMAC: ");
    // Serial.println(SourceHMAC);
    Serial.print("_hash_size: ");
    Serial.println(_hash_size);
    Serial.print("_key_size: ");
    Serial.println(_key_size);
    Serial.print("secret: ");
    for (auto index = 0; index < _key_size; index++)
    {
        if (secret[index]<0x10) {Serial.print("0");}
        Serial.print(String(secret[index], HEX));
    }
    Serial.println();
    Serial.print("sequence: ");
    Serial.println(sequence, HEX);
    Serial.print("command: ");
    Serial.println(command);
    Serial.print("salt: ");
    Serial.println(salt);
    Serial.print("separator: ");
    Serial.println(_command_message_separator);
}

void loop(){};