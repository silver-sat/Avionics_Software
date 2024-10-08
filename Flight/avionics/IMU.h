/**
 * @file IMU.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @author Benjamin S. Cohen (ben@silversat.org)
 * @brief SilverSat Inertial Management Unit
 * @version 1.0.0
 * @date 2022-08-02
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

// MPU6050 gyro calibration

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

    /**
     * @brief Initialize inertial management unit
     *
     */

    bool begin(TwoWire *theWire);

    /**
     * @brief Get acceleration
     *
     */

    String get_acceleration();

    /**
     * @brief Get rotation
     *
     */

    String get_rotation();

    /**
     * @brief Get temperature
     *
     */

    String get_temperature();

    /**
     * @brief Determine satellite stability
     *
     */

    bool is_stable();

private:
    /**
     * @brief Update the data from the IMU
     *
     */

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