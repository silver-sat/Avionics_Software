/**
 * @file test_I2C_switch.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test I2C switch
 * @version 1.0.0
 * @date 2022-07-21
 *
 */

#ifndef TEST_I2C_SWITCH_H
#define TEST_I2C_SWITCH_H

#include <Arduino.h>

#define OE_OVERBAR_PIN 11u

/**
 * @brief The bus switch object
 *
 */
class BusSwitch
{
public:
    BusSwitch();

    /**
     * @brief Available actions
     *
     */

    /**
     * @brief Enable the bus
     *
     * @return true if successful
     * @return false otherwise
     */

    void enableBus();

    /**
     * @brief Disable the bus
     *
     * @return true if successful
     * @return false otherwise
     */

    void disableBus();

};

#endif