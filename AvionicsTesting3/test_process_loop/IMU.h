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
    sensors_event_t m_a;
    sensors_event_t m_g;
    sensors_event_t m_temp;
    Adafruit_MPU6050 m_mpu{};
};

#endif // IMU_H