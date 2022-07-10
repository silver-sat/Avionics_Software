/**
 * @file test_SilverSat_I2C_mock.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test mock I2C interface
 * @version 1.0.0
 * @date 2022-07-10
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

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println("Starting I2C Test");
  I2C i2c;
  i2c.begin(); // join i2c bus (address optional for master)
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

  Serial.print("I2C Test Complete");
}

void loop()
{
}
