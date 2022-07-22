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

  // Start the test

  Serial.begin(115200);
  while (!Serial)
    ;
  auto start_time = micros();
  Serial.println();
  Serial.println("Starting Watchdog Test");

  Watchdog watchdog{};

  // Normal trigger

  Serial.println("\nTesting normal trigger");
  watchdog.check_reset();
  watchdog.trigger();
  for (auto count = 0; count < 10; count++)
  {

    watchdog.check_reset();
    delay(WATCHDOG_LOWER_BOUNDARY / 1000 * 2);
    watchdog.check_reset();
    watchdog.trigger();
  }
  watchdog.check_reset();

  watchdog.dumpLog();
  Serial.println("Normal trigger test complete");

  // Late trigger

  Serial.println("\nTesting late trigger");

  delay(WATCHDOG_LOWER_BOUNDARY / 1000 * 2);
  watchdog.check_reset();
  watchdog.trigger();

  for (auto count = 0; count < 20; count++)
  {
    watchdog.check_reset();
    delay(500);
  }
  watchdog.check_reset();

  watchdog.dumpLog();
  Serial.println("Late trigger test complete");

  // Early trigger

  Serial.println("\nTesting early trigger");

  watchdog.trigger();
  watchdog.check_reset();
  delay(WATCHDOG_LOWER_BOUNDARY / 1000 / 2);
  watchdog.check_reset();

  watchdog.trigger();
  watchdog.check_reset();
  watchdog.trigger();
  watchdog.check_reset();

  watchdog.dumpLog();
  Serial.println("Late trigger test complete");

  Serial.print("\nCompleted Watchdog Test Suite in ");
  Serial.print((micros() - start_time) / 1000000.0, 3);
  Serial.println(" seconds");
}
void loop(void)
{
}
