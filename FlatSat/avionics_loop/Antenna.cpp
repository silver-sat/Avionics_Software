/**
 * @file Antenna.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Device driver for SilverSat antenna
 * @version 1.0.0
 * @date 2023-04-01
 *
 *
 */

#include "Antenna.h"
#include "avionics_constants.h"
#include "log_utility.h"
#include "AvionicsBoard.h"
// #include "RadioBoard.h"

/**
 * @brief Antenna constants
 *
 */
// todo: extend to 80 seconds for full lifecycle test
constexpr unsigned long antenna_delay{5 * seconds_to_milliseconds};

/**
 * @brief Deploy the antenna
 *
 * @return true successful
 * @return false failure
 */

bool Antenna::deploy()
{
    // Execute algorithm 1 for all 4 antenna rods

    Log.traceln("Executing algorithm 1 and starting antenna delay");
    constexpr uint8_t algorithm1_all{0x1F};
    m_i2c_dev.write(&algorithm1_all, 1);
    unsigned long antenna_timer_start{millis()};
    extern AvionicsBoard avionics;
    while ((millis() - antenna_timer_start) < antenna_delay)
        avionics.trigger_watchdog();
    Log.traceln("Ending antenna delay");

    // Validate successful deployment

    Log.traceln("Reading antenna state");
    // todo: adjust for testing with antenna
    byte antenna_state[4]{0xFF, 0xFF, 0xFF, 0xFF};
    // m_i2c_dev.read(antenna_state, 4);
    for (size_t index{0}; index < 4; ++index)
        Log.verboseln("Antenna byte %d: %X", index, antenna_state[index]);
    if (antenna_state[3] == 0xFF)
    {
        Log.traceln("All antenna doors open");
        return true;
    }

    // Execute algorithm 2 for all doors

    Log.warningln("Antenna door(s) not open, executing algorithm 2 and starting delay");
    constexpr u_int8_t algorithm2_all{0x2F};
    m_i2c_dev.write(&algorithm2_all, 1);
    antenna_timer_start = millis();
    while ((millis() - antenna_timer_start) < antenna_delay)
        avionics.trigger_watchdog();
    Log.traceln("Ending antenna delay");

    // Validate successful deployment

    Log.traceln("Reading antenna state");
    m_i2c_dev.read(antenna_state, 4);
    for (size_t index{0}; index < 4; ++index)
        Log.verboseln("Antenna byte %d: %X", index, antenna_state[index]);
    if (antenna_state[3] == 0xFF)
    {
        Log.traceln("All antenna doors open");
        return true;
    }

    // Notify Radio Board to deploy antenna via DigitalIO mode A

    Log.errorln("Antenna door(s) not open; issuing Radio Board command to deploy via DigitalIO mode A");
    Message message{Message::antenna_release, "A"};
    antenna_timer_start = millis();
    while ((millis() - antenna_timer_start) < antenna_delay)
        avionics.trigger_watchdog();

    // Validate successful deployment

    Log.traceln("Reading antenna state");
    m_i2c_dev.read(antenna_state, 4);
    for (size_t index{0}; index < 4; ++index)
        Log.verboseln("Antenna byte %d: %X", index, antenna_state[index]);
    if (antenna_state[3] == 0xFF)
    {
        Log.traceln("All antenna doors open");
        return true;
    }

    // Notify Radio Board to deploy antenna via DigitalIO mode B

    Log.errorln("Antenna door(s) not open; issuing Radio Board command to deploy via DigitalIO mode B");
    message = Message{Message::antenna_release, "B"};
    antenna_timer_start = millis();
    while ((millis() - antenna_timer_start) < antenna_delay)
        avionics.trigger_watchdog();

    // Validate successful deployment

    Log.traceln("Reading antenna state");
    m_i2c_dev.read(antenna_state, 4);
    for (size_t index{0}; index < 4; ++index)
        Log.verboseln("Antenna byte %d: %X", index, antenna_state[index]);
    if (antenna_state[3] == 0xFF)
    {
        Log.traceln("All antenna doors open");
        return true;
    }

    // Unable to open all doors, attempt to continue

    Log.fatalln("Antenna door(s) not open, attempting to continue");
    return false;
}