/**
 * @author Lee A. Congdon (lee@silversat.org)
 * @author Benjamin S. Cohen (ben@silversat.org)
 * @brief SilverSat Inertial Management Unit
 *
 * This file declares the class that interfaces with the Intertial
 * Management Unit
 *
 * RTC and IMU have the same I2C addresses but are located on different buses
 *
 */

#pragma once

#include <Adafruit_MPU6050.h>
#include <CircularBuffer.hpp>

constexpr unsigned IMU_I2C_ADDRESS{0x68}; /**< inertial measurement unit I2C address @hideinitializer */
constexpr size_t buffer_size{10};         /**< for data smoothing */

// MPU6050 gyro calibration, hardware specific

constexpr float x_calibration{-0.0655F};
constexpr float y_calibration{-0.016F};
constexpr float z_calibration{-0.0137F};

/**
 * @brief Inertial Management Unit
 *
 */

class IMU final
{
public:
    bool begin(TwoWire *theWire);
    String get_acceleration();
    String get_rotation();
    String get_temperature();
    bool is_stable();
private:
    bool refresh_data();
    Adafruit_MPU6050 m_mpu{};
    sensors_event_t m_a{};
    sensors_event_t m_g{};
    sensors_event_t m_temp{};
    CircularBuffer<sensors_event_t, buffer_size> m_data_buffer{};
    float m_x_total{x_calibration * static_cast<float>(buffer_size)}; // buffer initially filled with calibration constants
    float m_y_total{y_calibration * static_cast<float>(buffer_size)};
    float m_z_total{z_calibration * static_cast<float>(buffer_size)};
};