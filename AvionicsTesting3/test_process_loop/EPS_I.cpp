/**
 * @file EPS_I.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat driver for Endurosat EPS I
 * @version 1.0.0
 * @date 2022-10-23
 *
 *
 */

#include "EPS_I.h"

// #include <avr/pgmspace.h>
// #include <limits.h>
// #include "pins_arduino.h"
// #include "wiring_private.h"
/**
 * @brief Construct a new eps i::eps i object
 *
 */
EPS_I::EPS_I(void)
{
}

/**
 * @brief Set up the hardware and initialize I2C
 *
 * @param i2c_address address of the device
 * @param wire wire object for I2C connections
 * @return true successful
 * @return false error
 */
bool EPS_I::begin(uint8_t i2c_address, TwoWire *wire)
{
  if (!i2c_dev)
  {
    i2c_dev = new Adafruit_I2CDevice(i2c_address, wire);
  }

  if (i2c_dev->begin())
  {
    return false;
  }
  return _init();
}

/**
 * @brief Initialization code for EPS I
 *
 * @return true if successful
 * @return false error
 */
bool EPS_I::_init(void){
  // todo: initialize EPS I
  return true;
}

/**
 * @brief Read 16 bits of data from the EPS I
 * 
 * @return raw 16 bits in correct endian format
 */
uint16_t EPS_I::read_value(uint8_t command)
{
  uint8_t return_buffer[2];
  uint16_t value;

  i2c_dev->write_then_read(&command, 1, return_buffer, 2, true);
  value = return_buffer[1] | (return_buffer[0] << 8);

  return value;
}

/**
 * @brief Write an 8-bit command and 8-bit state to the EPS I
 * 
 * @param command command to execute
 * @param state state parameter for command
 */

void EPS_I::write_command(uint8_t command, uint8_t state)
{
  i2c_dev->write(&state, 1, true, &command, 1);
}