/**
 * @file test_process_loop.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test the Avionics Board
 * @version 1.2.0
 * @date 2022-07-24
 *
 */

/**
 * @mainpage Test Process Loop
 * @section overview Overview
 *
 * This is the main process loop to test the SilverSat Avionics Board.
 *
 * The on-board devices are implemented as classes interfacing to real hardware and include a watchdog timer, external realtime clock, inertial measurement
 * unit, and FRAM. The board also includes serial ports, I2C buses, and a SAMD21 processor.
 *
 * The other boards: Power, Radio, and Payload, are implemented as mock devices in software for these
 * tests. Each mock board performs a subset, as needed to test the Avionics Board, of the functionality provided by the actual board,.
 *
 * The beacon message which Avionics sends to the radio board, the command messages the Radio
 * Board forwards to Avionics, and the response and local command messages sent to the Radio Board are also represented as classes.
 *
 */

#undef INSTRUMENTATION // Instrumentation for processor and memory usage

#include "log_utility.h"
#include "Beacon.h"
#include "CollectCommand.h"
#include "ExecuteCommand.h"
#include "mock_power_board.h"
#include "AvionicsBoard.h"
#include "mock_radio_board.h"
#include "mock_payload_board.h"

/**
 * @brief Process loop constants
 *
 */

// todo: adjust to 45 minutes for full test
constexpr unsigned long separation_delay{5 * seconds_to_milliseconds};
constexpr unsigned long separation_time{0};

/**
 * @brief Serial interface constant
 *
 */
constexpr uint32_t serial_baud_rate{115200};  /**< speed of serial connection @hideinitializer */

/**
 * @brief Create the boards and command processor
 *
 */

AvionicsBoard avionics;
MockPayloadBoard payload;
MockRadioBoard radio;
MockPowerBoard power;
CollectCommand command_processor;

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
unsigned long memory_minimum{32768};
unsigned long memory_minimum_timestamp{};
unsigned long display_start_time{};
constexpr int display_interval{30 * 1000};

/**
 * @brief Helper function for memory use
 *
 */

#ifdef __arm__
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char *sbrk(int incr);
#else  // __ARM__
extern char *__brkval;
#endif // __arm__

int freeMemory()
{
    char top;
#ifdef __arm__
    return &top - reinterpret_cast<char *>(sbrk(0));
#elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
    return &top - __brkval;
#else  // __arm__
    return __brkval ? &top - __brkval : &top - __malloc_heap_start;
#endif // __arm__
}
#endif // INSTRUMENTATION

/**
 * @brief Initialize the devices and the boards
 *
 */

void setup()

{
    // Initialize serial connections and log utility for test reporting

    Serial.begin(serial_baud_rate);
    while (!Serial)
    {
        avionics.trigger_watchdog();
    };
    Log.setPrefix(printPrefix);
    Log.setSuffix(printSuffix);
    Log.begin(LOG_LEVEL_VERBOSE, &Serial);
    Log.setShowLevel(false);

    Log.noticeln("Initializing SilverSat Process Loop Test");

    // Initialize Avionics Board

    Log.noticeln("Initializing Avionics Board");
    avionics.begin();
    Log.noticeln("Avionics Board initialization completed");

    // Initialize mock Power Board

    Log.noticeln("Initializing mock Power Board");
    power.begin();
    Log.noticeln("Mock Power Board initialization completed");

    // Initialize mock Radio Board

    Log.noticeln("Initializing mock Radio Board");
    radio.begin();
    Log.noticeln("Mock Radio Board initialization completed");

    // Initialize mock Payload Board

    Log.noticeln("Initializing mock Payload Board");
    payload.begin();
    Log.noticeln("Mock Payload Board initialization completed");

    // Wait for separation delay

    Log.noticeln("Beginning separation delay");
    while (millis() - separation_time < separation_delay)
    {
        avionics.trigger_watchdog();
    };
    Log.noticeln("Ending separation delay");

    // Deploy antenna

    Log.noticeln("Notifying mock Radio Board to deploy antenna");
    radio.deploy_antenna();

    // Initialization complete

    Log.noticeln("Process Loop Test initialization completed");

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

    // Take photo

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
        formatTimestamp(timestamp, memory_minimum_timestamp);
        Log.verboseln("Minimum free memory %l bytes at %s", memory_minimum, timestamp);
        display_start_time = millis();
        Log.verboseln("Current free memory %l bytes", freeMemory());
    }

    // Record free memory

    long free_memory{freeMemory()};
    if (free_memory < memory_minimum)
    {
        memory_minimum = free_memory;
        memory_minimum_timestamp = millis();
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
};