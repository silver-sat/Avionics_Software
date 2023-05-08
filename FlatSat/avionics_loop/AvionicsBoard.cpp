/**
 * @file AvionicsBoard.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Avionics Board for SilverSat
 * @version 1.0.4
 * @date 2022-07-29
 *
 * This file implements the class which encapsulates the functions of the Avionics Board
 * hardware.
 */

#include "AvionicsBoard.h"
#include "log_utility.h"
#include "Beacon.h"
#include "PowerBoard.h"
#include "RadioBoard.h"
#include "PayloadBoard.h"
#include <Adafruit_SleepyDog.h>

constexpr int internal_watchdog_interval{2 * seconds_to_milliseconds}; /**< internal watchdog interval **/

/**
 * @brief Initialize the Avionics Board
 *
 * @return true successful
 * @return false error
 */

bool AvionicsBoard::begin()
{

  // Internal watchdog timer
  //
  // Only required for internal watchdog
  // todo: consider adding window if internal watchdog is required

  Log.traceln("Initializing internal watchdog timer");
  auto interval{Watchdog.enable(internal_watchdog_interval)};
  Log.verboseln("Watchdog interval: %dms", interval);
  Log.traceln("Internal watchdog timer initialized");

  // Critical I2C

  Log.traceln("Initializing critical I2C bus");
  Wire.begin();
  Log.traceln("Critical I2C bus initialization completed");

  // External realtime clock
  Log.traceln("Initializing external realtime clock");

  if (m_external_rtc.begin(&Wire))
    Log.traceln("External realtime clock initialization completed");
  else
  {
    Log.errorln("External realtime clock not initialized");
    m_avionics_status = Beacon::AvionicsStatus::rtc_initialization_error;
  }

  // Non-Critical I2C

  Log.traceln("Initializing non-critical I2C bus");
  busswitch_enable();
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
    m_avionics_status = Beacon::AvionicsStatus::initialization_error_imu;
  }

  // FRAM

  Log.traceln("Initializing FRAM");
  status = m_fram.begin(FRAM_I2C_ADDRESS, &Wire1);
  if (status)
    Log.traceln("FRAM initialization completed");
  else
  {
    Log.errorln("FRAM not initialized");
    m_avionics_status = Beacon::AvionicsStatus::initialization_error_FRAM;
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
  m_external_watchdog.set_force_reset();
  Watchdog.disable();
  Watchdog.enable(0);
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
  if ((time.year() <= minimum_valid_year) || (time.year() >= maximum_valid_year))
  {
    Log.errorln("Time must be between %d and %d, inclusive", minimum_valid_year, maximum_valid_year);
    return false;
  }
  auto status{m_external_rtc.set_time(time)};
  if (status)
    m_avionics_status = Beacon::AvionicsStatus::everything_ok;
  else
    m_avionics_status = Beacon::AvionicsStatus::unknown_time;
  return status;
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
  m_beacon_interval = seconds * seconds_to_milliseconds;
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
  // todo: insure stability assessment prior to beacon
  // todo: insure time is set assessment prior to beacon
  if ((millis() - m_last_beacon_time > m_beacon_interval) && (m_beacon_interval > 0))
  {
    extern PowerBoard power;
    extern PayloadBoard payload;
    if (!payload.get_payload_active()) // only send beacon when Payload is not active
    {
      Beacon beacon{power.get_status(), get_status(), payload.get_status()};
      beacon.send();
    }
    m_last_beacon_time = millis();
  }
  return true;
}

/**
 * @brief Get Avionics status for beacon
 *
 */

Beacon::AvionicsStatus AvionicsBoard::get_status()
{
  return m_avionics_status;
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
  if (!m_external_rtc.is_set())
  {
    Log.errorln("External realtime clock is not set");
    return false;
  }
  if ((time.year() < minimum_valid_year) || (time.year() > maximum_valid_year))
  {
    Log.errorln("Picture time must be between %d and %d, inclusive", minimum_valid_year, maximum_valid_year);
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
    Log.errorln("Picture time is before current time");
    return false;
  }
  if (m_picture_count + 1 > maximum_scheduled_pictures)
  {
    Log.errorln("Too many picture times");
    return false;
  }
  size_t index{m_picture_count++};
  for (; index > 0; --index)
  {
    if (time > m_picture_times[index - 1])
      break;
    else
      m_picture_times[index] = m_picture_times[index - 1];
  }
  m_picture_times[index] = time;
  return true;
}

/**
 * @brief Check time for photo and start payload if required
 *
 * @return true successful
 * @return false error
 *
 * Picture times rely on the realtime clock
 */

bool AvionicsBoard::check_photo()
{
  if (!m_external_rtc.is_set())
    return false;
  DateTime time{};
  if (!m_external_rtc.get_time(time))
  {
    Log.errorln("Error from external real time clock");
    clear_pic_times();
    return false;
  }
  if ((time.year() < minimum_valid_year) || (time.year() > maximum_valid_year))
  {
    Log.errorln("Time outside valid range");
    clear_pic_times();
    return false;
  }
  // todo: check for sufficient power
  if ((m_picture_count > 0) && (time >= m_picture_times[0]))
  {
    Log.traceln("Photo time reached %s", get_timestamp().c_str());
    for (size_t index = 0; index < m_picture_count; ++index)
      m_picture_times[index] = m_picture_times[index + 1];
    --m_picture_count;
    extern PayloadBoard payload;
    if (payload.get_payload_active())
    {
      Log.errorln("Payload board active, picture time ignored");
      return false;
    }
    else
      payload.photo();
  }
  return true;
}

/**
 * @brief Get picture times
 *
 * @return String count and timestamps
 */

String AvionicsBoard::get_pic_times()
{
  String response{m_picture_count};
  for (size_t index = 0; index < m_picture_count; ++index)
    response += (' ' + m_picture_times[index].timestamp());
  return response;
}

/**
 * @brief Clear picture times
 *
 * @return true successful
 * @return false error
 */

bool AvionicsBoard::clear_pic_times()
{
  m_picture_count = 0;
  return true;
}

/**
 * @brief Get telemetry
 *
 * @return String telemetry
 */

String AvionicsBoard::get_telemetry()
{
  // todo: calibrate device and adjust results
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
 * todo: remove either external or internal watchdog, including .h and .cpp files and includes as required
 */

void AvionicsBoard::trigger_watchdog()
{
  m_external_watchdog.trigger();
  Watchdog.reset();
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
  return String(m_fram.read(address));
}

/**
 * @brief Unset the realtime clock
 *
 * @return true successful
 * @return false error
 */

bool AvionicsBoard::unset_clock()
// todo: consider eliminating command
{
  Log.verboseln("Unsetting the realtime clock");
  clear_pic_times();
  m_avionics_status = Beacon::AvionicsStatus::unknown_time;
  return m_external_rtc.unset_clock();
}

/**
 * @brief Deploy antenna
 *
 */

bool AvionicsBoard::deploy_antenna()
{
  bool status{m_antenna.deploy()};
  if (!status)
    m_avionics_status = Beacon::AvionicsStatus::antenna_not_deployed;
  return status;
}

/**
 * @brief Determine stability
 *
 */

bool AvionicsBoard::determine_stability()
{
  if (!m_imu.is_stable())
  {
    m_avionics_status = Beacon::AvionicsStatus::unstable;
    return false;
  }
  else
  m_avionics_status = Beacon::AvionicsStatus::everything_ok;
    return true;
}
