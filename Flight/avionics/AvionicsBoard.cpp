/**
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Avionics Board for SilverSat
 *
 * This file implements the class which encapsulates the functions of the Avionics Board
 * hardware.
 */

#include "AvionicsBoard.h"
#include "log_utility.h"
#include "I2C_ClearBus.h"
#include "Beacon.h"
#include "Antenna.h"
#include "PowerBoard.h"
#include "RadioBoard.h"
#include "PayloadBoard.h"
#include "PayloadQueue.h"

/**
 * @brief Initialize the Avionics Board
 *
 * @return true successful
 * @return false error
 */

bool AvionicsBoard::begin()
{

  // Critical I2C

  Log.traceln("Initializing critical I2C bus");
  int critical_bus_status{I2C_ClearBus(SDA_CRIT, SCL_CRIT)};
  switch (critical_bus_status)
  {
  case bus_clear:
    Log.verboseln("Critical I2C bus is clear");
    break;
  case SCL_low:
    Log.verboseln("Critical I2C bus SCL line held low");
    break;
  case SCL_low_stretch:
    Log.verboseln("Critical I2C bus SCL line held low by clock stretch");
    break;
  case SDA_low:
    Log.verboseln("Critical I2C bus SDA line held low");
    break;
  default:
    Log.verboseln("Unknown error on critical I2C bus");
    break;
  }
  Wire.begin();
  Log.traceln("Critical I2C bus initialization completed");

  // External realtime clock
  Log.traceln("Initializing external realtime clock");

  if (m_external_rtc.begin(&Wire))
    Log.traceln("External realtime clock initialization completed");
  else
  {
    Log.errorln("External realtime clock not initialized");
    m_rtc_initialization_error = true;
  }

  // Non-Critical I2C

  Log.traceln("Initializing non-critical I2C bus");
  busswitch_enable();
  int non_critical_bus_status{I2C_ClearBus(SDA_NON_CRIT, SCL_NON_CRIT)};
  switch (non_critical_bus_status)
  {
  case bus_clear:
    Log.verboseln("Non-critical I2C bus is clear");
    break;
  case SCL_low:
    Log.verboseln("Non-critical I2C bus SCL line held low");
    break;
  case SCL_low_stretch:
    Log.verboseln("Non-critical I2C bus SCL line held low by clock stretch");
    break;
  case SDA_low:
    Log.verboseln("Non-critical I2C bus SDA line held low");
    break;
  default:
    Log.verboseln("Unknown error on non-critical I2C bus");
    break;
  }
  Wire1.begin();
  Log.traceln("Non-critical I2C bus initialization completed");

  // Inertial Management Unit

  Log.traceln("Initializing inertial measurement unit");
  auto status = m_imu.begin(&Wire1);
  if (status)
    Log.traceln("Inertial measurement unit initialization completed");
  else
  {
    Log.errorln("Inertial management unit not initialized");
    m_imu_initialization_error = true;
  }

  // FRAM

  Log.traceln("Initializing FRAM");
  status = m_fram.begin(FRAM_I2C_ADDRESS, &Wire1);
  if (status)
    Log.traceln("FRAM initialization completed");
  else
  {
    Log.errorln("FRAM not initialized");
    m_FRAM_initialization_error = true;
  }

  return true;
}

/**
 * @brief Force the watchdog to reset the processor
 *
 */

void AvionicsBoard::watchdog_force_reset()
{
  Log.fatalln("Forcing watchdog reset");
  m_external_watchdog.force_reset();
}

/**
 * @brief Set the external realtime clock
 *
 * @param time new time setting
 * @return true successful
 * @return false error
 *
 */

bool AvionicsBoard::set_external_rtc(const DateTime time)
{
  if ((time.year() < minimum_valid_year) || (time.year() > maximum_valid_year))
  {
    Log.errorln("Time must be between %d and %d, inclusive", minimum_valid_year, maximum_valid_year);
    return false;
  }
  return m_external_rtc.set_time(time);
}

/**
 * @brief Get a timestamp
 *
 * @return String timestamp
 */

String AvionicsBoard::get_timestamp()
{
  return m_external_rtc.get_timestamp();
}

/**
 * @brief Set beacon interval
 *
 * @param seconds
 * @return true successful
 * @return false error
 *
 */

bool AvionicsBoard::set_beacon_interval(const int seconds)
{
  if ((seconds != 0) && ((seconds < minimum_beacon_interval) || (seconds > maximum_beacon_interval)))
  {
    Log.errorln("Beacon interval must be zero or between %d and %d, inclusive",
                minimum_beacon_interval, maximum_beacon_interval);
    return false;
  }
  m_last_beacon_time = millis(); // set beacon start to present time
  m_beacon_interval = static_cast<unsigned long>(seconds) * seconds_to_milliseconds;
  return true;
}

/**
 * @brief Send a beacon if the beacon interval has elapsed
 *
 * @return true successful
 * @return false error
 *
 */

bool AvionicsBoard::check_beacon()
{
  extern RadioBoard radio;
  extern Antenna antenna;
  extern PowerBoard power;
  extern PayloadBoard payload;

  if ((millis() - m_last_beacon_time > m_beacon_interval) && (m_beacon_interval > 0) && radio.recent_ground_contact())
  {
    if (antenna.antenna_cycle_completed() && !payload.get_payload_active()) // only send beacon when Antenna deployment cycle completed and Payload is not active
    {
      Beacon beacon{power.get_status(), get_status(), payload.get_status()};
      beacon.send();
    }
    else
    {
      Log.verboseln("Beacon not sent, Antenna deployment cycle not completed or Payload active");
    }
    m_last_beacon_time = millis();
  }
  return true;
}

/**
 * @brief Get Avionics status for beacon
 *
 */

AvionicsBeacon AvionicsBoard::get_status()
{

  AvionicsBeacon status{AvionicsBeacon::everything_ok};
  // show most recent initialization error if any
  if (m_rtc_initialization_error)
  {
    status = AvionicsBeacon::rtc_initialization_error;
    Log.verboseln("Realtime clock initialization error occurred");
  }
  if (m_imu_initialization_error)
  {
    status = AvionicsBeacon::imu_initialization_error;
    Log.verboseln("Inertial Measurement Unit initialization error occurred");
  }
  if (m_FRAM_initialization_error)
  {
    status = AvionicsBeacon::FRAM_initialization_error;
    Log.verboseln("FRAM initialization error occurred");
  }
  extern Antenna antenna;
  if (!antenna.antenna_deployed())
  {
    status = AvionicsBeacon::antenna_deployment_error;
    Log.verboseln("Antenna not deployed");
  }
  // todo: how to clear initialization errors
  // show stability if unstable and no initialization errors
  if ((status == AvionicsBeacon::everything_ok) && (!get_stability()))
  {
    status = AvionicsBeacon::unstable;
    Log.verboseln("Satellite is not stable");
  }
  // when stable, show unknown time until realtime clock set
  if ((status == AvionicsBeacon::everything_ok) && (!m_external_rtc.is_set()))
  {
    status = AvionicsBeacon::unknown_time;
    Log.verboseln("Time is not set");
  }
  return status;
}

/**
 * @brief Set the time for the next payload photo
 *
 * @param time time for photo
 * @return true successful
 * @return false error
 *
 */

bool AvionicsBoard::set_picture_time(const DateTime time)
{
  if (!valid_time(time))
  {
    return false;
  }
  if (!m_payload_queue.push(PayloadQueue::Element(time, PayloadQueue::ActivityType::Photo)))
  {
    return false;
  }
  return true;
}

/**
 * @brief Set the time for the next payload photo
 *
 * @param time time for SSDV broadcast
 * @return true successful
 * @return false error
 *
 */

bool AvionicsBoard::set_SSDV_time(const DateTime time)
{
  if (!valid_time(time))
  {
    return false;
  }
  if (!m_payload_queue.push(PayloadQueue::Element(time, PayloadQueue::ActivityType::SSDV)))
  {
    return false;
  }
  return true;
}

bool AvionicsBoard::valid_time(const DateTime time)
{
  if (!m_external_rtc.is_set())
  {
    Log.errorln("External realtime clock is not set");
    return false;
  }
  if ((time.year() < minimum_valid_year) || (time.year() > maximum_valid_year))
  {
    Log.errorln("Payload activity time must be between %d and %d, inclusive", minimum_valid_year, maximum_valid_year);
    return false;
  }
  DateTime current_time{};
  if (!m_external_rtc.get_time(current_time))
  {
    Log.errorln("Error from external realtime clock");
    return false;
  }
  if (time < current_time)
  {
    Log.errorln("Payload activity time is before current time");
    return false;
  }
  if (m_payload_queue.size() + 1 > maximum_payload_queue_size)
  {
    Log.errorln("Too many payload activity times");
    return false;
  }
  return true;
}

/**
 * @brief Check time for photo or SSDV session and start payload if required
 *
 * @return true successful
 * @return false error
 *
 * Payload activity times rely on the realtime clock
 */

bool AvionicsBoard::check_payload()
{
  if (!m_external_rtc.is_set())
    return false;
  DateTime time{};
  if (!m_external_rtc.get_time(time))
  {
    Log.errorln("Error from external real time clock");
    clear_payload_queue();
    return false;
  }
  if ((time.year() < minimum_valid_year) || (time.year() > maximum_valid_year))
  {
    Log.errorln("Time outside valid range");
    clear_payload_queue();
    return false;
  }
  // todo: validate time zero entry
  if (m_payload_queue.size() > 0 && (time >= m_payload_queue.peek().time))
  {
    Log.traceln("Payload activity time reached %s", get_timestamp().c_str());
    extern PayloadBoard payload;
    if (payload.get_payload_active())
    {
      Log.errorln("Payload board active, activity ignored");
      m_payload_queue.pop();
      return false;
    }

    switch (m_payload_queue.pop().type)
    {
    case PayloadQueue::ActivityType::Photo:
    {
      Log.verboseln("Avionics starting photo session");
      payload.photo();
      break;
    }
    case PayloadQueue::ActivityType::SSDV:
    {
      Log.verboseln("Avionics starting SSDV session");
      payload.SSDV();
      break;
    }
    default:
    {
      Log.errorln("Avionics encountered nnknown payload activity type");
      return false;
    }
    }
  }
  return true;
}

/**
 * @brief Get the size of the payload queue
 *
 * @return size_t size of the queue
 */

size_t AvionicsBoard::get_payload_queue_size()
{
  return m_payload_queue.size();
}

/**
 * @brief Clear payload activity times
 *
 * @return true successful
 * @return false error
 */

bool AvionicsBoard::clear_payload_queue()
{
  m_payload_queue.clear();
  return true;
}

/**
 * @brief Get telemetry
 *
 * @return String telemetry
 */

String AvionicsBoard::get_telemetry()
{
  // todo: calibrate device and adjust results for flight
  return m_imu.get_acceleration() + m_imu.get_rotation() + m_imu.get_temperature();
}

/**
 * @brief Get the beacon interval
 *
 * @return String interval
 */

String AvionicsBoard::get_beacon_interval()
{
  return String(m_beacon_interval / seconds_to_milliseconds);
}

/**
 * @brief Trigger the watchdog
 *
 */

void AvionicsBoard::service_watchdog()
{
  m_external_watchdog.service();
}

/**
 * @brief Enable I2C bus switch
 *
 * @return true successful
 * @return false error
 */

bool AvionicsBoard::busswitch_enable()
{
  Log.verboseln("Enabling I2C bus switch");
  pinMode(EN_EXT_I2C, OUTPUT);
  digitalWrite(EN_EXT_I2C, LOW);
  return true;
}

/**
 * @brief Read byte from FRAM
 *
 * @param address address of data
 * @return String byte read
 */

String AvionicsBoard::read_fram(const size_t address)
{
  return String(m_fram.read(static_cast<uint16_t>(address)));
}

/**
 * @brief Unset the realtime clock
 *
 * @return true successful
 * @return false error
 */

bool AvionicsBoard::unset_clock()
{
  Log.verboseln("Unsetting the realtime clock");
  clear_payload_queue();
  return m_external_rtc.unset_clock();
}

/**
 * @brief Determine stability
 *
 * @return true stable
 * @return false unstable
 */

bool AvionicsBoard::get_stability()
{
  return m_imu.is_stable();
}

/**
 * @brief Report reatltime clock initialization status
 *
 * return true no error
 * return false error
 *
 */

bool AvionicsBoard::test_external_rtc()
{
  if (m_external_rtc.startup_error())
  {
    Log.errorln("External realtime clock initialization error");
    return false;
  }
  Log.noticeln("External realtime clock initialized");
  return true;
}

/**
 * @brief Test the inertial measurement unit
 *
 * @return true successful
 * @return false error
 */

bool AvionicsBoard::test_IMU()
{
  m_imu.get_acceleration();
  m_imu.get_rotation();
  m_imu.get_temperature();
  if (!m_imu.is_stable())
  {
    Log.errorln("IMU indicates instability");
    return false;
  }
  Log.noticeln("IMU indicates stability");
  return true;
}

/**
 * @brief Test the FRAM
 *
 * @return true
 * @return false
 */

bool AvionicsBoard::test_FRAM()
{
  auto analog_pin{A0};
  auto random_value{static_cast<u_int8_t>(analogRead(analog_pin))};
  m_fram.write(0, random_value);
  Log.verboseln("Wrote %X to FRAM address 0", random_value);
  auto read_value{m_fram.read(0)};
  Log.verboseln("Read %X from FRAM address 0", read_value);
  if (read_value != random_value)
  {
    Log.errorln("FRAM test failed %X != %X", read_value, random_value);
    return false;
  }
  Log.noticeln("FRAM test passed");
  return true;
}