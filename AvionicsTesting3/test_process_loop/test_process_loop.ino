/**
 * @file test_process_loop.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test the Avionics Board
 * @version 1.2.0
 * @date 2022-07-24
 * @mainpage Test Process Loop
 * @section overview Overview
 *
 * This is the main process loop to test the SilverSat Avionics Board.
 *
 * The devices are implemented as classes interfacing to real hardware and include an external realtime clock, FRAM, inertial measurement
 * unit, watchdog timer, serial ports, I2C buses, and the SAMD21 processor.
 *
 * The other boards: Power, Radio, and Payload are implemented as mock devices in software for these
 * tests. Each mock board performs a subset of the functionality provided by the actual board, as needed
 * to test the Avionics Board.
 *
 * The beacon message which Avionics sends to the radio board and the command messages the Radio
 * Board sends to Avionics are also represented as classes.
 *
 */

#include "log_utility.h"
#include "beacon.h"
#include "Command.h"
#include "AvionicsBoard.h"
#include "mock_power_board.h"
#include "mock_payload_board.h"
#include "mock_radio_board.h"

/**
 * @brief constants
 *
 */

constexpr unsigned long separation_delay{5 * 1000 * 1000}; // todo: adjust to 45 minutes for full test
const unsigned long separation_time{0};

// int power_status_time{0};
// int imu_colletion_time{0};
// int power_adequate_time{0};

/**
 * @brief global data
 *
 */

// sensors_event_t acceleration;
// sensors_event_t gyroscope;
// sensors_event_t temperature;

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
    // Serial connection for test reporting

    Serial.begin(115200);
    while (!Serial && !Serial.available())
    {
        avionics.trigger_watchdog();
    };

    // Log utility for test reporting

    Log.setPrefix(printPrefix);
    Log.setSuffix(printSuffix);
    Log.begin(LOG_LEVEL_VERBOSE, &Serial);
    Log.setShowLevel(false);

    Log.noticeln("Initializing SilverSat Process Loop Test");

    // Initialize Avionics Board

    Log.noticeln("Initializing Avionics Board");
    avionics.begin();
    Log.noticeln("Avionics Board initialization completed");

    // Initialize Power Board

    // power.begin();

    // Initialize Radio Board

    Log.noticeln("Initializing mock Radio Board");
    radio.begin();
    Log.noticeln("Mock Radio Board initialization completed");

    // Initialize Payload Board

    Log.noticeln("Initializing mock Payload Board");
    payload.begin();
    Log.noticeln("Mock Payload Board initialization completed");

    // wait for separation delay

    Log.noticeln("Beginning separation delay");
    while (micros() - separation_time < separation_delay)
    {
        avionics.trigger_watchdog();
    };
    Log.noticeln("Ending separation delay");

    // deploy antenna

    Log.noticeln("Process Loop Test initialization completed");
};

/**
 * @brief Run the Avionics functions
 *
 */

void loop()
{
    // Trigger the watchdog

    avionics.trigger_watchdog();

    // Send beacon

    avionics.check_beacon();

    // Process command

    radio.check_command();

    // Take photo

    avionics.check_photo();

    // Shut off Payload Board if ready to sleep

    payload.check_shutdown();
};