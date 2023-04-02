/**
 * @file Antenna.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Device driver for SilverSat antenna
 * @version 1.0.0
 * @date 2023-04-01
 *
 *
 */
#pragma once

#include <Adafruit_I2CDevice.h>

/**
 * @brief Antenna constants
 *
 */
constexpr unsigned ANTENNA_I2C_ADDRESS{0x33}; /**< antenna I2C address @hideinitializer */

class Antenna final
{
public:
    /**
     * @brief Deploy the antenna
     *
     * @return true successful
     * @return false failure
     */
    bool deploy();

private:
    Adafruit_I2CDevice m_i2c_dev{Adafruit_I2CDevice(ANTENNA_I2C_ADDRESS, &Wire1)};
};