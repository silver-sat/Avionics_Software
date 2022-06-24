//
// Mock FRAM Example
// Lee A. Congdon
// 24 June 2022
//
// Test a mock FRAM
//

#include "fram_mock.h"

#include <iostream>
#include <chrono>
#include <random>

// Byte patterns

const auto zeros_byte = 0x00;
const auto ones_byte = 0xFF;
const auto alternating_byte = 0xAA;
const auto test_byte = 0xAF;

// Set up random number generation

std::mt19937 mt;
std::uniform_int_distribution<> location{0, 32767};

// Specified FRAM size is 32K bytes

const long fram_size = 32 * long(1024);

// Create the FRAM object

auto fram = Fram();

// Run the tests

int main(void) {

  auto start = std::chrono::steady_clock::now();
  std::cout << "Starting FRAM Test Suite\n";

// Verify FRAM is present at specified address
  
  auto fram_i2c_address = 0x50;
  if (fram.begin(fram_i2c_address)) {  
    std::cout << "Found FRAM at I2C address 0x" << std::hex << fram_i2c_address << '\n';
  } else {
    std::cout << "I2C FRAM not identified...check your connections and setup and retry\n";
    return 1;
  }

// Get size

  auto size_check_successful = true;
  std::cout << "Checking size of FRAM\n";
  if (! fram.write(0, test_byte)) {
    std::cout << "Failed to write address 0x0000\n";
    size_check_successful = false;
  };

// Read increasing addresses looking for test byte

  long address;
  for (address = 1; address < fram_size * 8; address++) {

// If values don't match, memory address hasn't wrapped

    if (fram.read(address) != test_byte)
      continue;

// test_byte found, write the inverse to check

    if (! fram.write(address, ~test_byte)) {
        std::cout << "\nFailed to write address 0x" << std::hex << address << '\n';
        size_check_successful = false;
        continue;
    }

// Check if address 0 was changed

    if (fram.read(0) == ~test_byte) {
      std::cout << "Found maximum address\n";
      break;
    }
  }

  std::cout << "Memory size is " << std::dec << address << " bytes\n";
  if (address == fram_size) {
    std::cout << "Size agrees with specified length\n";
  } else {
    std::cout <<  "Error, size does not equal specified length\n";
    size_check_successful = false;
  }
  std::cout << "Size check complete\n";

// Write/read alternating bits from byte zero up

  auto alternating_test_successful = true;
  std::cout << "Writing and reading alternating ones and zeros ascending\n";
 
  for (long address = 0; address < fram_size; address++) {
    
// Write and read pattern
    
    fram.write(address, alternating_byte);
    if (fram.read(address) != alternating_byte) {
      std::cout << "I/O error at address 0x" << std::hex << address << '\n';
      std::cout << "Error during alternating bits test\n";
      alternating_test_successful = false;
    }
  }
  std::cout << "Alternating bits test complete\n";

// Read/write zero bytes from the largest address down
  
  auto zeros_test_successful = true;  
  std::cout << "Writing and reading zeros descending\n";
 
  for (long address = fram_size - 1; address >= 0; address--) {
    
// Write and read pattern
    
    fram.write(address, zeros_byte);
    if (fram.read(address) != zeros_byte) {
      std::cout << "I/O error at address 0x" << std::hex << address << '\n';
      std::cout << "Error during zero bits test\n";
      zeros_test_successful = false;
    }
  }
  std::cout << "Zero bits test complete\n";

// Read/write one bytes randomly

  auto ones_test_successful = true;
  std::cout << "Writing and reading ones at random locations\n";
  for (long count = 0; count < fram_size; count++) {

// Write and read pattern

    address = location(mt);
    fram.write(address, ones_byte);
    if (fram.read(address) != ones_byte) {
      std::cout << "I/O error at address 0x\n" << std::hex << address << '\n';
      std::cout << "Error during zero bits test\n";
      zeros_test_successful = false;
    }
  }
  std::cout << "One bits test complete\n";

// Tests completed

  if (size_check_successful &&
      alternating_test_successful &&
      zeros_test_successful &&
      ones_test_successful
  ) {
    std::cout << "All tests succeeded\n";
  } else {
    std::cout << "Test(s) failed\n";
  }

  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start; 
  std::cout << "Completed FRAM Test Suite in " << std::dec << elapsed_seconds.count() << " seconds\n";

}