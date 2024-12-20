/**
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Device Driver for CY15B256 FRAM
 *
 * Based on Adafruit_FRAM_I2C
 *
 * This file declares the class that interfaces with the Avionics Board FRAM
 *
 */

#pragma once

#include <Adafruit_EEPROM_I2C.h>

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
    CY15B256J();

    bool begin(uint8_t addr = CY15B256J_DEFAULT_ADDRESS, TwoWire *theWire = &Wire);
    void getDeviceID(uint16_t *manufacturerID, uint16_t *productID);

private:
    Adafruit_I2CDevice *i2c_dev2 = NULL;
    boolean _framInitialized;
};