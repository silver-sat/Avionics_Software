/**
 * @file calibrate_mpu6050_gyro.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Calibrate the SilverSat MPU6050 gyro
 * @version 1.0.0
 * @date 2023-05-07
 *
 * Based on Adafruit MPU6050 basic_readings.ino and Arduino
 */

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "wiring_private.h"

// MPU 6050 gyro calibration

float x_calibration{-0.02};
float y_calibration{-0.01};
float z_calibration{-0.01};

Adafruit_MPU6050 imu;

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 gyro calibration");

  // Try to initialize!
  if (!imu.begin(0x68, &Wire1))
  {
    Serial.println("IMU not found");
    while (true)
    {
    };
  };
  Serial.println("MPU6050 Found!");

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
  sensors_event_t a, g, t;
  imu.getEvent(&a, &g, &t);

  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x - x_calibration);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y - y_calibration);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z - z_calibration);
  Serial.println(" rad/s");

  Serial.println("");
  delay(5000);
}
