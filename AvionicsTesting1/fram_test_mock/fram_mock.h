//
// Mock FRAM for demonstration and testing
// Lee A. Congdon
// 22 June 2022
//
// Based on Adafruit_FRAM_I2C
//

#ifndef FRAM_MOCK_H
#define FRAM_MOCK_H

#define FRAM_DEFAULT_ADDRESS (0x50)
#define FRAM_MEMORY_SIZE 32768

#include <Arduino.h>

class Fram {
public:
    Fram(void);

    bool begin(uint8_t i2caddr = FRAM_DEFAULT_ADDRESS, void *theWire = NULL);
    bool write(uint16_t addr, uint8_t value);
    uint8_t read(uint16_t addr);
    bool write(uint16_t addr, uint8_t *buffer, uint16_t num);
    bool read(uint16_t addr, uint8_t *buffer, uint16_t num);

// Write object to FRAM

template <class T> uint16_t writeObject(uint16_t addr, const T &value) {
    const byte *p = (const byte *)(const void *)&value;
    uint16_t n;
    for (n = 0; n < sizeof(value); n++) {
      write(addr++, *p++);
    }
    return n;
  }

// Read object from FRAM

template <class T> uint16_t readObject(uint16_t addr, T &value) {
    byte *p = (byte *)(void *)&value;
    uint16_t n;
    for (n = 0; n < sizeof(value); n++) {
      *p++ = read(addr++);
    }
    return n;
  }

protected:
    uint8_t _i2caddr = 0;
    const uint16_t _memory_size = FRAM_MEMORY_SIZE;
    uint8_t _memory[FRAM_MEMORY_SIZE];

};

#endif
