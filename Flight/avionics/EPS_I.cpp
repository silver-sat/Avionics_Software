/**
 * @author Lee A. Congdon (lee@silversat.org)
 * @author Benjamin S. Cohen (ben@silversat.org)
 * @brief SilverSat device driver for Endurosat EPS I
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

bool EPS_I::_init()
{
  return true;
}

/**
 * @brief Get the battery voltage
 *
 * @return float voltage
 *
 */

float EPS_I::getBatteryVoltage()
{
  uint16_t value{read_value(EPS_I_Read_Command::GETBATTERYINFO_BATTERY_BATT_VOLT)};
  float voltage{static_cast<float>(value) * GETBATTERYINFO_BATTERY_BATT_VOLT_COEFFICIENT};
  Log.verboseln("Battery voltage is %F V", voltage);
  return voltage;
}

/**
 * @brief Get the battery current
 *
 * @return float amperage
 *
 */

float EPS_I::getBatteryCurrent()
{
  uint16_t value{read_value(EPS_I_Read_Command::GETBATTERYINFO_BATTERY_BATT_CURR)};
  float current{static_cast<float>(value) * GETBATTERYINFO_BATTERY_BATT_CURR_COEFFICIENT};
  Log.verboseln("Battery current is %F A", current);
  return current;
}

/**
 * @brief Get the temperature at sensor 1
 *
 * @return float temperature
 *
 */

float EPS_I::getTemperatureSensor1()
{
  uint16_t value{read_value(EPS_I_Read_Command::GETTEMPERATURESINFO_TEMPERATURES_BATTERY0)};
  float temperature{};
  if (value < 0x8000U)
    temperature = static_cast<float>(value) * GETTEMPERATURESINFO_TEMPERATURES_BATTERY_COEFFICIENT_POSITIVE;
  else
    temperature = static_cast<float>((((value >> 4) - 1) ^ 0xFFFF)) * GETTEMPERATURESINFO_TEMPERATURES_BATTERY_COEFFICIENT_NEGATIVE;
  Log.verboseln("Temperature sensor 1 is %F deg C", temperature);
  return temperature;
}

/**
 * @brief Get the temperature at sensor 2
 *
 * @return float temperature
 *
 */

float EPS_I::getTemperatureSensor2()
{
  uint16_t value{read_value(EPS_I_Read_Command::GETTEMPERATURESINFO_TEMPERATURES_BATTERY1)};
  float temperature{};
  if (value < 0x8000U)
    temperature = static_cast<float>(value) * GETTEMPERATURESINFO_TEMPERATURES_BATTERY_COEFFICIENT_POSITIVE;
  else
    temperature = static_cast<float>((((value >> 4) - 1) ^ 0xFFFF)) * GETTEMPERATURESINFO_TEMPERATURES_BATTERY_COEFFICIENT_NEGATIVE;
  Log.verboseln("Temperature sensor 2 is %F deg C", temperature);
  return temperature;
}

/**
 * @brief Get the temperature at sensor 3
 *
 * @return float temperature
 *
 */

float EPS_I::getTemperatureSensor3()
{
  uint16_t value{read_value(EPS_I_Read_Command::GETTEMPERATURESINFO_TEMPERATURES_BATTERY2)};
  float temperature{};
  if (value < 0x8000U)
    temperature = static_cast<float>(value) * GETTEMPERATURESINFO_TEMPERATURES_BATTERY_COEFFICIENT_POSITIVE;
  else
    temperature = static_cast<float>((((value >> 4) - 1) ^ 0xFFFF)) * GETTEMPERATURESINFO_TEMPERATURES_BATTERY_COEFFICIENT_NEGATIVE;
  Log.verboseln("Temperature sensor 3 is %F deg C", temperature);
  return temperature;
}

/**
 * @brief Get the Z negative panel current
 *
 * @return float amperage
 *
 */

float EPS_I::getZNegativeCurrent()
{
  uint16_t value{read_value(EPS_I_Read_Command::GETSOLARPANELSINFO_SOLAR_Z_CURR_NEG)};
  float current{static_cast<float>(value) * GETSOLARPANELSINFO_SOLAR_Z_CURR_NEG_COEFFICIENT};
  Log.verboseln("Z negative current is %F A", current);
  return current;
}

/**
 * @brief Get the 5 volt current
 *
 * @return float voltage
 *
 */

float EPS_I::get5VCurrent()
{
  uint16_t value{read_value(EPS_I_Read_Command::GETBUSESINFO_BUSES_BUS_5V_CURR)};
  float current{static_cast<float>(value) * GETBUSESINFO_BUSES_BUS_5V_CURR_COEFFICIENT * 1000.0f};
  Log.verboseln("5 volt current is %F mA", current);
  return current;
}

/**
 * @brief Get the LUP 5V voltage
 *
 * @return float voltage
 */

float EPS_I::getLUP_5VVoltage()
{
  uint16_t value{read_value(EPS_I_Read_Command::GETBUSESINFO_BUSES_LUP_5V_VOLT_VOLT)};
  float voltage{static_cast<float>(value) * GETBUSESINFO_BUSES_LUP_5V_VOLT_COEFFICIENT};
  Log.verboseln("LUP 5 volt voltage is %F V", voltage);
  return voltage;
}

/**
 * @brief Get the heater 1 state
 *
 * @return bool true ON
 * @return bool false OFF
 *
 */

bool EPS_I::getHeater1State()
{
  uint16_t value{read_value(EPS_I_Read_Command::GETCONFIGURATIONINFO_CONFIG_OUTPUTCONDITIONS1)};
  bool state{static_cast<bool>(0x0001 & (value >> static_cast<uint8_t>(EPS_I_Output_Condition_1::Heater_1)))};
  Log.verboseln("Heater 1 state is %T", state);
  return state;
}

/**
 * @brief Get the heater 2 state
 *
 * @return bool true ON
 * @return bool false OFF
 *
 */

bool EPS_I::getHeater2State()
{
  uint16_t value{read_value(EPS_I_Read_Command::GETCONFIGURATIONINFO_CONFIG_OUTPUTCONDITIONS1)};
  bool state{static_cast<bool>(0x0001 & (value >> static_cast<uint8_t>(EPS_I_Output_Condition_1::Heater_2)))};
  Log.verboseln("Heater 2 state is %T", state);
  return state;
}

/**
 * @brief Get the heater 3 state
 *
 * @return bool true ON
 * @return bool false OFF
 *
 */

bool EPS_I::getHeater3State()
{
  uint16_t value{read_value(EPS_I_Read_Command::GETCONFIGURATIONINFO_CONFIG_OUTPUTCONDITIONS1)};
  bool state{static_cast<bool>(0x0001 & (value >> static_cast<uint8_t>(EPS_I_Output_Condition_1::Heater_3)))};
  Log.verboseln("Heater 3 state is %T", state);
  return state;
}

/**
  * @brief method in EPS class that turns on the 5v LUP
 *
 *
 */

bool EPS_I::turn_on_5v_LUP()
{
  // Documentation error! OFF/ON and FORCED_OFF/FORCED_ON are each reversed

  auto state{static_cast<uint8_t>(EPS_I_Write_State::FORCED_OFF)};
  Log.verboseln("Sending command to EPS_I to turn on 5v LUP");
  return write_command(EPS_I_Write_Command::QUERYCONTROLS_AND_TOGGLEOUTPUT06, state);
}

/**
  * @brief method in EPS class that turns off the 3.3v LUP
 *
 *
 */

bool EPS_I::turn_off_3v3_LUP()
{
  // Documentation error! OFF/ON and FORCED_OFF/FORCED_ON are each reversed

  auto state{static_cast<uint8_t>(EPS_I_Write_State::FORCED_ON)};
  Log.verboseln("Sending command to EPS_I to turn off 3.3v LUP");
  return write_command(EPS_I_Write_Command::QUERYCONTROLS_AND_TOGGLEOUTPUT05, state);
}

/**
 * @brief method in EPS class that sends cycle for 5v
 *
 * default cycle time is two seconds
 *
 */

bool EPS_I::cycle_5v_bus()
{
  auto state{static_cast<uint8_t>(EPS_I_Write_State::TOGGLE)};
  Log.verboseln("Sending toggle command to EPS_I");
  return write_command(EPS_I_Write_Command::QUERYCONTROLS_AND_TOGGLEOUTPUT04, state);
}

/**
 * @brief Dump all data from EPS I
 *
 */

void EPS_I::dump_data()

{
  for (auto i{static_cast<int>(EPS_I_Read_Command::GETBATTERYINFO_BATTERY_BATT_VOLT)}; i <= static_cast<int>(EPS_I_Read_Command::GETSOFTWAREVERSION_BUILDTIME3); i++)
  {
    Log.verboseln("EPS-I Read Command %x: %X", i, read_value(static_cast<EPS_I_Read_Command>(i)));
  }
  for (auto i{static_cast<int>(EPS_I_Read_Command::QUERYWATCHDOG_NEW_TIMER)}; i <= static_cast<int>(EPS_I_Read_Command::QUERYLAUNCHSTATE_POWER_UP_DELAY); i++)
  {
    Log.verboseln("EPS-I Read Command %x: %X", i, read_value(static_cast<EPS_I_Read_Command>(i)));
  }
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
  value = static_cast<u_int16_t>(return_buffer[1] | (return_buffer[0] << 8));
  return value;
}

/**
 * @brief Write an 8-bit command and 8-bit state to the EPS I
 *
 * @param command command to execute
 * @param state state parameter for command
 *
 */

bool EPS_I::write_command(const EPS_I_Write_Command command, const uint8_t state)
{
  uint8_t command_byte{static_cast<uint8_t>(command)};
  return m_i2c_dev.write(&state, 1, true, &command_byte, 1);
}