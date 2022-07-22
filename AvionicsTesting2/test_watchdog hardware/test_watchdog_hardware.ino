/**
 * @file test_watchdog_hardware.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test the watchdog hardware
 * @version 1.0.0
 * @date 2022-07-22
 *
 *
 */

#include "test_watchdog_hardware.h"

// Run the tests

void setup(void)
{

  // Start the test

  Serial.begin(115200);
  while (!Serial)
    ;
  auto start_time = micros();
  Serial.println();
  Serial.println("Starting Watchdog Hardware Test");

  Watchdog watchdog{};

  // Normal trigger

  Serial.println("\nTesting normal trigger (should complete)");
  Serial.flush();
  watchdog.trigger();
  for (auto count = 0; count < 10; count++)
  {

    delay(WATCHDOG_LOWER_BOUNDARY / 1000 * 2);
    watchdog.trigger();
  }

  watchdog.dumpLog();
  Serial.println("Normal trigger test complete");
  Serial.flush();

  // Late trigger

  // Serial.println("\nTesting late trigger (should reset microcontroller)");
  // Serial.flush();
  // while (true)
  // {
  //   Serial.print("Timeout loop: ");
  //   Serial.println(micros());
  //   Serial.flush();
  //   delay(10);
  // }

  // Early trigger (comment out late trigger to test)

  Serial.println("\nTesting early trigger (should reset microcontroller)");
  Serial.flush();
  watchdog.trigger();
  watchdog.trigger();
  watchdog.trigger();
  Serial.println("End of early trigger test");
  Serial.flush();
}
void loop(void)
{
}
