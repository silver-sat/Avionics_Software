// ---------------------------------------------------------------- /
// Arduino I2C Scanner
// Re-writed by Arbi Abdul Jabbaar
// Using Arduino IDE 1.8.7
// Using GY-87 module for the target
// Tested on 10 September 2019
// This sketch tests the standard 7-bit addresses
// Devices with higher bit address might not be seen properly.
// ---------------------------------------------------------------- /

#include <Wire.h> //include Wire.h library
#include "wiring_private.h"

u_int32_t counter{1};
constexpr unsigned EN_EXT_I2C{11u}; /**< enable non-critical I2C @hideinitializer */

// TwoWire myWire(&sercom2, 3, 4);

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
  };
  Serial.println("\nI2C Scanner");
  pinMode(EN_EXT_I2C, OUTPUT);
  digitalWrite(EN_EXT_I2C, LOW);

  Wire.begin();
  // myWire.begin();
  // pinPeripheral(3, PIO_SERCOM_ALT);
  // pinPeripheral(4, PIO_SERCOM_ALT);
  Wire1.begin();
}

void loop()
{
  Serial.print("Scanning ");
  Serial.println(counter++);
  byte error, address; // variable for error and I2C address
  auto nDevices{0};

  for (int bus = 0; bus < 2; bus++)
  {
    for (address = 1; address < 127; address++)
    {
      if (bus == 0)
      {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
      }
      else
      {
        // myWire.beginTransmission(address);
        Wire1.beginTransmission(address);
        error = Wire1.endTransmission();
      };
      if (error == 0)
      {
        Serial.print("I2C device found at address 0x");
        if (address < 16)
          Serial.print("0");
        Serial.print(address, HEX);
        if (bus == 0)
        {
          Serial.println(" on the critical bus!");
        }
        else
        {
          Serial.println(" on the non-critical bus!");
        };
        nDevices++;
      }
      else if (error == 4)
      {
        Serial.print("Unknown error at address 0x");
        if (address < 16)
          Serial.print("0");
        Serial.println(address, HEX);
      }
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(5000); // wait 5 seconds for the next I2C scan
}