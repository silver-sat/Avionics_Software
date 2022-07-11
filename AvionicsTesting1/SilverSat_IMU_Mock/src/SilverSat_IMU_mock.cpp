/**
 * @file SilverSat_IMU_mock.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Mock IMU for demonstration and testing
 * @version 1.0.1
 * @date 2022-07-11
 *
 *
 */

#include <SilverSat_IMU_mock.h>

IMU::IMU()
{
}

bool IMU::begin(uint8_t i2c_addr, int wire,
                int32_t sensorID)
{
    return true;
}

mpu6050_accel_range_t IMU::getAccelerometerRange()
{
    return _accel_range;
};

void IMU::setAccelerometerRange(mpu6050_accel_range_t new_range)
{
    _accel_range = new_range;
};

mpu6050_gyro_range_t IMU::getGyroRange()
{
    return _gyro_range;
};

void IMU::setGyroRange(mpu6050_gyro_range_t new_range)
{
    _gyro_range = new_range;
};

void IMU::setFilterBandwidth(mpu6050_bandwidth_t bandwidth)
{
    _bandwidth = bandwidth;
};

mpu6050_bandwidth_t IMU::getFilterBandwidth()
{
    return _bandwidth;
};

bool IMU::getEvent(sensors_event_t *accel, sensors_event_t *gyro,
                   sensors_event_t *temp)
{
    accel->acceleration = {1.0, 2.0, 3.0};
    gyro->gyro = {4.0, 5.0, 6.0};
    temp->temperature = {23.0};
    return true;
};
