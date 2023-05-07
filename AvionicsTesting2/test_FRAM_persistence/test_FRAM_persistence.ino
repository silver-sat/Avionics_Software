/**
 * @file test_FRAM_persistence.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test the FRAM persistence
 * @version 1.0.0
 * @date 2023-05-06
 *
 *
 */

#include "CY15B256J.h"

// Size for FRAM

const size_t FRAM_size = 32 * 1024L;

// Create the FRAM object

CY15B256J fram;

// Execute the test

void setup(void)
{

  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println("Starting FRAM Persistence Test");

  // Verify FRAM is present at specified address

  int fram_i2c_address = 0x50;
  if (fram.begin(fram_i2c_address, &Wire1))
  {
    Serial.print("Found FRAM at I2C address 0x");
    Serial.println(fram_i2c_address, HEX);
  }
  else
  {
    Serial.println("I2C FRAM not identified...check your connections and setup and retry");
    while (true)
      ;
  }

  // Determine if FRAM already contains sequential entries

  bool sequential_entries{true};
  for (uint16_t address{0}; address < FRAM_size; ++address)
  {
    if (fram.read(address) != static_cast<uint8_t>(address)) // use lower 8 bits of address
    {
      sequential_entries = false;
      break;
    }
  }
  if (sequential_entries)
    Serial.println("FRAM has sequential entries");
  else
  {
    Serial.println("FRAM does not have sequential entries");
    Serial.println("Writing sequential entries");
    for (uint16_t address{0}; address < FRAM_size; ++address)
      fram.write(address, static_cast<uint8_t>(address));
    Serial.println("Sequential entries written, disconnect power and reconnect");
  }
  Serial.println("Test phase complete");
}

void loop(void)
{
}
