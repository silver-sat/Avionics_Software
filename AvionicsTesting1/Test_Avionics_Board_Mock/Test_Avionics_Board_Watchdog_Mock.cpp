/**
 * @file Test_Avionics_Board_Watchdog_Mock.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test the Watchdog Timer
 * @version 1.0.0
 * @date 2022-07-11
 *
 *
 */

#include <SilverSat_Watchdog_mock.h>

// Run the tests

bool test_Watchdog()
{

    Watchdog watchdog{};

    Serial.println("-----");
    Serial.println("Starting Watchdog test");

    // Early trigger

    Serial.println("\nTesting early trigger");
    watchdog.trigger();
    delay(WATCHDOG_LOWER_BOUNDARY);
    watchdog.trigger();
    watchdog.trigger();
    watchdog.dumpLog();
    Serial.println("Early trigger test complete");

    // Normal operation

    Serial.println("\nTesting normal trigger");
    delay(WATCHDOG_LOWER_BOUNDARY);
    watchdog.trigger();
    delay(WATCHDOG_LOWER_BOUNDARY + 1);
    watchdog.trigger();
    delay(WATCHDOG_LOWER_BOUNDARY);
    watchdog.trigger();
    delay(WATCHDOG_LOWER_BOUNDARY + 1);
    watchdog.trigger();
    watchdog.dumpLog();
    Serial.println("Normal trigger test complete");

    // Late trigger

    Serial.println("\nTesting late trigger");
    delay(WATCHDOG_UPPER_BOUNDARY + 1);
    watchdog.trigger();
    delay(WATCHDOG_UPPER_BOUNDARY);
    watchdog.trigger();
    delay(WATCHDOG_UPPER_BOUNDARY + 1);
    watchdog.trigger();
    delay(WATCHDOG_UPPER_BOUNDARY);
    watchdog.trigger();
    watchdog.dumpLog();
    Serial.println("Late trigger test complete");

    // Normal reset

    Serial.println("\nTesting normal reset");
    watchdog.reset();
    delay(WATCHDOG_LOWER_BOUNDARY);
    watchdog.reset();
    delay(WATCHDOG_UPPER_BOUNDARY);
    watchdog.reset();
    watchdog.reset();
    watchdog.dumpLog();
    Serial.println("Normal reset test complete");

    // Late reset

    Serial.println("\nTesting late reset");
    watchdog.reset();
    delay(WATCHDOG_UPPER_BOUNDARY + 1);
    watchdog.reset();
    delay(WATCHDOG_UPPER_BOUNDARY + 1);
    watchdog.reset();
    watchdog.dumpLog();
    Serial.println("Late reset test complete");

    // End of test

    Serial.println("\nWatchdog test complete");
    return true;

}
