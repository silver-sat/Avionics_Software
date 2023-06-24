/**
 * @file eps_simulator_test.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Avionics Board code to test the EPS Simulator
 * @version 1.0.0
 * @date 2023-03-29
 *
 *
 */

#include <Adafruit_I2CDevice.h>

#define I2C_ADDRESS 0x18
Adafruit_I2CDevice i2c_dev = Adafruit_I2CDevice(I2C_ADDRESS, &Wire1);


void setup() {
  while (!Serial) { delay(10); }
  Serial.begin(57600);
  Serial.println("I2C device read and write test");

  if (!i2c_dev.begin()) {
    Serial.print("Did not find device at 0x");
    Serial.println(i2c_dev.address(), HEX);
    while (1);
  }
  Serial.print("Device found on address 0x");
  Serial.println(i2c_dev.address(), HEX);

  constexpr uint8_t command{0xAA};
  uint8_t buffer[]{0xBB, 0xBB};
  i2c_dev.write_then_read(&command, 1, buffer, 2, false);
  Serial.print("Write then Read: ");
  for (uint8_t i=0; i<2; ++i) {
    Serial.print("0x"); Serial.print(buffer[i], HEX); Serial.print(", ");
  }
  Serial.println();
}

void loop() {
  
}