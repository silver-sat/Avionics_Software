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
#include "AvionicsBoard.h"
#include "RadioBoard.h"

/**
 * @brief Antenna constants
 *
 */
// todo: extend to 80 seconds for full lifecycle test
constexpr unsigned long antenna_delay{5 * seconds_to_milliseconds};

bool Antenna::deploy()
{
    // Execute algorithm 1 for all 4 antenna rods

    Log.verboseln("Executing algorithm 1 and starting antenna delay");
    constexpr uint8_t algorithm1_all{0x1F};
    m_i2c_dev.write(&algorithm1_all, 1);
    unsigned long antenna_timer_start{millis()};
    extern AvionicsBoard avionics;
    while ((millis() - antenna_timer_start) < antenna_delay)
    {
        avionics.trigger_watchdog();
    }
    Log.noticeln("Ending antenna delay");

    // Validate successful deployment

    Log.noticeln("Reading antenna state");
    byte antenna_state[4]{};
    m_i2c_dev.read(antenna_state, 4);
    if (antenna_state[3] == 0xFF)
    {
        Log.noticeln("Antenna doors open");
        return true;
    }

    // Execute algorithm 2 for all doors

    Log.warningln("Antenna door(s) not open, executing algorithm 2 and starting delay");
    constexpr u_int8_t algorithm2_all{0x2F};
    m_i2c_dev.write(&algorithm2_all, 1);
    antenna_timer_start = millis();
    while ((millis() - antenna_timer_start) < antenna_delay)
    {
        avionics.trigger_watchdog();
    }
    Log.noticeln("Ending antenna delay");

    // Validate successful deployment

    Log.noticeln("Reading antenna state");
    m_i2c_dev.read(antenna_state, 4);
    if (antenna_state[3] == 0xFF)
    {
        Log.noticeln("Antenna doors open");
        return true;
    }

    // Notifying Radio Board to deploy antenna via DigitalIO

    Log.errorln("Antenna door(s) not open; issuing Radio Board command to deploy via DigitalIO");
    extern RadioBoard radio;
    radio.deploy_antenna();
    antenna_timer_start = millis();
    while ((millis() - antenna_timer_start) < antenna_delay)
    {
        avionics.trigger_watchdog();
    }

    // Validate successful deployment

    Log.noticeln("Reading antenna state");
    m_i2c_dev.read(antenna_state, 4);
    if (antenna_state[3] == 0xFF)
    {
        Log.noticeln("Antenna doors open");
        return true;
    }
    else
    {
        Log.fatalln("Antenna door(s) not open, attempting to continue");
        return false;
    }
}