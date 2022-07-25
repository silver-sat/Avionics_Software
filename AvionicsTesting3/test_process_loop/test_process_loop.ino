/**
 * @file test_process_loop.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test the Avionics Board
 * @version 1.1.0
 * @date 2022-07-24
 *
 *
 */

#include "mock_power_board.h"
#include "mock_payload_board.h"
#include "mock_radio_board.h"

// constants

const unsigned long watchdog_lower_boundary{23500}; // 23.5 milliseconds
const unsigned long beacon_delay{5000000};          // 5 minutes

// timers and flags

unsigned long watchdog_reset_time{0};
// bool clock_set{false};
// int power_status_time{0};
// int imu_colletion_time{0};
// int power_adequate_time{0};
unsigned long last_beacon_time{0};

// global data

// sensors_event_t acceleration;
// sensors_event_t gyroscope;
// sensors_event_t temperature;

// Create management objects

// ExternalRTC rtc{};
// Watchdog watchdog{};
// IMU imu{};
// FRAM fram{};

// Initialize the boards and devices

MockPayloadBoard payload;
MockRadioBoard radio;
MockPowerBoard power;
// BusSwitch bus_switch;
// Create serial buffer as serial_buffer;
// Create the exernal RTC as external_rtc;
// Create the FRAM as fram;
// Create the imu as imu;
// Create the watchdog as watchdog;

void setup()
{

    Serial.begin(115200);
    while (!Serial)
        ;
    Serial.println("Testing SilverSat process loop");

    // Ensure payload board power is off

    payload.power_down();

    // Disable I2C non crit links

    // busswitch.disable();
    // pinMode(EN_EXT_I2C, OUTPUT);
    // digitalWrite(EN_EXT_I2C, LOW);

    // Disconnect from the serial port
    // serial_buffer.disable(payload);
    // serial_buffer.disable(radio);

    // Initialize connection to RTC

    // external_rtc.begin();

    // Initialize connection to IMU

    // imu.begin();

    // Initialize connection to FRAM

    // Start the watchdog timer

    // watchdog.trigger();
    // watchdog_reset_time = millis();
}

// Run the management functions

void loop()
{
    // trigger the watchdog if past lower boundary

    if (micros() - watchdog_reset_time > watchdog_lower_boundary)
    {
        // watchdog.trigger();
        watchdog_reset_time = micros();
    };

    // send beacon

    if (micros() > last_beacon_time + beacon_delay)
    {
        // todo: format beacon message
        MockRadioBoard::beacon message {"test beacon"};
        radio.send_beacon(message);
        last_beacon_time = micros();
    }

    // receive command

    if (radio.command_received())
    {

        // todo: implement command processing
        auto command = radio.get_command();
        Serial.print(micros()); Serial.print(" Command received: ");
        Serial.println(command);
    }

};