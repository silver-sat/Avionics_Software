/**
 * @file SilverSat_SAMD21_mock.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Mock SAMD21 for self test and demonstration
 * @version 1.0.0
 * @date 2022-07-10
 *
 *
 */

#ifndef SILVERSAT_SAMD21_MOCK_H
#define SILVERSAT_SAMD21_MOCK_H

#define MEMORY_SIZE 8

#include <Arduino.h>

/**
 * @brief Mock SAMD21
 *
 */

class SAMD21
{
public:
  /**
   * @brief Construct a new SAMD21 object
   *
   */

  SAMD21();

  /**
   * @brief Reset the SAMD21
   *
   */

  void reset();

  /**
   * @brief Store a value
   *
   * @param addr memory address (0x0 to MEMORY_SIZE - 1)
   * @param value value to store
   */

  void store(uint32_t addr, uint32_t value);

  /**
   * @brief Load a value
   *
   * @param addr memory address (0x0 to MEMORY_SIZE - 1)
   * @return uint32_t value retrieved
   */

  uint32_t load(uint32_t addr);

  /**
   * @brief Add two integers
   *
   * @param addend1 first integer
   * @param addend2 second integer
   * @return uint64_t result
   */

  uint64_t add(uint32_t addend1, uint32_t addend2);

  /**
   * @brief Multiply two integers
   *
   * @param addend1 first integer
   * @param addend2 second integer
   * @return uint64_t result
   */

  uint64_t multiply(uint32_t multiplicand1, uint32_t multiplicand2);

  /**
   * @brief Read the real time counter
   *
   * @return uint32_t timer value
   */

  uint32_t read_timer();

  /**
   * @brief Access the USB
   *
   * @param string string to print during test
   * @return true if successful
   * @return false otherwise
   */

  bool access_usb(String string);

  /**
   * @brief Access the I2C bus
   *
   * @param string string to print during test
   * @return true if successful
   * @return false otherwise
   */

  bool access_i2c(String string);

  /**
   * @brief Access the serial port
   *
   * @param string string to print during test
   * @return true if successful
   * @return false otherwise
   */

  bool access_serial(String string);

  /**
   * @brief Read a digital pin
   *
   * @param pin the pin to read
   * @return HIGH if high
   * @return LOW if low
   */

  bool read_digital(uint8_t pin);

  /**
   * @brief Write a digital pin
   *
   * @param pin the pin to write
   * @return true if successful
   * @return false otherwise
   */

  void write_digital(uint8_t pin, uint8_t value);

  /**
   * @brief Read an analog pin
   *
   * @param pin the pin to read
   * @return int16_t result
   */

  int16_t read_analog(uint8_t pin);

  /**
   * @brief Write an analog pin
   *
   * @param pin the pin to write
   * @return true if successful
   * @return false otherwise
   */
  void write_analog(uint8_t pin, uint8_t value);

  /**
   * @brief Get the last reset time
   *
   * @return uint32_t
   */

  uint32_t get_last_reset_time();

private:
  uint32_t _last_reset_time = 0xFFFF;
  uint32_t _memory[MEMORY_SIZE] = {0};
};

#endif
