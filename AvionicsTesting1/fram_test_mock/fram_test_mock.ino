//
// Mock FRAM Test
// Lee A. Congdon
// 22 June 2022
//
// Test the mock FRAM on the Avionics Board for SilverSat
//

#include <Arduino.h>
#include "fram_mock.h"

// Byte patterns

const auto zeros_byte = 0x00;
const auto ones_byte = 0xFF;
const auto alternating_byte = 0xAA;
const auto test_byte = 0xAF;

// Specified FRAM size is 32K bytes

const long fram_size = 32 * long(1024);

// Create the FRAM object

auto fram = Fram();

// Run the tests

void setup(void) {

  Serial.begin(115200);
  while (!Serial);
  auto start_time = millis();
  Serial.println();
  Serial.println("Starting FRAM Test Suite");

// Verify FRAM is present at specified address
  
  auto fram_i2c_address = 0x50;
  if (fram.begin(fram_i2c_address)) {  
    Serial.print("Found FRAM at I2C address 0x"); Serial.println(fram_i2c_address, HEX);
  } else {
    Serial.println("I2C FRAM not identified...check your connections and setup and retry");
    while (true);
  }

// Get size

  auto size_check_successful = true;
  Serial.println("Checking size of FRAM");
  if (! fram.write(0, test_byte)) {
    Serial.print("\nFailed to write address 0x0000");
    size_check_successful = false;
  };

// Read increasing addresses looking for test byte

  long address;
  for (address = 1; address < fram_size * 8; address++) {

// If values don't match, memory address hasn't wrapped

    if (fram.read(address) != test_byte)
      continue;

// test_byte found, write the inverse to check

    if (! fram.write(address, (byte)~test_byte)) {
        Serial.print("\nFailed to write address 0x");
        Serial.println(address, HEX);
        size_check_successful = false;
        continue;
    }

// Check if address 0 was changed

    if (fram.read(0) == (byte)~test_byte) {
      Serial.println("Found maximum address");
      break;
    }
  }

  Serial.print("Memory size is "); Serial.print(address); Serial.println(" bytes");
  if (address == fram_size) {
    Serial.println("Size agrees with specified length");
  } else {
    Serial.println("Error, size does not equal specified length");
    size_check_successful = false;
  }
  Serial.println("Size check complete");

// Write/read alternating bits from byte zero up

  auto alternating_test_successful = true;
  Serial.println("\nWriting and reading alternating ones and zeros ascending");
 
  for (long address = 0; address < fram_size; address++) {
    
// Write and read pattern
    
    fram.write(address, alternating_byte);
    if (fram.read(address) != alternating_byte) {
      Serial.print("\nI/O error at address 0x"); Serial.println(address, HEX);
      Serial.print("Error during alternating bits test");
      alternating_test_successful = false;
    }
  }
  Serial.println("Alternating bits test complete");

// Read/write zero bytes from the largest address down
  
  auto zeros_test_successful = true;  
  Serial.println("\nWriting and reading zeros descending");
 
  for (long address = fram_size - 1; address >= 0; address--) {
    
// Write and read pattern
    
    fram.write(address, zeros_byte);
    if (fram.read(address) != zeros_byte) {
      Serial.print("\nI/O error at address 0x"); Serial.println(address, HEX);
      Serial.print("Error during zero bits test");
      zeros_test_successful = false;
    }
  }
  Serial.println("Zero bits test complete");

// Read/write one bytes randomly

  auto ones_test_successful = true;
  Serial.println("\nWriting and reading ones at random locations");
  for (long count = 0; count < fram_size; count++) {

// Write and read pattern

    address = random(0, fram_size);
    fram.write(address, ones_byte);
    if (fram.read(address) != ones_byte) {
      Serial.print("\nI/O error at address 0x"); Serial.println(address, HEX);
      Serial.print("Error during zero bits test");
      zeros_test_successful = false;
    }
  }
  Serial.println("One bits test complete");

// Tests completed

  if (size_check_successful &&
      alternating_test_successful &&
      zeros_test_successful &&
      ones_test_successful
  ) {
    Serial.println("\nAll tests succeeded");
  } else {
    Serial.println("\nTest(s) failed");
  }

  Serial.print("Completed FRAM Test Suite in "); Serial.print( (millis() - start_time) / 1000.0, 3 ); Serial.println(" seconds");

}

void loop(void) {

}
