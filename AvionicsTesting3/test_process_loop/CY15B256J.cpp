/**
 * @file CY15B256J.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Driver for CY15B256 FRAM
 * @version 1.0.0
 * @date 2022-10-17
 * 
 * Based on Adafruit_FRAM_I2C
 */

#include "CY15B256J.h"
#include <math.h>
#include <stdlib.h>

/**
 * @brief Construct a new CY15B256J::CY15B256J object
 * 
 */
CY15B256J::CY15B256J(void) {_framInitialized = false;}

/**
 * @brief Sets up the hardware and initializes I2C
 * 
 * @param addr The I2C address to be used.
 * @param theWire The Wire object to be used for I2C connections.
 * @return true initialization successful
 * @return false otherwire
 */
bool CY15B256J::begin(uint8_t addr, TwoWire *theWire) {
  Adafruit_EEPROM_I2C::begin(addr, theWire);

  // the CY15B256J has a secondary address too!
  i2c_dev2 = new Adafruit_I2CDevice(CY15B256J_SECONDARY_ADDRESS, theWire);
  if (!i2c_dev2->begin()) {
    return false;
  }

  /* Make sure we're actually connected */
  uint16_t manufID, prodID;
  getDeviceID(&manufID, &prodID);
  if (manufID != 0x004) {
    Serial.print("Unexpected Manufacturer ID: 0x");
    Serial.println(manufID, HEX);
    return false;
  }
  if (prodID != 0x221) {
    Serial.print("Unexpected Product ID: 0x");
    Serial.println(prodID, HEX);
    return false;
  }

  /* Everything seems to be properly initialised and connected */
  _framInitialized = true;

  return true;
}

/**
 * @brief Reads the Manufacturer ID and the Product ID from the IC
 * 
 * @param[out] manufacturerID 
 *              The 12-bit manufacturer ID () (Cypress = 0x004)
 * @param productID 
 *              The memory density (bytes 11..8) and proprietary
 *              Product ID fields (bytes 7..0). Should be 0x221 for
 *              the CY15B256J.
 */
void CY15B256J::getDeviceID(uint16_t *manufacturerID,
                                    uint16_t *productID) {
  uint8_t buff[3] = {(uint8_t)(_addr * 2), 0, 0};

  i2c_dev2->write_then_read(buff, 1, buff, 3, false);
  /* Shift values to separate manuf and prod IDs */
  /* See p.11 of
   * https://www.infineon.com/dgdl/Infineon-CY15B256J_256_Kbit_%2832K_8%29_Automotive_Serial_%28I2C%29_F_RAM-DataSheet-v10_00-EN.pdf?fileId=8ac78c8c7d0d8da4017d0ecf69af49d8&utm_source=cypress&utm_medium=referral&utm_campaign=202110_globe_en_all_integration-datasheet
   */
  *manufacturerID = (buff[0] << 4) + (buff[1] >> 4);
  *productID = ((buff[1] & 0x0F) << 8) + buff[2];
}
