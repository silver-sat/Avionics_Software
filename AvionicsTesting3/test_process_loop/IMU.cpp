/**
 * @file IMU.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Implement inertial management unit
 * @version 1.0.0
 * @date 2022-08-02
 *
 *
 */

#include "IMU.h"
#include "log_utility.h"

IMU::IMU(){

};

/**
 * @brief Initialize inertial management unit
 *
 * @return true successful
 * @return false error
 */
    // todo: manage busswitch for non-critical I2C

bool IMU::begin(TwoWire* theWire)
{
    if (!_mpu.begin(IMU_I2C_ADDRESS, theWire))
    {
        Log.errorln("Cannot initialize inertial management unit");
        return false;
    };

    _mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    String prefix {"Accelerometer range set to: "};
    switch (_mpu.getAccelerometerRange())
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

    _mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    prefix = {"Gyro range set to: "};
    switch (_mpu.getGyroRange())
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

    _mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
    prefix = {"Filter bandwidth set to: "};
    switch (_mpu.getFilterBandwidth())
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
                  _a.acceleration.x, _a.acceleration.y, _a.acceleration.z);
    String data = String("AX") +
                  String(_a.acceleration.x, 3) +
                  String("AY") +
                  String(_a.acceleration.y, 3) +
                  String("AZ") +
                  String(_a.acceleration.z, 3);

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
    Log.verboseln("Rotation X: %F, Y: %F, Z: %F rad/s", _g.gyro.x, _g.gyro.y, _g.gyro.z);
    String data = String("RX") +
                  String(_g.gyro.x, 3) +
                  String("RY") +
                  String(_g.gyro.y, 3) +
                  String("RZ") +
                  String(_g.gyro.z, 3);

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
    Log.verboseln("Temperature: %F degC", _temp.temperature);
    String data = String("T") +
                  String(_temp.temperature, 3);

    return data;
};

bool IMU::refresh_data()
{
    _mpu.getEvent(&_a, &_g, &_temp);
    return true;
}