/**
 * @file test_imu_non_crit_i2c.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test the Inertial Measurement Unit for SilverSat on the non-critical I2C bus
 * @version 1.0.0
 * @date 2022-08-07
 *
 * Based on Adafruit MPU6050 basic_readings.ino and Arduino
 */

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "wiring_private.h"

Adafruit_MPU6050 imu;
TwoWire non_crit_i2c(&sercom1, 11, 13);

void SERCOM1_Handler(void){
  non_crit_i2c.onService();
}

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  Wire.begin();
  non_crit_i2c.begin();
  pinPeripheral(11, PIO_SERCOM);
  pinPeripheral(13, PIO_SERCOM);

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!imu.begin(0x68, &non_crit_i2c))
  {
    Serial.println("IMU not found");
    while (true)
    {
    };
  };
  Serial.println("MPU6050 Found!");

  imu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (imu.getAccelerometerRange())
  {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  imu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (imu.getGyroRange())
  {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  imu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (imu.getFilterBandwidth())
  {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }
}
void loop()
{
  Serial.println("");
  delay(100);

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  imu.getEvent(&a, &g, &temp);

  /* Print out the values */
  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" degC");

  Serial.println("");
  delay(5000);
}
