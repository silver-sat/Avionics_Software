/**
 * @file SilverSat_FRAM_mock.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Mock FRAM for demonstration and testing
 * @version 1.0.0
 * @date 2022-06-22
 *
 *
 */

#include "SilverSat_FRAM_mock.h"

// @brief Construct a new FRAM object

FRAM::FRAM()
{
    _i2caddr = FRAM_DEFAULT_ADDRESS;
}

// Start the session

bool FRAM::begin(uint8_t i2caddr, void *theWire)
{
    _i2caddr = i2caddr;
    return true;
}

// Write a byte

bool FRAM::write(uint16_t addr, uint8_t value)
{
    _memory[addr % _memory_size] = value;
    return true;
}

// Read a byte

uint8_t FRAM::read(uint16_t addr)
{
    return _memory[addr % _memory_size];
}

// Write multiple bytes

bool FRAM::write(uint16_t addr, uint8_t *buffer, uint16_t num)
{
    while (num--)
    {
        write(addr++, buffer[0]);
        buffer++;
    }
    return true;
}

// Read multiple bytes

bool FRAM::read(uint16_t addr, uint8_t *buffer, uint16_t num)
{
    for (uint16_t i = 0; i < num; i++)
    {
        buffer[i] = read(addr);
        addr++;
    }
    return true;
}
