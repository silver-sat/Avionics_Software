/**
 * @file Test_Avionics_Board_I2C_Mock.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test the I2C connection
 * @version 1.0.0
 * @date 2022-07-11
 *
 *
 */

// Based on:
// Wire Master Reader
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI slave device
// Refer to the "Wire Slave Sender" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

#include <SilverSat_I2C_mock.h>

// Run the tests

bool test_I2C()
{

  I2C i2c;

  Serial.println("-----");
  Serial.println("Starting I2C Test");

  // Test read

  i2c.begin(); // join i2c bus (address optional for master)
  Serial.println("\nReading I2C bus");
  for (auto tests = 10; tests > 0; tests--)
  {
    i2c.requestFrom(2, 6, true); // request 6 bytes from slave device #2

    for (auto quantity = i2c.available(); quantity > 0; quantity--) // slave may send less than requested
    {
      char c = i2c.read(); // receive a byte as character
      Serial.print(c);     // print the character
    }
    Serial.print("\n");
  }

  // End of test

  Serial.println("\nI2C Test Complete");
  return true;
}