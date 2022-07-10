/**
 * @file SilverSat_I2C_mock.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Mock I2C interface for demonstration and testing
 * @version 1.0.0
 * @date 2022-07-10
 *
 *
 */

#ifndef SILVERSAT_I2C_MOCK_H
#define SILVERSAT_I2C_MOCK_H

#include <Arduino.h>

class I2C
{
public:
    I2C();
    void begin();
    uint8_t requestFrom(uint8_t address, size_t quantity, bool stopBit);
    int available();
    int read();

private:
    size_t _quantity;
};

#endif
