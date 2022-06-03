//
// FRAM Test Prototype
// Lee A. Congdon
// 21 May 2022
//
// Prototype to test the FRAM on the Avionics Board for SilverSat
// The Adafruit FRAM (Product ID: 1895) is not the FRAM specified for the satellite
// Caution: this test overwrites existing data in the FRAM
//

#include "Adafruit_FRAM_I2C.h"

// Byte patterns

const auto zeros_byte = 0x00;
const auto ones_byte = 0xFF;
const auto alternating_byte = 0xAA;
const auto test_byte = 0xAF;

// Specified FRAM size is 32K bytes

const long fram_size = 32 * long(1024);

// Power off delay in milliseconds

const auto power_delay = 5 * 1000;

// Create the FRAM object

auto fram = Adafruit_FRAM_I2C();


// Helper function to update the counter and print a dot if required

void progress(int &counter) {
  counter++;
  if (counter > 1000) {
    Serial.print(".");
    counter = 0;
  }
}


// Run the tests

void setup(void) {

// Setup the test

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

  auto progress_counter = 0;
  long address;
  for (address = 1; address < fram_size * 8; address++) {

    progress(progress_counter);
    
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
      Serial.println("\nFound maximum address");
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
  Serial.println("Writing and reading alternating ones and zeros ascending");
  progress_counter = 0;
 
  for (long address = 0; address < fram_size; address++) {
    
    progress(progress_counter);

// Write and read pattern
    
    fram.write(address, alternating_byte);
    if (fram.read(address) != alternating_byte) {
      Serial.print("\nI/O error at address 0x"); Serial.println(address, HEX);
      Serial.print("Error during alternating bits test");
      alternating_test_successful = false;
    }
  }
  Serial.println("\nAlternating bits test complete");

// Read/write zero bytes from the largest address down
  
  auto zeros_test_successful = true;  
  Serial.println("Writing and reading zeros descending");
  progress_counter = 0;
 
  for (long address = fram_size - 1; address >= 0; address--) {
    
    progress(progress_counter);

// Write and read pattern
    
    fram.write(address, zeros_byte);
    if (fram.read(address) != zeros_byte) {
      Serial.print("\nI/O error at address 0x"); Serial.println(address, HEX);
      Serial.print("Error during zero bits test");
      zeros_test_successful = false;
    }
  }
  Serial.println("\nZero bits test complete");


// Read/write one bytes randomly

  auto ones_test_successful = true;
  Serial.println("Writing and reading ones at random locations");
  progress_counter = 0;
 
  for (long count = 0; count < fram_size; count++) {
    
    progress(progress_counter);

// Write and read pattern

    address = random(0, fram_size);
    fram.write(address, ones_byte);
    if (fram.read(address) != ones_byte) {
      Serial.print("\nI/O error at address 0x"); Serial.println(address, HEX);
      Serial.print("Error during zero bits test");
      zeros_test_successful = false;
    }
  }
  Serial.println("\nOne bits test complete");

// Write test_bytes from address zero up, request power off, request power on, check memory 

  auto power_test_successful = true;
  Serial.println("Writing test bytes ascending");
  progress_counter = 0;
 
  for (long address = 0; address < fram_size; address++) {
    
    progress(progress_counter);

// Write pattern
    
    fram.write(address, test_byte);
    if (fram.read(address) != test_byte) {
      Serial.print("\nI/O error at address 0x"); Serial.println(address, HEX);
      Serial.print("Error during power test");
      power_test_successful = false;
    }
  }

// Ask for power off
  
  Serial.println("\nDisconnect power to the FRAM and press Enter");
  while (true) {
    if (Serial.read() == '\n') break;
  }
  Serial.print("Waiting "); Serial.print( power_delay / 1000 ); Serial.println(" seconds");
  delay(power_delay);
  
// Ask for power on and reinitialize FRAM
  
  Serial.println("Connect power to the FRAM and press Enter");
  while (true) {
    if (Serial.read() == '\n') break;
  }
  if (fram.begin(fram_i2c_address)) {  
    Serial.println("Reestablished FRAM I2C connection");
  } else {
    Serial.println("I2C FRAM not identified...check your connections and setup and retry");
    while (true);
  }
    
  Serial.println("Verifying test bytes ascending");
  progress_counter = 0;
 
  for (long address = 0; address < fram_size; address++) {
    
    progress(progress_counter);
  
// Read pattern
   
    if (fram.read(address) != test_byte) {
      Serial.print("\nI/O error at address 0x"); Serial.println(address, HEX);
      Serial.print("Error during power test");
      power_test_successful = false;
    }
  }
  Serial.println("\nPower test complete");

// Tests completed

  if (size_check_successful &&
      alternating_test_successful &&
      zeros_test_successful &&
      ones_test_successful &&
      power_test_successful
  ) {
    Serial.println("All tests succeeded");
  } else {
    Serial.println("Test(s) failed");
  }

  Serial.print("Completed FRAM Test Suite in "); Serial.print( (millis() - start_time) / 1000 ); Serial.println(" seconds");

}

void loop(void) {

}
