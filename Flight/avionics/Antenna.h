/**
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Device driver for SilverSat antenna
 *
 *
 */
#pragma once

#include <Adafruit_I2CDevice.h>
#include "avionics_constants.h"

/**
 * @brief Antenna constants
 *
 */
constexpr unsigned ANTENNA_I2C_ADDRESS{0x33}; /**< antenna I2C address @hideinitializer */
// set to 45 minutes for flight
// constexpr unsigned long separation_delay{45 * minutes_to_seconds * seconds_to_milliseconds}; /**< Separation delay prior to antenna deployment */
constexpr unsigned long separation_delay{3 * seconds_to_milliseconds}; /**< Separation delay prior to antenna deployment */
// set to 80 seconds for flight
constexpr unsigned long antenna_delay{3 * seconds_to_milliseconds};
// constexpr unsigned long antenna_delay{10 * seconds_to_milliseconds};

/**
 * @brief Antenna status byte
 * 
 */

enum class AntennaStatus : byte
{
    closed = 0x00,
    open = 0xFF
};

/**
 * @brief Antenna states
 *
 * States correspond to actions taken to open the antenna
 *
 */

enum class AntennaState
{
    startup,
    in_delay,
    deploying_algorithm_1,
    deploying_algorithm_2,
    deploying_radio_A,
    deploying_radio_B,
    completed
};

class Antenna final
{
public:
    bool begin();
    void test_antenna();
    bool check_antenna();
    bool antenna_deployed() { return m_antenna_deployed; }
    bool antenna_cycle_completed() { return m_antenna_cycle_completed; }
private:
    AntennaStatus check_deployment_state();
    void deployment_completed();
    Adafruit_I2CDevice m_i2c_dev{Adafruit_I2CDevice(ANTENNA_I2C_ADDRESS, &Wire1)};
    AntennaState m_state{AntennaState::startup};
    unsigned long m_state_start_time{};
    bool m_antenna_deployed{false};
    bool m_antenna_cycle_completed{false};
};