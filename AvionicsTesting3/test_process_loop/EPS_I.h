/**
 * @file EPS_I.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat driver for Endurosat EPS I
 * @version 1.0.0
 * @date 2022-10-23
 * 
 * Based on the Adafruit Sensor Library
 */

#ifndef EPS_I_H
#define EPS_I_H

#include <Adafruit_Sensor.h>
#include "Arduino.h"

typedef enum {
// ESPS Command
// I2C Command
// EPS parameter
// Controlled feature
// Conversion coefficient
// (Unit)*
// *Unit - Dimension after conversion

GETBATTERYINFO_BATTERY_BATT_VOLT = 0x01,
// Battery Voltage
// Batt. BUS voltage - 12 bit ADC Units (from 0 to 4095)
// *0.0023394775
// V

GETBATTERYINFO_BATTERY_BATT_CURR = 0x02,
// Battery Current
// Batt. BUS current - 12 bit ADC Units
// *0.0030517578
// A

GETBATTERYINFO_BATTERY_BCR_VOLT = 0x03,
// BCR Voltage
// Ext. Battery Pack - 12 bit ADC Units
// *0.0023394775
// V

GETBATTERYINFO_BATTERY_BCR_CURR = 0x04,
// BCR Current
// Ext. Battery Pack - 12 bit ADC Units
// *0.0015258789
// A

GETSOLARPANELSINFO_SOLAR_X_VOLT = 0x05,
// X Voltage
// Solar Panel X axis voltage - 12 bit ADC Units
// *0.0024414063
// V

GETSOLARPANELSINFO_SOLAR_X_CURR_NEG = 0x06,
// X- Current
// Solar Panel X- current - 12 bit ADC Units
// *0.0006103516
// A

GETSOLARPANELSINFO_SOLAR_X_CURR_POS = 0x07,
// X+ Current
// Solar Panel X+ current - 12 bit ADC Units
// *0.0006103516
// A

GETSOLARPANELSINFO_SOLAR_Y_VOLT = 0x08,
// Y Voltage
// Solar Panel Y axis voltage - 12 bit ADC Units
// *0.0024414063
// V

GETSOLARPANELSINFO_SOLAR_Y_CURR_NEG = 0x09,
// Y- Current
// Solar Panel Y- current - 12 bit ADC Units
// *0.0006103516
// A

GETSOLARPANELSINFO_SOLAR_Y_CURR_POS = 0x0A,
// Y+ Current
// Solar Panel Y+ current - 12 bit ADC Units
// *0.0006103516
// A

GETSOLARPANELSINFO_SOLAR_Z_VOLT = 0x0B,
// Z Voltage
// Solar Panel Z axis voltage - 12 bit ADC Units
// *0.0024414063
// V

GETSOLARPANELSINFO_SOLAR_Z_CURR_NEG = 0x0C,
// Z- Current
// Solar Panel Z- current - 12 bit ADC Units
// *0.0006103516
// A

GETSOLARPANELSINFO_SOLAR_Z_CURR_POS = 0x0D,
// Z+ Current
// Solar Panel Z+ current - 12 bit ADC Units
// *0.0006103516
// A

GETBUSESINFO_BUSES_BUS_3V3_CURR = 0x0E,
// Current at 3.3 V bus
// 3.3V BUS current - 12 bit ADC Units.
// *0.0020345052
// A

GETBUSESINFO_BUSES_BUS_5V_CURR = 0x0F,
// Current at 5 V bus
// 5V BUS current - 12 bit ADC Units.
// *0.0020345052
// A

GETBUSESINFO_BUSES_LUP_3V3_VOLT_VOLT = 0x10,
// LUP 3.3 V
// 3.3V Latch-up - 12 bit ADC Units.
// *0.0023394775
// V

GETBUSESINFO_BUSES_LUP_5V_VOLT_VOLT = 0x11,
// LUP 5 V
// 5V Latch-up fault - 12 bit ADC Units.
// *0.0023394775
// V

GETTEMPERATURESINFO_TEMPERATURES_MCU = 0x12,
// MCU Temp
// MCU Temperature
// (((RV * (2.5 / 4096)) - 0.986) / 0.00355)
// °C

GETTEMPERATURESINFO_TEMPERATURES_BATTERY0 = 0x13,
// Batt. Temp. Sens. 1
// Batt. Cell 1 Temp.
// See Note 1
// °C

GETTEMPERATURESINFO_TEMPERATURES_BATTERY1 = 0x14,
// Batt. Temp. Sens. 2
// Batt. Cell 2 Temp.
// See Note 1
// °C

GETTEMPERATURESINFO_TEMPERATURES_BATTERY2 = 0x15,
// Batt. Temp. Sens. 3
// Batt. Cell 3 Temp.
// See Note 1
// °C

GETTEMPERATURESINFO_TEMPERATURES_BATTERY3 = 0x16,
// Batt. Temp. Sens. 4
// Batt. Cell 4 Temp.
// See Note 1
// °C

GETCONFIGURATIONINFO_CONFIG_INPUTCONDITIONS = 0x17,
// Input Condition
// Bits description in Table 10
// N/A

GETCONFIGURATIONINFO_CONFIG_OUTPUTCONDITIONS = 0x18,
// Output Condition 1
// Bits description in Table 11
// N/A

getConfigurationInfo_config_outputConditions = 0x19,
// Output Condition 2
// Bits description in Table 12
// N/A

getStatisticInfo_statistics_counters_powerOn = 0x1A,
// Power_ON_Cycles
// Counter for number of times the condition occurred
// N/A

getStatisticInfo_statistics_counters_underVoltage = 0x1B,
// V_Under_Voltage
// Counter for number of times the condition occurred
// N/A

getStatisticInfo_statistics_counters_shortCircuit = 0x1C,
// V_Short_Circuit
// Counter for number of times the condition occurred
// N/A

getStatisticInfo_statistics_counters_overtemperature = 0x1D,
// V_Over Temperature
// Counter for number of times the condition occurred
// N/A

getStatisticInfo_statistics_maxTemp0 = 0x1E,
// MAX_Temp 1
// Batt. Pack 1 Temp.Sens.1
// See Note 1
// °C

getStatisticInfo_statistics_maxTemp1 = 0x1F,
// MAX_Temp 2
// Batt. Pack 1 Temp.Sens.2
// See Note 1
// °C

getStatisticInfo_statistics_maxTemp2 = 0x20,
// MAX_Temp 3
// Batt. Pack 2 Temp.Sens.1
// See Note 1
// °C

getStatisticInfo_statistics_maxTemp3 = 0x21,
// MAX_Temp 4
// Batt. Pack 2 Temp.Sens.2
// See Note 1
// °C

getStatisticInfo_statistics_minTemp0 = 0x22,
// MIN_Temp 1
// Batt. Pack 1 Temp.Sens.1
// See Note 1
// °C

getStatisticInfo_statistics_minTemp1 = 0x23,
// MIN_Temp 2
// Batt. Pack 1 Temp.Sens.2
// See Note 1
// °C

getStatisticInfo_statistics_minTemp2 = 0x24,
// MIN_Temp 3
// Batt. Pack 2 Temp.Sens.1
// See Note 1
// °C

getStatisticInfo_statistics_minTemp3 = 0x25,
// MIN_Temp 4
// Batt. Pack 2 Temp.Sens.2
// See Note 1
// °C

getTemperaturesInfo_temperatures_battery4 = 0x26,
// Temp Sensor 5
// External Temp. Sensor 5
// See Note 1
// °C

getTemperaturesInfo_temperatures_battery5 = 0x27,
// Temp Sensor 6
// External Temp. Sensor 6
// See Note 1
// °C

getTemperaturesInfo_temperatures_battery6 = 0x28,
// Temp Sensor 7
// External Temp. Sensor 7
// See Note 1
// °C

getTemperaturesInfo_temperatures_battery7 = 0x29,
// Reserved (Temp Sensor 8)
// (for future use of External Temp. Sensor 8)
// See Note 1
// °C

getSoftwareVersion_ver_number = 0x2A,
// EPS Software Version
// Software version
// N/A

getConfigurationInfo_config_defaultOutputs0 = 0x2B,
// Defaults 1
// Default values of LUPs Fast charge modes See Table 13
// N/A

getConfigurationInfo_config_defaultOutputs1 = 0x2C,
// Defaults 2
// Default Values of Output 1 to 6 See Table 14
// N/A

getBusesInfo_buses_bus_3v3_volt = 0x31,
// 3.3 V Bus
// +3.3V Bus - 12 bit ADC Units
// *0.0023394775
// V

getBusesInfo_buses_bus_5v_volt = 0x32,
// 5 V Bus
// +5V Bus - 12 bit ADC Units
// *0.0023394775
// V

getStatisticInfo_statistics_uptime0 = 0x33,
// Uptime counter:16-bits
// Higher 16 bits of 32-bits uptime counter
// Uptime = (MSB « 16) | LSB
// s

getStatisticInfo_statistics_uptime1 = 0x34,
// Uptime counter: 32-bits
// Lower 16 bits of 32-bits uptime counter
// Uptime = (MSB « 16) | LSB
// s

getSoftwareVersion_buildDate0 = 0x35,
// buildDate bytes 1 and 2
// Part of the Build date: byte 1 and 2
// ASCII

getSoftwareVersion_buildDate1 = 0x36,
// buildDate bytes 3 and 4
// Part of the Build date: byte 3 and 4
// ASCII

getSoftwareVersion_buildDate2 = 0x37,
// buildDate bytes 5 and 6
// Part of the Build date: byte 5 and 6
// ASCII

getSoftwareVersion_buildDate3 = 0x38,
// buildDate bytes 7 and 8
// Part of the Build date: byte 7 and 8
// ASCII

getSoftwareVersion_buildDate4 = 0x39,
// buildDate bytes 9 and 10
// Part of the Build date: byte 9 and 10
// ASCII

getSoftwareVersion_buildDate5 = 0x3A,
// buildDate bytes 11 and 12
// Part of the Build date: byte 11 and 12
// ASCII

getSoftwareVersion_buildTime0 = 0x3B,
// buildTime bytes 1 and 2
// Part of the Build time: byte 1 and 2
// ASCII

getSoftwareVersion_buildTime1 = 0x3C,
// buildTime bytes 3 and 4
// Part of the Build time: byte 3 and 4
// ASCII

getSoftwareVersion_buildTime2 = 0x3D,
// buildTime bytes 5 and 6
// Part of the Build time: byte 5 and 6
// ASCII

getSoftwareVersion_buildTime3 = 0x3E,
// buildTime bytes 7 and 8
// Part of the Build time: byte 7 and 8
// ASCII

queryWatchdog_new_timer = 0x70,
// Watchdog timeout
// Time to execute watchdog reset after commands resetWatchdogTimer (0x72)
// N/A
// min

queryWatchdog_new_type = 0x71,
// Type watchdog
// Ignore/Disable/Payload Auto/Payload ON/System Auto/System ON See Note 2
// N/A

HellModeRead_Hell_mode_Vlow = 0x74,
// VBattLow HellMode
// Battery Voltage level to enter Hell mode
// N/A

HellModeRead_Hell_mode_Vhigh = 0x75,
// VBattHigh HellMode
// Battery Voltage level to exit Hell mode
// N/A

HellModeRead_Hell_mode_Tlow = 0x76,
// TLow HellMode
// EPS temperature to Exit Hell mode
// N/A

HellModeRead_Hell_mode_Thigh = 0x77,
// THigh HellMode
// EPS temperature to Enter Hell mode
// N/A

HeatersSettingsRead_Heaters_T1_low = 0x78,
// TLow Heater1
// Battery temperature at which to start heater 1
// N/A
// °C

HeatersSettingsRead_Heaters_hysteresis1 = 0x79,
// Hysteresis1
// Hysteresis of Heater 1 settings
// N/A
// °C

HeatersSettingsRead_Heaters_T2_low = 0x7A,
// TLow Heater2
// Battery temperature at which to start heater 2
// N/A
// °C

HeatersSettingsRead_Heaters_hysteresis2 = 0x7B,
// Hysteresis2
// Hysteresis of Heater 2 settings
// N/A
// °C

HeatersSettingsRead_Heaters_T3_low = 0x7C,
// TLow Heater3
// Battery temperature at which to start heater 3
// N/A
// °C

HeatersSettingsRead_Heaters_hysteresis3 = 0x7D,
// Hysteresis3
// Hysteresis of Heater 3 settings
// N/A
// °C

ToggleOutPut_actualTimeAtToggledState = 0x7E,
// Toggle Timeout
// Time to toggle an output (State=5 for CMD 0x00-0x19)
// N/A
// s

queryLaunchState_requested = 0x80,
// Enable PowerUp Delay
// Enable Delay for Power Lines after PowerUp
// N/A

queryLaunchState_Power_Up_Delay = 0x81,
// PowerUp Delay
// Waiting time for the power lines to be enabled after Power Up
// N/A
// min
} eps_i_commands;

// * Unit - Dimension after conversion
// Tables and footnotes refer to Eudurosat Electrical Power System EPS I 
// & EPS I Plus User Manual, Version 5.1, August 2022

class EPS_I : public Adafruit_Sensor {

 public: 
  /* Constructor */
  EPS_I(int32_t);

  bool getEvent(sensors_event_t*);
  void getSensor(sensor_t*);
  
 private:
   int32_t _sensorID;
};

#endif // EPS_I_H