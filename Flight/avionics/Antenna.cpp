/**
 * @file Antenna.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Device driver for SilverSat antenna
 * @version 1.1.0
 * @date 2023-04-01
 *
 *
 */

#include "Antenna.h"
#include "avionics_constants.h"
#include "log_utility.h"
#include "AvionicsBoard.h"

/**
 * @brief Antenna constants
 *
 */
// todo: set to 80 seconds for flight
constexpr unsigned long antenna_delay{3 * seconds_to_milliseconds};

/**
 * @brief Check antenna state
 *
 * @return true all doors deployed
 * @return false some doors not deployee
 *
 */
bool Antenna::check()
{

    Log.traceln("Reading antenna state");
    byte antenna_state[4]{};
    m_i2c_dev.read(antenna_state, 4);
    for (size_t index{0}; index < 4; ++index)
        Log.verboseln("Antenna byte %d: %X", index, antenna_state[index]);
    if (antenna_state[3] == 0xFF)
    {
        Log.traceln("All antenna doors open");
        return true;
    }
    return false;
}

/**
 * @brief Deploy the antenna
 *
 * @return true successful
 * @return false failure
 */

bool Antenna::deploy()
{

    m_i2c_dev.begin();

    // Check initial state

    Log.traceln("Checking initial antenna state");
    check();

    // Execute algorithm 1 for all 4 antenna rods

    Log.traceln("Executing algorithm 1 and starting antenna delay");
    constexpr uint8_t algorithm1_all{0x1F};
    m_i2c_dev.write(&algorithm1_all, 1);
    unsigned long antenna_timer_start{millis()};
    extern AvionicsBoard avionics;
    while ((millis() - antenna_timer_start) < antenna_delay)
        avionics.trigger_watchdog();
    Log.traceln("Ending antenna delay");
    if (check())
        return true;

    // Execute algorithm 2 for all 4 antenna rods

    Log.warningln("Antenna door(s) not open, executing algorithm 2 and starting delay");
    constexpr u_int8_t algorithm2_all{0x2F};
    m_i2c_dev.write(&algorithm2_all, 1);
    antenna_timer_start = millis();
    while ((millis() - antenna_timer_start) < antenna_delay)
        avionics.trigger_watchdog();
    Log.traceln("Ending antenna delay");
    if (check())
        return true;

    // Notify Radio Board to deploy antenna via DigitalIO mode A

    Log.errorln("Antenna door(s) not open; issuing Radio Board command to deploy via DigitalIO mode A");
    Message message{Message::antenna_release, "A"};
    message.send();
    antenna_timer_start = millis();
    while ((millis() - antenna_timer_start) < antenna_delay)
        avionics.trigger_watchdog();
    if (check())
        return true;

    // Notify Radio Board to deploy antenna via DigitalIO mode B

    Log.errorln("Antenna door(s) not open; issuing Radio Board command to deploy via DigitalIO mode B");
    message = Message{Message::antenna_release, "B"};
    message.send();
    antenna_timer_start = millis();
    while ((millis() - antenna_timer_start) < antenna_delay)
        avionics.trigger_watchdog();
    if (check())
        return true;

    // Unable to open all doors, attempt to continue

    Log.fatalln("Antenna door(s) not open, attempting to continue");
    return false;
}