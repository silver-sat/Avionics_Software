/**
 * @file SilverSat_FRAM_mock.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Mock FRAM for demonstration and testing
 * @version 1.0.0
 * @date 2022-06-22
 *
 *
 */

// Based on Adafruit_FRAM_I2C

#ifndef SILVERSAT_FRAM_MOCK_H
#define SILVERSAT_FRAM_MOCK_H

#define FRAM_DEFAULT_ADDRESS (0x50)
#define FRAM_MEMORY_SIZE 16384 // 32K FRAM does not fit on Metro M0 Express

#include <Arduino.h>

/**
 * @brief Mock FRAM object
 *
 */
class FRAM
{
public:
  /**
   * @brief Construct a new FRAM object
   *
   */

  FRAM();

  /**
   * @brief Initialize the FRAM deviced
   *
   * @param i2caddr I2C address
   * @param theWire I2C wire object
   * @return true if successful
   * @return false otherwise
   */

  bool begin(uint8_t i2caddr = FRAM_DEFAULT_ADDRESS, void *theWire = NULL);

  /**
   * @brief Write a byte to the FRAM
   *
   * @param addr FRAM address to update
   * @param value New value
   * @return true if successful
   * @return false otherwise
   */

  bool write(uint16_t addr, uint8_t value);

  /**
   * @brief Read a byte from the FRAM
   *
   * @param addr FRAM address to read
   * @return uint8_t return value
   */

  uint8_t read(uint16_t addr);

  /**
   * @brief Write multiple bytes to the FRAM
   *
   * @param addr starting FRAM address
   * @param buffer pointer to source buffer
   * @param num number of bytes to write
   * @return true if successful
   * @return false otherwise
   */

  bool write(uint16_t addr, uint8_t *buffer, uint16_t num);

  /**
   * @brief Read multiple bytes from the FRAM
   *
   * @param addr starting FRAM address
   * @param buffer pointer to target buffer
   * @param num number of bytes to read
   * @return true if successful
   * @return false otherwise
   */

  bool read(uint16_t addr, uint8_t *buffer, uint16_t num);

  /**
   * @brief Write object to FRAM
   *
   * @tparam T type of object
   * @param addr starting FRAM address
   * @param value object to write
   * @return uint16_t number of bytes written
   */

  template <class T>
  uint16_t writeObject(uint16_t addr, const T &value)
  {
    const byte *p = (const byte *)(const void *)&value;
    uint16_t n;
    for (n = 0; n < sizeof(value); n++)
    {
      write(addr++, *p++);
    }
    return n;
  }

  /**
   * @brief Read object from FRAM
   *
   * @tparam T type of object
   * @param addr starting FRAM address
   * @param value object to read
   * @return uint16_t number of bytes to read
   */

  template <class T>
  uint16_t readObject(uint16_t addr, T &value)
  {
    byte *p = (byte *)(void *)&value;
    uint16_t n;
    for (n = 0; n < sizeof(value); n++)
    {
      *p++ = read(addr++);
    }
    return n;
  }

private:
  uint8_t _i2caddr = 0;
  const uint16_t _memory_size = FRAM_MEMORY_SIZE;
  uint8_t _memory[FRAM_MEMORY_SIZE];
};

#endif
