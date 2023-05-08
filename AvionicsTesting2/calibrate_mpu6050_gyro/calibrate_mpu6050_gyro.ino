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
#include <CircularBuffer.h>
#include <Wire.h>
#include "wiring_private.h"

// MPU 6050 gyro calibration

float x_calibration{-0.0232F};
float y_calibration{-0.0086F};
float z_calibration{-0.0058F};

constexpr size_t buffer_size{10};
CircularBuffer<sensors_event_t, buffer_size> data_buffer{};
float x_total{0.0F};
float y_total{0.0F};
float z_total{0.0F};

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

  sensors_event_t g;
  g.gyro.x = 0.0F;
  g.gyro.y = 0.0F;
  g.gyro.z = 0.0F;
  for (auto index{0}; index < buffer_size; ++index)
  {
    data_buffer.push(g); // fill the buffer, totals initialized to zero
  }
}
void loop()
{
  Serial.println("");
  delay(100);

  /* Get new sensor events with the readings */
  sensors_event_t a, g, t, oldest;
  oldest = data_buffer.shift();
  imu.getEvent(&a, &g, &t);
  x_total = x_total - oldest.gyro.x; 
  x_total = x_total + g.gyro.x;      
  y_total = y_total - oldest.gyro.y; 
  y_total = y_total + g.gyro.y;      
  z_total = z_total - oldest.gyro.z; 
  z_total = z_total + g.gyro.z;      
  data_buffer.push(g);        // store newest data in the buffer
  float x_average{x_total / static_cast<float>(buffer_size)};
  float y_average{y_total / static_cast<float>(buffer_size)};
  float z_average{z_total / static_cast<float>(buffer_size)};
  Serial.print("Smoothed rotation X: ");
  Serial.print(x_average - x_calibration, 6);
  Serial.print(", Y: ");
  Serial.print(y_average - y_calibration, 6);
  Serial.print(", Z: ");
  Serial.print(z_average - z_calibration, 6);
  Serial.println(" rad/s");

  Serial.println("");
  delay(5000);
}
