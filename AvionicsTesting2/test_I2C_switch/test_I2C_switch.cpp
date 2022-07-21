/**
 * @file test_I2C_switch.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test I2C switch
 * @version 1.0.0
 * @date 2022-07-21
 *
 */

#include "test_I2C_switch.h"

// Construct a new Bus Switch:: Bus Switch object

BusSwitch::BusSwitch()
{
      pinMode(OE_OVERBAR_PIN, OUTPUT);
};

// Disable the bus

void BusSwitch::disableBus()
{
    digitalWrite(OE_OVERBAR_PIN, HIGH);
};

// Enable the bus

void BusSwitch::enableBus()
{
    digitalWrite(OE_OVERBAR_PIN, LOW);
};