/**
 * @file IMU.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat Inertial Management Unit
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
    /**
     * @brief Construct a new IMU::IMU object
     *
     */

    IMU();
    
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

#endif // IMU_H