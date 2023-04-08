/**
 * @file EPS_I.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat device driver for Endurosat EPS I
 * @version 1.0.0
 * @date 2022-10-23
 *
 * This file implements the class that interfaces with the Power Board
 *
 */

#include "EPS_I.h"
#include "log_utility.h"

/**
 * @brief Set up the hardware and initialize I2C
 *
 * @return true successful
 * @return false error
 *
 */

bool EPS_I::begin()
{
  if (m_i2c_dev.begin())
  {
    return _init();
  }
  return false;
}

/**
 * @brief Initialization code for EPS I
 *
 * @return true if successful
 * @return false error
 *
 */

bool EPS_I::_init(void)
{
  // todo: initialize EPS I here if required
  return true;
}

/**
 * @brief Get the battery voltage
 *
 * @return float voltage
 *
 */

float EPS_I::getBatteryVoltage(void)
{
  uint16_t value{read_value(EPS_I_Read_Command::GETBATTERYINFO_BATTERY_BATT_VOLT)};
  return static_cast<float>(value) * GETBATTERYINFO_BATTERY_BATT_VOLT_COEFFICIENT;
}

/**
 * @brief Get the battery current
 *
 * @return float amperage
 *
 */

float EPS_I::getBatteryCurrent(void)
{
  uint16_t value{read_value(EPS_I_Read_Command::GETBATTERYINFO_BATTERY_BATT_CURR)};
  return static_cast<float>(value) * GETBATTERYINFO_BATTERY_BATT_CURR_COEFFICIENT;
}

/**
 * @brief Get the temperature at sensor 1
 *
 * @return float temperature
 *
 */

float EPS_I::getTemperatureSensor1(void)
{
  uint16_t value{read_value(EPS_I_Read_Command::GETTEMPERATURESINFO_TEMPERATURES_BATTERY0)};
  if (value < 0x8000)
    return static_cast<float>(value) * GETTEMPERATURESINFO_TEMPERATURES_BATTERY_COEFFICIENT_POSITIVE;
  else
    return (((value >> 4) - 1) ^ 0xFFFF) * GETTEMPERATURESINFO_TEMPERATURES_BATTERY_COEFFICIENT_NEGATIVE;
}

/**
 * @brief Get the temperature at sensor 2
 *
 * @return float temperature
 *
 */

float EPS_I::getTemperatureSensor2(void)
{
  uint16_t value{read_value(EPS_I_Read_Command::GETTEMPERATURESINFO_TEMPERATURES_BATTERY1)};
  if (value < 0x8000)
    return static_cast<float>(value) * GETTEMPERATURESINFO_TEMPERATURES_BATTERY_COEFFICIENT_POSITIVE;
  else
    return (((value >> 4) - 1) ^ 0xFFFF) * GETTEMPERATURESINFO_TEMPERATURES_BATTERY_COEFFICIENT_NEGATIVE;
}

/**
 * @brief Get the temperature at sensor 3
 *
 * @return float temperature
 *
 */

float EPS_I::getTemperatureSensor3(void)
{
  uint16_t value{read_value(EPS_I_Read_Command::GETTEMPERATURESINFO_TEMPERATURES_BATTERY2)};
  if (value < 0x8000)
    return static_cast<float>(value) * GETTEMPERATURESINFO_TEMPERATURES_BATTERY_COEFFICIENT_POSITIVE;
  else
    return (((value >> 4) - 1) ^ 0xFFFF) * GETTEMPERATURESINFO_TEMPERATURES_BATTERY_COEFFICIENT_NEGATIVE;
}

/**
 * @brief Get the Z negative panel current
 *
 * @return float amperage
 *
 */

float EPS_I::getZNegativeCurrent(void)
{
  uint16_t value{read_value(EPS_I_Read_Command::GETSOLARPANELSINFO_SOLAR_Z_CURR_NEG)};
  return static_cast<float>(value) * GETSOLARPANELSINFO_SOLAR_Z_CURR_NEG_COEFFICIENT;
}

/**
 * @brief Get the 5 volt current
 *
 * @return float voltage
 *
 */

float EPS_I::get5VCurrent(void)
{
  uint16_t value{read_value(EPS_I_Read_Command::GETBUSESINFO_BUSES_BUS_5V_CURR)};
  return static_cast<float>(value) * GETBUSESINFO_BUSES_BUS_5V_CURR_COEFFICIENT;
}

/**
 * @brief Get the heater 1 state
 *
 * @return bool true ON
 * @return bool false OFF
 *
 */

bool EPS_I::getHeater1State(void)
{
  uint16_t value{read_value(EPS_I_Read_Command::GETCONFIGURATIONINFO_CONFIG_OUTPUTCONDITIONS1)};
  return 0x0001 && (value >> static_cast<uint8_t>(EPS_I_Output_Condition_1::Heater_1));
}

/**
 * @brief Get the heater 2 state
 *
 * @return bool true ON
 * @return bool false OFF
 *
 */

bool EPS_I::getHeater2State(void)
{
  uint16_t value{read_value(EPS_I_Read_Command::GETCONFIGURATIONINFO_CONFIG_OUTPUTCONDITIONS1)};
  return 0x0001 && (value >> static_cast<uint8_t>(EPS_I_Output_Condition_1::Heater_2));
}

/**
 * @brief Get the heater 3 state
 *
 * @return bool true ON
 * @return bool false OFF
 *
 */

bool EPS_I::getHeater3State(void)
{
  uint16_t value{read_value(EPS_I_Read_Command::GETCONFIGURATIONINFO_CONFIG_OUTPUTCONDITIONS1)};
  return 0x0001 && (value >> static_cast<uint8_t>(EPS_I_Output_Condition_1::Heater_3));
}

/**
 * @brief Read 16 bits of data from the EPS I
 *
 * @return raw 16 bits in correct endian format
 *
 */

uint16_t EPS_I::read_value(EPS_I_Read_Command command)
{
  uint8_t return_buffer[2];
  uint16_t value;
  uint8_t command_byte{static_cast<uint8_t>(command)};
  m_i2c_dev.write_then_read(&command_byte, 1, return_buffer, 2, false);
  value = return_buffer[1] | (return_buffer[0] << 8);
  Log.verboseln("EPS-I reading from register %X is %X", command, value);
  return value;
}

/**
 * @brief Write an 8-bit command and 8-bit state to the EPS I
 *
 * @param command command to execute
 * @param state state parameter for command
 *
 */

void EPS_I::write_command(const EPS_I_Write_Command command, const uint8_t state)
{
  uint8_t command_byte{static_cast<uint8_t>(command)};
  m_i2c_dev.write(&state, 1, true, &command_byte, 1);
}