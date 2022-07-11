/**
 * @file Test_Avionics_Board_Bus_Switch_Mock.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test the I2C bus switch
 * @version 1.0.0
 * @date 2022-07-11
 *
 *
 */

#include <SilverSat_Bus_Switch_mock.h>

// Run the tests

bool test_Bus_Switch()
{

    BusSwitch bus_switch;

    Serial.println("-----");
    Serial.println("Starting Bus Switch Test");

    // Test the bus enable and disable functions

    for (auto index = 1; index < 21; index++)
    {
        bus_switch.enableBus();
        bus_switch.disableBus();
        bus_switch.enableBus();
    }

    // Dump the debug log

    auto count = bus_switch.getLogSize();
    Serial.print("\nThere are ");
    Serial.print(count);
    Serial.println(" entries in the log");
    for (auto index = count; index > 0; index--)
    {
        auto log_entry = bus_switch.getLogEntry();
        Serial.print("Entry: ");
        switch (log_entry.action)
        {
        case BusSwitch::Action::create:
            Serial.print("Created switch at ");
            break;
        case BusSwitch::Action::enable:
            Serial.print("Enabled switch at ");
            break;
        case BusSwitch::Action::disable:
            Serial.print("Disabled switch at ");
            break;
        }
        Serial.println(log_entry.time_stamp);
    }

    // End of test

    Serial.println("\nBus Switch test complete");
    return true;
}