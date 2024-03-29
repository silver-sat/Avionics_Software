/**
 * @file IMU.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Implement inertial management unit
 * @version 1.0.1
 * @date 2022-08-02
 *
 *
 */

#include "IMU.h"
#include "log_utility.h"
#include "board_configuration.h"

/**
 * @brief Construct a new IMU::IMU object
 *
 */

IMU::IMU(){

};

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
    {
    }
    if (!m_mpu.begin(IMU_I2C_ADDRESS, theWire))
    {
        Log.errorln("Cannot initialize inertial management unit");
        return false;
    };

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
    };

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
    };

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
    };

    return true;
};

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
    String data = String("AX") +
                  String(m_a.acceleration.x, 3) +
                  String("AY") +
                  String(m_a.acceleration.y, 3) +
                  String("AZ") +
                  String(m_a.acceleration.z, 3);

    return data;
};

/**
 * @brief Get rotation
 *
 * @return String rotation in rad/s
 */

String IMU::get_rotation()
{
    refresh_data();
    Log.verboseln("Rotation X: %F, Y: %F, Z: %F rad/s", m_g.gyro.x, m_g.gyro.y, m_g.gyro.z);
    String data = String("RX") +
                  String(m_g.gyro.x, 3) +
                  String("RY") +
                  String(m_g.gyro.y, 3) +
                  String("RZ") +
                  String(m_g.gyro.z, 3);

    return data;
};

/**
 * @brief Get temperature
 *
 * @return String temperature in degC
 */

String IMU::get_temperature()
{
    refresh_data();
    Log.verboseln("Temperature: %F degC", m_temp.temperature);
    String data = String("T") +
                  String(m_temp.temperature, 3);

    return data;
};

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