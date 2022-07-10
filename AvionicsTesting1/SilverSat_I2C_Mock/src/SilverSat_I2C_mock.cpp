/**
 * @file SilverSat_I2C_mock.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test mock I2C interface
 * @version 1.0.0
 * @date 2022-07-10
 * 
 * 
 */

#include <SilverSat_I2C_mock.h>

I2C::I2C()
{
}

/**
 * @brief Connect to bus (no operation)
 * 
 */
void I2C::begin(void)
{

}

/**
 * @brief Request bytes from a device on the bus 
 * 
 * @param address bus address
 * @param quantity number of bytes
 * @param stopBit ir true, close connection
 * @return uint8_t number of bytes available
 */
uint8_t I2C::requestFrom(uint8_t address, size_t quantity, bool stopBit)
{
    _quantity = quantity;
    return quantity;
}

/**
 * @brief Return number of bytes available
 * 
 * @return int number of bytes available
 */
int I2C::available(void)
{
    return _quantity;
}

/**
 * @brief Return character
 * 
 * @return int character
 */
int I2C::read(void)
{
    return '*';
}
