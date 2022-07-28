/**
 * @file test_process_loop.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test the Avionics Board
 * @version 1.2.0
 * @date 2022-07-24
 * @mainpage Test Process Loop
 * @section intro Overview
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

#include "beacon.h"
#include "Command.h"
#include "mock_power_board.h"
#include "mock_payload_board.h"
#include "mock_radio_board.h"
#include <RTClib.h>

/**
 * @brief constants
 *
 */

constexpr unsigned long separation_delay{5 * 1000 * 1000};  // todo: adjust to 45 minutes for full test
constexpr unsigned long watchdog_lower_boundary{23500};     // 23.5 milliseconds
constexpr unsigned long beacon_delay{2 * 60 * 1000 * 1000}; // 2 minutes

/**
 * @brief timers and flags
 *
 */

unsigned long separation_time{0};
unsigned long watchdog_reset_time{0};
unsigned long last_beacon_time{0};
bool clock_set{false};
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
 * @brief Create interface objects
 *
 */

RTC_PCF8523 external_rtc{}; // todo: replace with Avionics Board realtime clock
// Watchdog watchdog{};
// IMU imu{};
// FRAM fram{};
// BusSwitch bus_switch;
// Create serial buffer as serial_buffer;

MockPayloadBoard payload;
MockRadioBoard radio;
MockPowerBoard power;

/**
 * @brief Helper function for timestamp
 *
 */

void timestamp()
{
    Serial.print(external_rtc.now().hour(), DEC);
    Serial.print(':');
    Serial.print(external_rtc.now().minute(), DEC);
    Serial.print(':');
    Serial.print(external_rtc.now().second(), DEC);
    Serial.print(" UTC");
};

/**
 * @brief Initialize the devices and the boards
 *
 */

void setup()

{
    // Serial connection for test reporting

    Serial.begin(115200);
    while (!Serial)
    {
    };
    Serial.println("Testing SilverSat process loop");

    // Critical I2C
    // Disable I2C non crit links
    // busswitch.disable();
    // pinMode(EN_EXT_I2C, OUTPUT);
    // digitalWrite(EN_EXT_I2C, LOW);

    // Disconnect from the Payload serial port
    // serial_buffer.disable(payload);

    // Connect to the Radio Board serial port
    // serial_buffer.enable(radio);

    // Enable external realtime clock

    Serial.println("Initializing external realtime clock");
    if (!external_rtc.begin())
    {
        Serial.println("Waiting for external realtime clock");
        delay(10);
    }
    Serial.println("External realtime clock initialized");

    // Initialize connection to IMU
    // imu.begin();

    // Initialize connection to FRAM

    // Initialize Power Board

    // power.begin();

    // Initialize Radio Board

    radio.begin();

    // Initialize Payload Board and set power off

    // payload.begin();
    // payload.power_down();

    // wait for separation delay

    Serial.println("Entering separation delay");
    while (micros() - separation_time < separation_delay)
    {
    };
    Serial.println("Exiting separation delay");

    // deploy antenna

    // Start the watchdog timer
    // watchdog.trigger();
    // watchdog_reset_time = micros();

    Serial.println("Setup complete, starting process loop");
};

/**
 * @brief Run the Avionics functions
 *
 */

void loop()
{
    // trigger the watchdog if past lower boundary

    if (micros() - watchdog_reset_time > watchdog_lower_boundary)
    {
        // watchdog.trigger();
        watchdog_reset_time = micros();
    };

    // send beacon

    if (micros() - last_beacon_time > beacon_delay)
    {
        // todo: get power statusu
        // todo: get payload status
        // todo: format beacon message
        Beacon message{Beacon::excellent, Beacon::good, Beacon::fair, Beacon::poor, Beacon::critical};
        radio.send_beacon(message);
        last_beacon_time = micros();
    }

    // receive command

    if (radio.command_received())
    {
        timestamp();
        Serial.print(" Command received: ");
        auto command = radio.get_command();
        command->acknowledge_command();
        command->execute_command();
    }

    // take photo

    // Get RTC
    // if RTC >= next picture time
    // set GPIO to photo
    // enable payload

    // tweet

    // Get RTC
    // if RTC >= next tweet time
    // set GPIO to tweet
    // enable payload

    // payload requesting shutdown?

    // if GPIO shows shutdown
    // turn off payload
};