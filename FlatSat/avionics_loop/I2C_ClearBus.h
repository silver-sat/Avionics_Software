/**
 * I2C_ClearBus
 * (http://www.forward.com.au/pfod/ArduinoProgramming/I2C_ClearBus/index.html)
 * (c)2014 Forward Computing and Control Pty. Ltd.
 * NSW Australia, www.forward.com.au
 * This code may be freely used for both private and commerical use
 */

#pragma once

#include <Arduino.h>

/**
 * @brief clear bus contants
 *
 */

constexpr int bus_clear{0};       /**< bus is clear */
constexpr int SCL_low{1};         /**< SCL clock line held low */
constexpr int SCL_low_stretch{2}; /**< SCL clock line held low by slave clock stretch */
constexpr int SDA_low{3};         /**< SDA data line held low */

/**
 * @brief Clear the I2C bus
 * 
 */

int I2C_ClearBus(const uint8_t SDA, const uint8_t SCL);
