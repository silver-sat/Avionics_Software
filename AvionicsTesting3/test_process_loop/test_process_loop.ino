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
};

/**
 * @brief Execute the Avionics functions
 *
 */

void loop()
{
    // Trigger the watchdog

    avionics.trigger_watchdog();

    // Send beacon

    avionics.check_beacon();

    // Process command

    radio.check_for_command();

    // Take photo

    avionics.check_photo();

    // Shut off Payload Board if ready to sleep

    payload.check_shutdown();
};