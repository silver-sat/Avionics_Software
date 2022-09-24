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

#include "log_utility.h"
#include "Beacon.h"
#include "Command.h"
#include "AvionicsBoard.h"
#include "mock_power_board.h"
#include "mock_payload_board.h"
#include "mock_radio_board.h"

constexpr unsigned long separation_delay{5 * SECONDS_TO_MILLISECONDS}; // todo: adjust to 45 minutes for full test
constexpr unsigned long separation_time{0};

/**
 * @brief Create the boards
 *
 */

AvionicsBoard avionics;
MockPayloadBoard payload;
MockRadioBoard radio;
MockPowerBoard power;

/**
 * @brief Test instrumentation values
 *
 */

unsigned long _loop_start{};
unsigned long _loop_maximum{0};
unsigned long _loop_maximum_timestamp{};
unsigned long _memory_minimum{32768};
unsigned long _memory_minimum_timestamp{};
unsigned long _display_start{};
constexpr int _display_interval{30 * 1000};

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

/**
 * @brief Initialize the devices and the boards
 *
 */

void setup()

{
    // Initialize serial connections and log utility for test reporting

    Serial.begin(SERIAL_MONITOR_BAUD_RATE);
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
    Serial1.begin(SERIAL_MONITOR_BAUD_RATE);
    while (!Serial1)
    {
        avionics.trigger_watchdog();
    }
    Log.traceln("Serial1 (command) port initialized");
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

    // Set up instrumentation

    _loop_start = millis();
    _display_start = millis();
};

/**
 * @brief Execute the Avionics functions
 *
 */

void loop()
{
    // Trigger the watchdog

    avionics.trigger_watchdog();

    // Record loop time

    unsigned long loop_time = millis();
    if (loop_time - _loop_start > _loop_maximum)
    {
        _loop_maximum = loop_time - _loop_start;
        _loop_maximum_timestamp = millis();
        _loop_start = loop_time;
    }

    // Record free memory

    long free_memory{freeMemory()};
    if (free_memory < _memory_minimum)
    {
        _memory_minimum = free_memory;
        _memory_minimum_timestamp = millis();
    }

    // Check instrumentation display

    if (millis() - _display_start > _display_interval)
    {
        char timestamp[20]{};
        formatTimestamp(timestamp, _loop_maximum_timestamp);
        Log.verboseln("Maximum loop time %l ms at %s", _loop_maximum, timestamp);
        formatTimestamp(timestamp, _memory_minimum_timestamp);
        Log.verboseln("Minimum free memory %l bytes at %s", _memory_minimum, timestamp);
        _display_start = millis();
        Log.verboseln("Current free memory %l bytes", freeMemory());
    }

    // Send beacon

    avionics.check_beacon();

    // Process command

    radio.check_for_command();

    // Take photo

    avionics.check_photo();

    // Shut off Payload Board if ready to sleep

    payload.check_shutdown();
};