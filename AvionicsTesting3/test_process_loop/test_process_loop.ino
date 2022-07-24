/**
 * @file test_process_loop.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test the Avionics Board
 * @version 1.1.0
 * @date 2022-07-24
 *
 *
 */




enum PayloadStatus
{
    off,
    powerup,
    tweet,
    picture,
    shutdown,
};

// constants

const int watchdog_lower_boundary {23500};    // 23.5 milliseconds

// timers and flags

int watchdog_reset_time{0};
bool clock_set{false};
int clock_request_time{0}; // ask immediately for time during first cycle
int power_status_time{0};
int imu_colletion_time{0};
int power_adequate_time{0};
int beacon_time{0};

// global data

PowerStatus power_status{unknown};
sensors_event_t acceleration;
sensors_event_t gyroscope;
sensors_event_t temperature;

// Create management objects

ExternalRTC rtc{};
Watchdog watchdog{};
IMU imu{};
FRAM fram{};

// Initialize the board

void setup()
{
    // Ensure payload board power is off

    pinMode(PLD_ON_A, OUTPUT);
    pinMode(PLD_ON_B, OUTPUT);
    pinMode(PLD_ON_C, OUTPUT);
    digitalWrite(PLD_ON_A, HIGH); // HIGH is off per Preliminary Design Package
    digitalWrite(PLD_ON_B, HIGH);
    digitalWrite(PLD_ON_C, HIGH);

    // Disable I2C non crit links

    pinMode(EN_EXT_I2C, OUTPUT);
    digitalWrite(EN_EXT_I2C, LOW);

    // Disconnect from the serial port

    // Initialize connection to RTC

    rtc.begin();

    // Initialize connection to IMU

    imu.begin();

    // Initialize connection to FRAM

    // Start the watchdog timer

    watchdog.trigger();
    watchdog_reset_time = millis();
}

// Run the management functions

void loop()
{
    // trigger the watchdog if past lower boundary

    if (millis() > (watchdog_reset_time + watchdog_lower_boundary))
    {
        watchdog.trigger();
        watchdog_reset_time = millis();
    };

    // if clock not set, request the time via beacon if past delay interval

    if (!clock_set && (millis() > (clock_request_time + clock_request_delay)))
    {
        // todo: provide interface to communications beacon function (in mock radio board interface)
        clock_request_time = millis();
    };

    // get power state from the power board

    if (millis() > (power_status_time + power_status_delay))
    {
        // todo: provide interface to power board for capturing power state
        power_status_time = millis();
    };

    // determine rotation from IMU

    if (millis() > (imu_colletion_time + imu_data_delay))
    {
        imu.getEvent(&acceleration, &gyroscope, &temperature);
    }

    // send beacon

    if (millis() > beacon_time + beacon_delay)
    {
        // todo: format beacon message for radio board
    }

    // receive command

    // if(command available from radio board) {}
    // todo: implement mock radio board

    // process command

    
};