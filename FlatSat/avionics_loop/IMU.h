/**
 * @file IMU.h
 * @author Lee A. Congdon (lee@silversat.org)
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

constexpr unsigned IMU_I2C_ADDRESS{0x68};   /**< inertial measurement unit I2C address @hideinitializer */


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

private:
    /**
     * @brief Update the data from the IMU
     *
     */

    bool refresh_data();

    Adafruit_MPU6050 m_mpu{};
    sensors_event_t m_a;
    sensors_event_t m_g;
    sensors_event_t m_temp;
};