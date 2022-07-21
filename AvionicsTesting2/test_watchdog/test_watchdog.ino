/**
 * @file test_watchdog.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test the watchdog
 * @version 1.0.0
 * @date 2022-07-22
 *
 *
 */

#include "test_watchdog.h"

// Run the tests

void setup(void)
{

  Serial.begin(115200);
  while (!Serial)
    ;
  auto start_time = millis();
  Serial.println();
  Serial.println("Starting Watchdog Test");

  Watchdog watchdog{};

  Serial.println("\nTesting normal trigger");
  for (auto count = 0; count < 10; count++)
  {

    // Early trigger

    // Serial.println("\nTesting early trigger");
    // watchdog.trigger();
    // delay(WATCHDOG_LOWER_BOUNDARY);
    // watchdog.trigger();
    // watchdog.trigger();
    // watchdog.dumpLog();
    // Serial.println("Early trigger test complete");

    // Normal operation

    // delay(WATCHDOG_LOWER_BOUNDARY);
    watchdog.trigger();
    watchdog.check_reset();
    // delay(WATCHDOG_LOWER_BOUNDARY + 1);
    // watchdog.trigger();
    // delay(WATCHDOG_LOWER_BOUNDARY);
    // watchdog.trigger();
    // delay(WATCHDOG_LOWER_BOUNDARY + 1);
    // watchdog.trigger();

    // Late trigger

    // Serial.println("\nTesting late trigger");
    // delay(WATCHDOG_UPPER_BOUNDARY + 1);
    // watchdog.trigger();
    // delay(WATCHDOG_UPPER_BOUNDARY);
    // watchdog.trigger();
    // delay(WATCHDOG_UPPER_BOUNDARY + 1);
    // watchdog.trigger();
    // delay(WATCHDOG_UPPER_BOUNDARY);
    // watchdog.trigger();
    // watchdog.dumpLog();
    // Serial.println("Late trigger test complete");
  }

  watchdog.dumpLog();
  Serial.println("Normal trigger test complete");
  Serial.print("\nCompleted Watchdog Test Suite in ");
  Serial.print((millis() - start_time) / 1000.0, 3);
  Serial.println(" seconds");
}
void loop(void)
{
}
