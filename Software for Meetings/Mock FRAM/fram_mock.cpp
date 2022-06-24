//
// Mock FRAM for example
// Lee A. Congdon
// 24 June 2022
//

#include "fram_mock.h"

// Constructor

Fram::Fram(void) {

}

// Public functions

// Start the session

bool Fram::begin(int i2caddr, void* Bus) {
    _i2caddr = i2caddr;
    return true;
}

// Write a byte

bool Fram::write(std::size_t addr, int value) {
    _memory[addr % _memory_size] = value;
    return true;
}

// Read a byte

int Fram::read(std::size_t addr) {
    return _memory[addr % _memory_size];
}

// Write multiple bytes

bool Fram::write(std::size_t addr, int *buffer, std::size_t num) {
    while (num--) {
        write(addr++, buffer[0]);
        buffer++;
    }
    return true;
}

// Read multiple bytes

bool Fram::read(std::size_t addr, int *buffer, std::size_t num) {
    for (auto i = 0; i < num; i++) {
        buffer[i] = read(addr);
        addr++;
    }
    return true;
}

