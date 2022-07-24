/**
 * @file Test_I2C_switch.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief test for I2C switch
 * @version 1.0.0
 * @date 2022-07-21
 *
 */

#include "test_I2C_switch.h"

/**
 * @brief Construct the bus switch object
 *
 */
BusSwitch bus_switch;

void setup(void)
{

    // Enable the serial port and start the test

    Serial.begin(115200);
    while (!Serial)
        ;
    auto start_time = millis();
    Serial.println();
    Serial.println("Starting I2C Switch Test");

    // Test the bus enable and disable functions

    for (auto index = 1; index < 6; index++)
    {
        Serial.println("enabling");
        bus_switch.enableBus();
        delay(5000);
        Serial.println("disabling");
        bus_switch.disableBus();
        delay(5000);
        Serial.println("enabling");
        bus_switch.enableBus();
        delay(5000);
    }

    Serial.print("Completed Bus Switch Test in ");
    Serial.print((millis() - start_time) / 1000.0, 3);
    Serial.println(" seconds");
}

void loop(void)
{
}
