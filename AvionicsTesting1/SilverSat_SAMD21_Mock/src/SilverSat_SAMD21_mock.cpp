/**
 * @file SilverSat_SAMD21_mock.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Mock SAMD21 for self test and demonstration
 * @version 1.0.0
 * @date 2022-07-10
 *
 *
 */

#include <SilverSat_SAMD21_mock.h>
#include <Arduino.h>

// Create the SAMD21 object

SAMD21::SAMD21(){

};

// Reset the SAMD21

void SAMD21::reset()
{
  _last_reset_time = millis();
  return;
}

// Store a value

void SAMD21::store(uint32_t addr, uint32_t value)
{
  if (addr < MEMORY_SIZE)
  {
    _memory[addr] = value;
  }
};

// Load a value

uint32_t SAMD21::load(uint32_t addr)
{
  if (addr < MEMORY_SIZE)
  {
    return _memory[addr];
  }
  else
  {
    return 0x0;
  }
};

// Add two integers

uint64_t SAMD21::add(uint32_t addend1, uint32_t addend2)
{
  return addend1 + addend2;
};

// Multiply two integers

uint64_t SAMD21::multiply(uint32_t multiplicand1, uint32_t multiplicand2)
{
  return multiplicand1 * multiplicand2;
};

// Read the real time counter
// Returns micros() as a surrogate for the timer

uint32_t SAMD21::read_timer()
{
  return micros();
};

// Access the USB

bool SAMD21::access_usb(String string)
{
  Serial.println(string);
  return true;
};

// Access the I2C bus

bool SAMD21::access_i2c(String string)
{
  Serial.println(string);
  return true;
};

// Access the serial port

bool SAMD21::access_serial(String string)
{
  Serial.println(string);
  return true;
};

// Read a digital pin

bool SAMD21::read_digital(uint8_t pin)
{
  pinMode(pin, INPUT);
  return digitalRead(pin);
};

// Write a digital pin

void SAMD21::write_digital(uint8_t pin, uint8_t value)
{
  pinMode(pin, OUTPUT);
  digitalWrite(pin, value);
};

// Read an analog pin

int16_t SAMD21::read_analog(uint8_t pin)
{
  return analogRead(pin);
};

// Write an analog pin

void SAMD21::write_analog(uint8_t pin, uint8_t value)
{
  analogWrite(pin, value);
};

// Get the last reset time

uint32_t SAMD21::get_last_reset_time()
{
  return _last_reset_time;
};
