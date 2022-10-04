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
    /**
     * @brief Construct a new IMU::IMU object
     *
     */

    IMU();
    
    /**
     * @brief Initialize inertial management unit
     *
     * @return true successful
     * @return false error
     */
    
    bool begin(TwoWire *theWire);
    
    /**
     * @brief Get acceleration
     *
     * @return String acceleration in m/s^2
     */
    
    String get_acceleration();
    
    /**
     * @brief Get rotation
     *
     * @return String rotation in rad/s
     */
    
    String get_rotation();
    
    /**
     * @brief Get temperature
     *
     * @return String temperature in degC
     */
    
    String get_temperature();

private:
    /**
     * @brief Update the data from the IMU
     *
     * @return true
     * @return false
     */
    
    bool refresh_data();
    
    Adafruit_MPU6050 m_mpu{};
    sensors_event_t m_a;
    sensors_event_t m_g;
    sensors_event_t m_temp;
};

#endif // IMU_H