//
// Mock FRAM for demonstration and testing
// Lee A. Congdon
// 22 June 2022
//
// Based on Adafruit_FRAM_I2C
//

#include "fram_mock.h"

// Constructor

Fram::Fram(void) {

}

// Public functions

// Start the session

bool Fram::begin(uint8_t i2caddr, void* theWire) {
    _i2caddr = i2caddr;
    return true;
}

// Write a byte

bool Fram::write(uint16_t addr, uint8_t value) {
    _memory[addr % _memory_size] = value;
    return true;
}

// Read a byte

uint8_t Fram::read(uint16_t addr) {
    return _memory[addr % _memory_size];
}

// Write multiple bytes

bool Fram::write(uint16_t addr, uint8_t *buffer, uint16_t num) {
    while (num--) {
        write(addr++, buffer[0]);
        buffer++;
    }
    return true;
}

// Read multiple bytes

bool Fram::read(uint16_t addr, uint8_t *buffer, uint16_t num) {
    for (uint16_t i = 0; i < num; i++) {
        buffer[i] = read(addr);
        addr++;
    }
    return true;
}
