// convert a hex string such as "A489B1" into an array like [0xA4, 0x89, 0xB1].

#ifndef HEX_TO_BYTE_ARRAY
#define HEX_TO_BYTE_ARRAY

#include <Arduino.h>

void hexCharacterStringToBytes(byte *byteArray, const char *hexString);

void dumpByteArray(const byte * byteArray, const byte arraySize);

byte nibble(char c);

#endif // HEX_TO_BYTE_ARRAY