/**
 * @file test_SAMD21.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SAMD21 self test
 * @version 1.0.0
 * @date 2022-07-21
 *
 *
 */

#ifndef TEST_SAMD21_H
#define TEST_SAMD21_H

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
   * @brief Access the I2C bus
   *
   * @return true if successful
   * @return false otherwise
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

  private:
  uint32_t _memory[MEMORY_SIZE] = {0};
};

#endif
