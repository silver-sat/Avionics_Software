/**
 * @file test_Avionics_Board_mock.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Exercise the functions of the mock Avionics Board components
 * @version 1.0.0
 * @date 2022-07-11
 *
 *
 */

#include "Test_Avionics_Board_Mock.h"

void setup()
{
    // Run the tests

    Serial.begin(115200);
    while (!Serial)
    {
    }
    auto start_time = millis();
    auto tests_succeeded = true;
    Serial.println();
    Serial.println("Starting Avionics Board Test");

    // Test SAMD21

    tests_succeeded = tests_succeeded && test_SAMD21();

    // Test Watchdog

    tests_succeeded = tests_succeeded && test_Watchdog();

    // Test I2C Connectivity

    tests_succeeded = tests_succeeded && test_I2C();

    // Test Realtime Clock

    // Test I2C Switch

    tests_succeeded = tests_succeeded && test_Bus_Switch();

    // Test FRAM

    // Test IMU

    // End of tests

    Serial.println("-----");
    Serial.print("Completed Avionics Board Test Suite in ");
    Serial.print((millis() - start_time) / 1000.0, 3);
    Serial.println(" seconds");
    if (tests_succeeded)
    {
        Serial.print("All tests succeeded");
    }
    else
    {
        Serial.print("Test(s) failed");
    };
}

void loop(void)
{
}