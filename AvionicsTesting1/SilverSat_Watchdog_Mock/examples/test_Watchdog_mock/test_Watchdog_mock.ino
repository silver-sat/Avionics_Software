//
// Mock Watchdog Test
// Lee A. Congdon
// 30 June 2022
//
// Test the mock Watchdog on the Avionics Board for SilverSat
//

#include <SilverSat_Watchdog_mock.h>

// Run the tests

void setup(void)
{

  Serial.begin(115200);
  while (!Serial)
    ;
  auto start_time = millis();
  Serial.println();
  Serial.println("Starting Watchdog Test");

  // Create the Watchdog object

  Watchdog watchdog{};

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

  Serial.print("\nCompleted Watchdog Test Suite in ");
  Serial.print((millis() - start_time) / 1000.0, 3);
  Serial.println(" seconds");
}

void loop(void)
{
}
