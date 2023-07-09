/**
 * @file Antenna.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Device driver for SilverSat antenna
 * @version 1.1.0
 * @date 2023-04-01
 *
 *
 */
#pragma once

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wunused"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wdeprecated-copy"
#include <Adafruit_I2CDevice.h>
#pragma GCC diagnostic pop

/**
 * @brief Antenna constants
 *
 */
constexpr unsigned ANTENNA_I2C_ADDRESS{0x33}; /**< antenna I2C address @hideinitializer */

class Antenna final
{
public:
    /**
     * @brief Check antenna state
     * 
     */
    bool check();
    
    /**
     * @brief Deploy the antenna
     *
     */
    bool deploy();

private:
    Adafruit_I2CDevice m_i2c_dev{Adafruit_I2CDevice(ANTENNA_I2C_ADDRESS, &Wire1)};
};