/**
 * @author Lee A. Congdon (lee@silversat.org)
 * @author Benjamin S. Cohen (ben@silversat.org)
 * @brief Avionics Board Setup and Process Loop
 *
 */

/**
 * @mainpage Avionics Loop
 * @section overview Overview
 *
 * This is the setup and process loop for the SilverSat Avionics Board.
 *
 * The on-board devices are implemented as classes interfacing to real hardware and include an external watchdog timer, external realtime clock, inertial measurement
 * unit, and FRAM. The board also includes serial ports, I2C buses, and a SAMD21 processor. The SAMD21 internal watchdog timer is not used.
 *
 * The other boards: Power, Radio, and Payload, are represented as classes which provide interfaces to encapsulate their functions.
 *
 * The beacon message which Avionics sends to the Radio Board, the command messages the Radio Board forwards to Avionics,
 * and the response and local command messages sent to the Radio Board are also represented as classes.
 *
 */

#include "log_utility.h"
#include "Antenna.h"
#include "PowerBoard.h"
#include "AvionicsBoard.h"
#include "RadioBoard.h"
#include "PayloadBoard.h"
#include "CommandProcessor.h"

// Avionics loop constants

constexpr uint32_t serial_baud_rate{19200}; /**< speed of serial connection @hideinitializer */
constexpr unsigned long serial_delay{2 * seconds_to_milliseconds};

// Create the boards, antenna, and command processor

AvionicsBoard avionics{};
PowerBoard power{};
RadioBoard radio{};
PayloadBoard payload{};
Antenna antenna{};
CommandProcessor command_processor{};

/**
 * @brief Arduino setup function to initialize the boards and devices and test them
 *
 */

void setup()
{
  // Initialize logging and the boards

  Serial.begin(serial_baud_rate);
  unsigned long serial_delay_start{millis()};
  while ((millis() - serial_delay_start) < serial_delay)
  {
    avionics.service_watchdog(); // service the watchdog while waiting for the serial port
  }
  Log.setPrefix(printPrefix);
  Log.setSuffix(printSuffix);
  Log.begin(LOG_LEVEL_VERBOSE, &Serial);
  Log.setShowLevel(false);
  Log.noticeln("Avionics software compiled %s at %s local time", __DATE__, __TIME__);

  Log.warningln("Recommended change: calibration for flight MPU");
  Log.warningln("Required change: remove prompt for delay bypasses");
  Log.noticeln("Initializing Avionics Process");

  Log.noticeln("Initializing Avionics Board");
  if (avionics.begin()) {
    Log.noticeln("Avionics Board initialization completed");
  } else {
    Log.errorln("Avionics Board initialization failed");
  }

  Log.noticeln("Initializing Power Board interface");
  if (power.begin()) {
    Log.noticeln("Power Board interface initialization completed");
  } else {
    Log.errorln("Power Board interface initialization failed");
  }

  Log.noticeln("Initializing Radio Board interface");
  if (radio.begin()) {
    Log.noticeln("Radio Board interface initialization completed");
  } else {
    Log.errorln("Radio Board interface initialization failed");
  }

  Log.noticeln("Initializing Payload Board interface");
  if (payload.begin()) {
    Log.noticeln("Payload Board interface initialization completed");
  } else {
    Log.errorln("Payload Board interface initialization failed");
  }

  Log.noticeln("Initializing Antenna");
  if (antenna.begin()) {
    Log.noticeln("Antenna initialization completed");
  } else {
    Log.errorln("Antenna initialization failed");
  }

  Log.noticeln("Setup complete");
  Log.noticeln("Avionics process accepting commands");
  avionics.service_watchdog();

  // Testing: test the devices and the boards

  Log.noticeln("Testing satellite components");

  Log.noticeln("Verifying external realtime clock status");
  avionics.test_external_rtc();

  Log.noticeln("Testing IMU");
  avionics.test_IMU();

  Log.noticeln("Testing FRAM");
  avionics.test_FRAM();

  Log.noticeln("Testing EPS-I");
  power.test_EPS();

  Log.noticeln("Testing Radio");
  radio.test_radio();

  Log.noticeln("Testing Payload");
  payload.photo();

  Log.noticeln("Testing Antenna");
  antenna.test_antenna();

  Log.noticeln("Initial testing complete, Radio and Payload tests continue");
}

/**
 * @brief Arduino loop function to execute the Avionics functions
 *
 */

void loop()
{
  updateLogDay();
  avionics.service_watchdog();
  antenna.check_antenna();
  avionics.get_stability();
  avionics.check_beacon();
  command_processor.check_for_command();
  avionics.check_payload();
  payload.check_shutdown();
}
