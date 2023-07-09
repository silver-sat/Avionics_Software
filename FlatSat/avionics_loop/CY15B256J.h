/**
 * @file CY15B256J.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Device Driver for CY15B256 FRAM
 * @version 1.0.0
 * @date 2022-10-17
 *
 * Based on Adafruit_FRAM_I2C
 *
 * This file declares the class that interfaces with the Avionics Board FRAM
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
#include <Adafruit_EEPROM_I2C.h>
#pragma GCC diagnostic pop

// todo: resolve object creation location and use standard address

constexpr unsigned FRAM_I2C_ADDRESS{0x50};  /**< FRAM I2C address @hideinitializer */
#define CY15B256J_DEFAULT_ADDRESS \
    (0x50) ///<* 1010 + A2 + A1 + A0 = 0x50 default */
#define CY15B256J_SECONDARY_ADDRESS \
    (0x7C) ///< secondary ID for manufacture id info

/**
 * @brief Class that stores state and functions for interacting with
 *        I2C FRAM chips
 *
 */
class CY15B256J final : public Adafruit_EEPROM_I2C
{
public:
    CY15B256J(void);

    bool begin(uint8_t addr = CY15B256J_DEFAULT_ADDRESS, TwoWire *theWire = &Wire);
    void getDeviceID(uint16_t *manufacturerID, uint16_t *productID);

private:
    Adafruit_I2CDevice *i2c_dev2 = NULL;
    boolean _framInitialized;
};