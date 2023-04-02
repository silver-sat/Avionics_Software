/**
 * @file avionics_loop.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Avionics Board Setup and Process Loop
 * @version 1.3.0
 * @date 2022-07-24
 *
 */

/**
 * @mainpage Avionics Loop
 * @section overview Overview
 *
 * This is the setup and process loop for the SilverSat Avionics Board.
 *
 * The on-board devices are implemented as classes interfacing to real hardware and include an external watchdog timer, external realtime clock, inertial measurement
 * unit, and FRAM. The board also includes serial ports, I2C buses, and a SAMD21 processor. The SAMD21 internal watchdog timer is defined and activated as a backup
 * in the event hardware for the external timer is not available.
 *
 * The other boards: Power, Radio, and Payload, are represented as classes which provide interfaces to encapsulate their functions.
 *
 * The beacon message which Avionics sends to the Radio Board, the command messages the Radio
 * Board forwards to Avionics, and the response and local command messages sent to the Radio Board are also represented as classes.
 *
 */

#define INSTRUMENTATION // Instrumentation for processor and memory usage

#include "log_utility.h"
#include "Beacon.h"
#include "PowerBoard.h"
#include "AvionicsBoard.h"
#include "RadioBoard.h"
#include "PayloadBoard.h"
#include "Antenna.h"
#include "CommandProcessor.h"

/**
 * @brief Process loop constants
 *
 */
constexpr uint32_t serial_baud_rate{115200}; /**< speed of serial connection @hideinitializer */
// todo: adjust to 45 minutes for full test
constexpr unsigned long separation_delay{5 * seconds_to_milliseconds};

/**
 * @brief Create the boards, antenna, and command processor
 *
 */

AvionicsBoard avionics{};
PayloadBoard payload{};
RadioBoard radio{};
PowerBoard power{};
Antenna antenna{};
CommandProcessor command_processor{};

#ifdef INSTRUMENTATION
/**
 * @brief Test instrumentation values
 *
 */

unsigned long previous_time{};
unsigned long current_time{};
unsigned long duration{};
unsigned long loop_start_time{};
unsigned long loop_maximum{0};
unsigned long loop_maximum_timestamp{};
unsigned long watchdog_maximum{0};
unsigned long watchdog_maximum_timestamp{};
unsigned long beacon_maximum{0};
unsigned long beacon_maximum_timestamp{};
unsigned long command_maximum{0};
unsigned long command_maximum_timestamp{};
unsigned long photo_maximum{0};
unsigned long photo_maximum_timestamp{};
unsigned long payload_maximum{0};
unsigned long payload_maximum_timestamp{};
long RAM_minimum{32768};
unsigned long RAM_minimum_timestamp{};
unsigned long display_start_time{};
constexpr int display_interval{30 * 1000};

/**
 * @brief Helper function for memory use
 *
 */
extern "C" char *sbrk(int i);

int FreeRam () {
  char stack_dummy = 0;
  return &stack_dummy - sbrk(0);
}

#endif // INSTRUMENTATION

/**
 * @brief Initialize the devices and the boards
 *
 */

void setup()

{
  // Initialize serial connection and log utility

  Serial.begin(serial_baud_rate);
  while (!Serial)
  {
    avionics.trigger_watchdog(); // OK to trigger the internal watchdog before initialization
  };
  Log.setPrefix(printPrefix);
  Log.setSuffix(printSuffix);
  Log.begin(LOG_LEVEL_VERBOSE, &Serial);
  Log.setShowLevel(false);

  Log.noticeln("Initializing Avionics Process");

  // Initialize Avionics Board

  Log.noticeln("Initializing Avionics Board");
  avionics.begin();
  Log.noticeln("Avionics Board initialization completed");

  // Initialize Power Board

  Log.noticeln("Initializing Power Board interface");
  power.begin();
  Log.noticeln("Power Board interface initialization completed");

  // Initialize Radio Board

  Log.noticeln("Initializing Radio Board interface");
  radio.begin();
  Log.noticeln("Radio Board interface initialization completed");

  // Initialize Payload Board

  Log.noticeln("Initializing Payload Board interface");
  payload.begin();
  Log.noticeln("Payload Board interface initialization completed");

  // Wait for separation delay

  Log.noticeln("Beginning separation delay");
  unsigned long separation_timer_start{millis()};
  while ((millis() - separation_timer_start) < separation_delay)
  {
    avionics.trigger_watchdog();
  };
  Log.noticeln("Ending separation delay");

  // Deploy antenna

  Log.noticeln("Beginning antenna deployment");
  antenna.deploy();
  Log.noticeln("Antenna deployment completed");

  // Initialization complete

  Log.noticeln("Avionics Process initialization completed");

#ifdef INSTRUMENTATION
  // Set up instrumentation

  loop_start_time = micros();
  display_start_time = millis();
#endif // INSTRUMENTATION
};

/**
 * @brief Execute the Avionics functions
 *
 */

void loop()
{

#ifdef INSTRUMENTATION
  previous_time = micros();
#endif // INSTRUMENTATION

  // Trigger the watchdog

  avionics.trigger_watchdog();

#ifdef INSTRUMENTATION
  duration = micros() - previous_time;
  if (duration > watchdog_maximum)
  {
    watchdog_maximum = duration;
    watchdog_maximum_timestamp = millis();
  }
  previous_time = micros();
#endif // INSTRUMENTATION

  // Send beacon

  avionics.check_beacon();

#ifdef INSTRUMENTATION
  duration = micros() - previous_time;
  if (duration > beacon_maximum)
  {
    beacon_maximum = duration;
    beacon_maximum_timestamp = millis();
  }
  previous_time = micros();
#endif // INSTRUMENTATION

  // Process command

  command_processor.check_for_command();

#ifdef INSTRUMENTATION
  duration = micros() - previous_time;
  if (duration > command_maximum)
  {
    command_maximum = duration;
    command_maximum_timestamp = millis();
  }
  previous_time = micros();
#endif // INSTRUMENTATION

  // Check for photo time

  avionics.check_photo();

#ifdef INSTRUMENTATION
  duration = micros() - previous_time;
  if (duration > photo_maximum)
  {
    photo_maximum = duration;
    photo_maximum_timestamp = millis();
  }
  previous_time = micros();
#endif // INSTRUMENTATION

  // Shut off Payload Board if ready to sleep

  payload.check_shutdown();

#ifdef INSTRUMENTATION
  duration = micros() - previous_time;
  if (duration > payload_maximum)
  {
    payload_maximum = duration;
    payload_maximum_timestamp = millis();
  }
#endif // INSTRUMENTATION

#ifdef INSTRUMENTATION
  if (millis() - display_start_time > display_interval)
  {
    char timestamp[20]{};
    formatTimestamp(timestamp, loop_maximum_timestamp);
    Log.verboseln("Maximum loop time %l microseconds at %s", loop_maximum, timestamp);
    formatTimestamp(timestamp, watchdog_maximum_timestamp);
    Log.verboseln("Maximum watchdog processing duration %l microseconds at %s", watchdog_maximum, timestamp);
    formatTimestamp(timestamp, beacon_maximum_timestamp);
    Log.verboseln("Maximum beacon processing time %l microseconds at %s", beacon_maximum, timestamp);
    formatTimestamp(timestamp, command_maximum_timestamp);
    Log.verboseln("Maximum command processing time %l microseconds at %s", command_maximum, timestamp);
    formatTimestamp(timestamp, photo_maximum_timestamp);
    Log.verboseln("Maximum photo processing time %l microseconds at %s", photo_maximum, timestamp);
    formatTimestamp(timestamp, payload_maximum_timestamp);
    Log.verboseln("Maximum payload processing time %l microseconds at %s", payload_maximum, timestamp);
    formatTimestamp(timestamp, RAM_minimum_timestamp);
    Log.verboseln("Minimum free RAM %l bytes at %s", RAM_minimum, timestamp);
    display_start_time = millis();
    Log.verboseln("Current free RAM %l bytes", FreeRam());
  }

  // Record free RAM

  auto free_RAM{FreeRam()};
  if (free_RAM < RAM_minimum)
  {
    RAM_minimum = free_RAM;
    RAM_minimum_timestamp = millis();
  }

  // Record loop time

  duration = micros() - loop_start_time;
  if (duration > loop_maximum)
  {
    loop_maximum = duration;
    loop_maximum_timestamp = millis();
  }
  loop_start_time = micros();
#endif // INSTRUMENTATION
}