/**
 * @file IMU.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilveSat Inertial Management Unit
 * @version 1.0.1
 * @date 2022-08-02
 *
 * This file implements the class that interfaces with the Intertial
 * Management Unit
 *
 */

#include "IMU.h"
#include "log_utility.h"
#include "avionics_constants.h"

// Stability margin

float stable_radians_sec_margin{0.01};

/**
 * @brief Initialize inertial management unit
 *
 * @return true successful
 * @return false error
 */

bool IMU::begin(TwoWire *theWire)
{
    unsigned long delayStartTime{millis()};
    // wait for IMU to become available
    while ((!m_mpu.begin(IMU_I2C_ADDRESS, theWire)) && ((millis() - delayStartTime) < wait_for_i2c_device))
        ;
    if (!m_mpu.begin(IMU_I2C_ADDRESS, theWire))
    {
        Log.errorln("Cannot initialize inertial management unit");
        return false;
    }

    m_mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    String prefix{"Accelerometer range set to: "};
    switch (m_mpu.getAccelerometerRange())
    {
    case MPU6050_RANGE_2_G:
        Log.verboseln((prefix + "+-2G").c_str());
        break;
    case MPU6050_RANGE_4_G:
        Log.verboseln((prefix + "+-4G").c_str());
        break;
    case MPU6050_RANGE_8_G:
        Log.verboseln((prefix + "+-8G").c_str());
        break;
    case MPU6050_RANGE_16_G:
        Log.verboseln((prefix + "+-16G").c_str());
        break;
    }

    m_mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    prefix = {"Gyro range set to: "};
    switch (m_mpu.getGyroRange())
    {
    case MPU6050_RANGE_250_DEG:
        Log.verboseln((prefix + "+-250 deg/s").c_str());
        break;
    case MPU6050_RANGE_500_DEG:
        Log.verboseln((prefix + "+-500 deg/s").c_str());
        break;
    case MPU6050_RANGE_1000_DEG:
        Log.verboseln((prefix + "+-1000 deg/s").c_str());
        break;
    case MPU6050_RANGE_2000_DEG:
        Log.verboseln("+- 2000 deg/s");
        break;
    }

    m_mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
    prefix = {"Filter bandwidth set to: "};
    switch (m_mpu.getFilterBandwidth())
    {
    case MPU6050_BAND_260_HZ:
        Log.verboseln((prefix + "260 Hz").c_str());
        break;
    case MPU6050_BAND_184_HZ:
        Log.verboseln((prefix + "184 Hz").c_str());
        break;
    case MPU6050_BAND_94_HZ:
        Log.verboseln((prefix + "94 Hz").c_str());
        break;
    case MPU6050_BAND_44_HZ:
        Log.verboseln((prefix + "44 Hz").c_str());
        break;
    case MPU6050_BAND_21_HZ:
        Log.verboseln((prefix + "21 Hz").c_str());
        break;
    case MPU6050_BAND_10_HZ:
        Log.verboseln((prefix + "10 Hz").c_str());
        break;
    case MPU6050_BAND_5_HZ:
        Log.verboseln((prefix + "5 Hz").c_str());
        break;
    }
// load smoothing array with initial data
sensors_event_t g;
g.gyro.x = x_calibration;
g.gyro.y = y_calibration;
g.gyro.z = z_calibration;
for (auto index{0}; index < buffer_size; ++index)
m_data_buffer.push(g);
    return true;
}

/**
 * @brief Get acceleration
 *
 * @return String acceleration in m/s^2
 */

String IMU::get_acceleration()
{
    refresh_data();
    Log.verboseln("Acceleration X: %F, Y: %F, Z: %F m/s^2",
                  m_a.acceleration.x, m_a.acceleration.y, m_a.acceleration.z);
    String data = String(" AX ") +
                  String(m_a.acceleration.x, 3) +
                  String(" AY ") +
                  String(m_a.acceleration.y, 3) +
                  String(" AZ ") +
                  String(m_a.acceleration.z, 3);

    return data;
}

/**
 * @brief Get rotation
 *
 * @return String rotation in rad/s
 */

String IMU::get_rotation()
{
    refresh_data();
    Log.verboseln("Rotation X: %F, Y: %F, Z: %F rad/s", m_g.gyro.x, m_g.gyro.y, m_g.gyro.z);
    String data = String(" RX ") +
                  String(m_g.gyro.x, 3) +
                  String(" RY ") +
                  String(m_g.gyro.y, 3) +
                  String(" RZ ") +
                  String(m_g.gyro.z, 3);

    return data;
}

/**
 * @brief Get temperature
 *
 * @return String temperature in degC
 */

String IMU::get_temperature()
{
    refresh_data();
    Log.verboseln("Temperature: %F degC", m_temp.temperature);
    String data = String(" T ") +
                  String(m_temp.temperature, 3);

    return data;
}

/**
 * @brief Update the data from the IMU
 *
 * @return true
 * @return false
 */

bool IMU::refresh_data()
{
    m_mpu.getEvent(&m_a, &m_g, &m_temp);
    return true;
}

/**
 * @brief Determine satellite stability
 *
 */

bool IMU::is_stable()
{
    sensors_event_t oldest{m_data_buffer.shift()};
    refresh_data();
    m_x_total = m_x_total - oldest.gyro.x;
    m_x_total = m_x_total + m_g.gyro.x;
    m_y_total = m_y_total - oldest.gyro.y;
    m_y_total = m_y_total + m_g.gyro.y;
    m_z_total = m_z_total - oldest.gyro.z;
    m_z_total = m_z_total + m_g.gyro.z;
    m_data_buffer.push(m_g);
    float x_average{m_x_total / static_cast<float>(buffer_size)};
    float y_average{m_y_total / static_cast<float>(buffer_size)};
    float z_average{m_z_total / static_cast<float>(buffer_size)};
    if ((abs(x_average - x_calibration) <= stable_radians_sec_margin) &&
        (abs(y_average - y_calibration) <= stable_radians_sec_margin) &&
        (abs(z_average - z_calibration) <= stable_radians_sec_margin))
        return true;
    else
        return false;
}