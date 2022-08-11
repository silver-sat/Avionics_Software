/**
 * @file IMU.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Implement inertial management unit
 * @version 1.0.0
 * @date 2022-08-02
 *
 *
 */

#ifndef IMU_U
#define IMU_U

#include <Adafruit_MPU6050.h>

#define IMU_I2C_ADDRESS 0x68

/**
 * @brief Inertial Management Unit
 *
 */

class IMU
{
public:
    IMU();
    bool begin(TwoWire *theWire);
    String get_acceleration();
    String get_rotation();
    String get_temperature();

private:
    bool refresh_data();
    sensors_event_t _a;
    sensors_event_t _g;
    sensors_event_t _temp;
    Adafruit_MPU6050 _mpu{};
};

#endif // IMU_H