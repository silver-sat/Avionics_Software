/**
 * @file EPS_I.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief SilverSat device driver for Endurosat EPS I
 * @version 1.0.0
 * @date 2022-10-23
 *
 * Based on the Adafruit Sensor Library
 *
 * This file declares the class that interfaces with the Power Board
 *
 */

#pragma once

#include <Adafruit_I2CDevice.h>
#include <Adafruit_Sensor.h>
#include "Arduino.h"

/**
 * @brief EPS_I Constants
 *
 */
// todo: consider changing case of constants
constexpr uint8_t EPS_I_I2C_ADDRESS{0x18};                                                 /**< I2C address of EPS I */
constexpr float GETBATTERYINFO_BATTERY_BATT_VOLT_COEFFICIENT{0.0023394775};                /**< Battery voltage coefficient */
constexpr float GETBATTERYINFO_BATTERY_BATT_CURR_COEFFICIENT{0.0030517578};                /**< Battery current coefficient */
constexpr float GETTEMPERATURESINFO_TEMPERATURES_BATTERY_COEFFICIENT_POSITIVE{0.00390625}; /**< Battery temperature coefficient positive */
constexpr float GETTEMPERATURESINFO_TEMPERATURES_BATTERY_COEFFICIENT_NEGATIVE{-0.0624};    /**< Battery temperature coefficient negative */
constexpr float GETSOLARPANELSINFO_SOLAR_Z_CURR_NEG_COEFFICIENT{0.0006103516};             /**< Solar Z current coefficient negative */
constexpr float GETBUSESINFO_BUSES_BUS_5V_CURR_COEFFICIENT{0.0020345052};                  /**< Bus 5 volt current coefficient */

/**
 * @brief Read commands
 *
 */
enum class EPS_I_Read_Command
{
  // ESPS Command = I2C Command
  // EPS parameter
  // Controlled feature
  // Conversion coefficient
  // Unit Dimension after conversion

  // Tables and footnotes refer to Eudurosat Electrical Power System EPS I
  // & EPS I Plus User Manual, Version 5.1, August 2022

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

  GETCONFIGURATIONINFO_CONFIG_OUTPUTCONDITIONS1 = 0x18,
  // Output Condition 1
  // Bits description in Table 11
  // N/A

  GETCONFIGURATIONINFO_CONFIG_OUTPUTCONDITIONS2 = 0x19,
  // Output Condition 2
  // Bits description in Table 12
  // N/A

  GETSTATISTICINFO_STATISTICS_COUNTERS_POWERON = 0x1A,
  // Power_ON_Cycles
  // Counter for number of times the condition occurred
  // N/A

  GETSTATISTICINFO_STATISTICS_COUNTERS_UNDERVOLTAGE = 0x1B,
  // V_Under_Voltage
  // Counter for number of times the condition occurred
  // N/A

  GETSTATISTICINFO_STATISTICS_COUNTERS_SHORTCIRCUIT = 0x1C,
  // V_Short_Circuit
  // Counter for number of times the condition occurred
  // N/A

  GETSTATISTICINFO_STATISTICS_COUNTERS_OVERTEMPERATURE = 0x1D,
  // V_Over Temperature
  // Counter for number of times the condition occurred
  // N/A

  GETSTATISTICINFO_STATISTICS_MAXTEMP0 = 0x1E,
  // MAX_Temp 1
  // Batt. Pack 1 Temp.Sens.1
  // See Note 1
  // °C

  GETSTATISTICINFO_STATISTICS_MAXTEMP1 = 0x1F,
  // MAX_Temp 2
  // Batt. Pack 1 Temp.Sens.2
  // See Note 1
  // °C

  GETSTATISTICINFO_STATISTICS_MAXTEMP2 = 0x20,
  // MAX_Temp 3
  // Batt. Pack 2 Temp.Sens.1
  // See Note 1
  // °C

  GETSTATISTICINFO_STATISTICS_MAXTEMP3 = 0x21,
  // MAX_Temp 4
  // Batt. Pack 2 Temp.Sens.2
  // See Note 1
  // °C

  GETSTATISTICINFO_STATISTICS_MINTEMP0 = 0x22,
  // MIN_Temp 1
  // Batt. Pack 1 Temp.Sens.1
  // See Note 1
  // °C

  GETSTATISTICINFO_STATISTICS_MINTEMP1 = 0x23,
  // MIN_Temp 2
  // Batt. Pack 1 Temp.Sens.2
  // See Note 1
  // °C

  GETSTATISTICINFO_STATISTICS_MINTEMP2 = 0x24,
  // MIN_Temp 3
  // Batt. Pack 2 Temp.Sens.1
  // See Note 1
  // °C

  GETSTATISTICINFO_STATISTICS_MINTEMP3 = 0x25,
  // MIN_Temp 4
  // Batt. Pack 2 Temp.Sens.2
  // See Note 1
  // °C

  GETTEMPERATURESINFO_TEMPERATURES_BATTERY4 = 0x26,
  // Temp Sensor 5
  // External Temp. Sensor 5
  // See Note 1
  // °C

  GETTEMPERATURESINFO_TEMPERATURES_BATTERY5 = 0x27,
  // Temp Sensor 6
  // External Temp. Sensor 6
  // See Note 1
  // °C

  GETTEMPERATURESINFO_TEMPERATURES_BATTERY6 = 0x28,
  // Temp Sensor 7
  // External Temp. Sensor 7
  // See Note 1
  // °C

  GETTEMPERATURESINFO_TEMPERATURES_BATTERY7 = 0x29,
  // Reserved (Temp Sensor 8)
  // (for future use of External Temp. Sensor 8)
  // See Note 1
  // °C

  GETSOFTWAREVERSION_VER_NUMBER = 0x2A,
  // EPS Software Version
  // Software version
  // N/A

  GETCONFIGURATIONINFO_CONFIG_DEFAULTOUTPUTS0 = 0x2B,
  // Defaults 1
  // Default values of LUPs Fast charge modes See Table 13
  // N/A

  GETCONFIGURATIONINFO_CONFIG_DEFAULTOUTPUTS1 = 0x2C,
  // Defaults 2
  // Default Values of Output 1 to 6 See Table 14
  // N/A

  GETBUSESINFO_BUSES_BUS_3V3_VOLT = 0x31,
  // 3.3 V Bus
  // +3.3V Bus - 12 bit ADC Units
  // *0.0023394775
  // V

  GETBUSESINFO_BUSES_BUS_5V_VOLT = 0x32,
  // 5 V Bus
  // +5V Bus - 12 bit ADC Units
  // *0.0023394775
  // V

  GETSTATISTICINFO_STATISTICS_UPTIME0 = 0x33,
  // Uptime counter:16-bits
  // Higher 16 bits of 32-bits uptime counter
  // Uptime = (MSB « 16) | LSB
  // s

  GETSTATISTICINFO_STATISTICS_UPTIME1 = 0x34,
  // Uptime counter: 32-bits
  // Lower 16 bits of 32-bits uptime counter
  // Uptime = (MSB « 16) | LSB
  // s

  GETSOFTWAREVERSION_BUILDDATE0 = 0x35,
  // buildDate bytes 1 and 2
  // Part of the Build date: byte 1 and 2
  // ASCII

  GETSOFTWAREVERSION_BUILDDATE1 = 0x36,
  // buildDate bytes 3 and 4
  // Part of the Build date: byte 3 and 4
  // ASCII

  GETSOFTWAREVERSION_BUILDDATE2 = 0x37,
  // buildDate bytes 5 and 6
  // Part of the Build date: byte 5 and 6
  // ASCII

  GETSOFTWAREVERSION_BUILDDATE3 = 0x38,
  // buildDate bytes 7 and 8
  // Part of the Build date: byte 7 and 8
  // ASCII

  GETSOFTWAREVERSION_BUILDDATE4 = 0x39,
  // buildDate bytes 9 and 10
  // Part of the Build date: byte 9 and 10
  // ASCII

  GETSOFTWAREVERSION_BUILDDATE5 = 0x3A,
  // buildDate bytes 11 and 12
  // Part of the Build date: byte 11 and 12
  // ASCII

  GETSOFTWAREVERSION_BUILDTIME0 = 0x3B,
  // buildTime bytes 1 and 2
  // Part of the Build time: byte 1 and 2
  // ASCII

  GETSOFTWAREVERSION_BUILDTIME1 = 0x3C,
  // buildTime bytes 3 and 4
  // Part of the Build time: byte 3 and 4
  // ASCII

  GETSOFTWAREVERSION_BUILDTIME2 = 0x3D,
  // buildTime bytes 5 and 6
  // Part of the Build time: byte 5 and 6
  // ASCII

  GETSOFTWAREVERSION_BUILDTIME3 = 0x3E,
  // buildTime bytes 7 and 8
  // Part of the Build time: byte 7 and 8
  // ASCII

  QUERYWATCHDOG_NEW_TIMER = 0x70,
  // Watchdog timeout
  // Time to execute watchdog reset after commands resetWatchdogTimer (0x72)
  // N/A
  // min

  QUERYWATCHDOG_NEW_TYPE = 0x71,
  // Type watchdog
  // Ignore/Disable/Payload Auto/Payload ON/System Auto/System ON See Note 2
  // N/A

  HELLMODEREAD_HELL_MODE_VLOW = 0x74,
  // VBattLow HellMode
  // Battery Voltage level to enter Hell mode
  // N/A

  HELLMODEREAD_HELL_MODE_VHIGH = 0x75,
  // VBattHigh HellMode
  // Battery Voltage level to exit Hell mode
  // N/A

  HELLMODEREAD_HELL_MODE_TLOW = 0x76,
  // TLow HellMode
  // EPS temperature to Exit Hell mode
  // N/A

  HELLMODEREAD_HELL_MODE_THIGH = 0x77,
  // THigh HellMode
  // EPS temperature to Enter Hell mode
  // N/A

  HEATERSSETTINGSREAD_HEATERS_T1_LOW = 0x78,
  // TLow Heater1
  // Battery temperature at which to start heater 1
  // N/A
  // °C

  HEATERSSETTINGSREAD_HEATERS_HYSTERESIS1 = 0x79,
  // Hysteresis1
  // Hysteresis of Heater 1 settings
  // N/A
  // °C

  HEATERSSETTINGSREAD_HEATERS_T2_LOW = 0x7A,
  // TLow Heater2
  // Battery temperature at which to start heater 2
  // N/A
  // °C

  HEATERSSETTINGSREAD_HEATERS_HYSTERESIS2 = 0x7B,
  // Hysteresis2
  // Hysteresis of Heater 2 settings
  // N/A
  // °C

  HEATERSSETTINGSREAD_HEATERS_T3_LOW = 0x7C,
  // TLow Heater3
  // Battery temperature at which to start heater 3
  // N/A
  // °C

  HEATERSSETTINGSREAD_HEATERS_HYSTERESIS3 = 0x7D,
  // Hysteresis3
  // Hysteresis of Heater 3 settings
  // N/A
  // °C

  TOGGLEOUTPUT_ACTUALTIMEATTOGGLEDSTATE = 0x7E,
  // Toggle Timeout
  // Time to toggle an output (State=5 for CMD 0x00-0x19)
  // N/A
  // s

  QUERYLAUNCHSTATE_REQUESTED = 0x80,
  // Enable PowerUp Delay
  // Enable Delay for Power Lines after PowerUp
  // N/A

  QUERYLAUNCHSTATE_POWER_UP_DELAY = 0x81,
  // PowerUp Delay
  // Waiting time for the power lines to be enabled after Power Up
  // N/A
  // min
};

/**
 * @brief Note 2 constants
 *
 */
enum class EPS_I_Query_Watchdog
{
  Ignore = 0,       // Used only for EnduroSat Protocol Stack I (ESPS I) to read current values.
  Disable = 1,      // The Watchdog is turned off, not in use.
  Payload_Auto = 2, // The Watchdog resets only the payload. Starts automatically, after first command resetWatchdogTimer (0x72).
  Payload_ON = 3,   // The Watchdog resets only the payload. Starts immediately after power ON.
  System_Auto = 4,  // The Watchdog resets the whole system. Starts automatically, after first command resetWatchdogTimer (0x72).
  System_ON = 5,    // The Watchdog resets the whole system. Starts immediately after power ON.
};

/**
 * @brief Table 10 constants: Command 23
 *
 */

enum class EPS_I_Input_Condition_1
{
  // Least Significant Bit
  KS_Lock_Reset = 0 // Reset SW Self Lock
                    // Unused
                    // Most Significant Bit
};

/**
 * @brief Table 11 constants: Command 24
 *
 */

enum class EPS_I_Output_Condition_1
{
  // Least Significant Bit
  SWSelfLock = 0,     // SW Self Lock
  VBATTENEnable = 1,  // Battery BUS
  BCROutENEnable = 2, // BCR BUS
  SHD_3_3V = 3,       // Enable 3.3V BUS
  SHD_5V = 4,         // Enable 5V BUS
                      // RESERVED = 5,
                      // RESERVED = 6,
  OUT1 = 7,           // Output 1 / Payload
  OUT2 = 8,           // Output 2
  OUT3 = 9,           // Output 3
  OUT4 = 10,          // Output 4/ OBC
  OUT5 = 11,          // Output 5/ UHF
  OUT6 = 12,          // Output 6
  Heater_1 = 13,      // Battery heater 1
  Heater_2 = 14,      // Battery heater 2
  Heater_3 = 15,      // Battery heater 3
                      // Most Significant Bit
};

/**
 * @brief Table 12 constants: Command 25
 *
 */

enum class EPS_I_Output_Condition_2
{
  // Least Significant Bit
  LUP_3_3V = 0,                      // Latch-up Protected output 3.3V (High Level - OFF)
  LUP_5V = 1,                        // Latch-up Protected output 5V (High Level - OFF)
  SHDChrg = 2,                       // Shutdown Battery Charger (High Level - OFF) Maximum Current 230mA.
  Fast_Charge_230mA0 = 3,            // Fast battery charge. Maximum current limit is increased with 230mA
  Fast_Charge_230mA1 = 4,            // Fast battery charge. Maximum current limit is increased with 230mA
  I2C_PULLUP_RES_10K = 5,            // Pull up resistor for I2 C communication (10kΩ)
  I2C_PULLUP_RES_4K7 = 6,            // Pull up resistor for I2 C communication (4.7kΩ)
  RS485_120_OHM_TERMINATING_RES = 7, // Terminating resistor for RS485 communication (120Ω)
  OUT7 = 8,                          // Output 7
  OUT8 = 9,                          // Output 8
                                     // 10 unused
                                     // 11 unused
                                     // 12 unused
                                     // 13 unused
                                     // 14 unused
                                     // 15 unused
                                     // Most Significant Bit
};

/**
 * @brief Table 13 constants: Command 43
 *
 */

enum class EPS_I_Defaults_1
{
  // Least Significant Bit
  LUP_3_3V_Default = 0,              //   State on power up ofoutput “LUP 3.3V” (High Level - OFF)
  LUP_5V_Default = 1,                // State on power up of output “LUP 5V” (High Level - OFF)
  Fast_Charge_230mA_Default0 = 2,    // State on power up of output “Fast Charge +230mA”
  Fast_Charge_230mA_Default1 = 3,    // State on power up of output “Fast Charge +2300mA”
  I2C_PULLUP_RES_10K = 4,            // Pull up resistor for I2C communication (10kΩ)
  I2C_PULLUP_RES_4K7 = 5,            // Pull up resistor for I2C communication (4.7kΩ)
  RS485_120_OHM_TERMINATING_RES = 6, // Terminating resistor for RS485 communication (120Ω)
                                     // 7 unused
                                     // 8 unused
                                     // 9 unused
                                     // 10 unused
                                     // 10 unused
                                     // 11 unused
                                     // 12 unused
                                     // 13 unused
                                     // 14 unused
                                     // 15 unused
                                     // Most Significant Bit
};

/**
 * @brief Table 14 constants: Command 44
 *
 */

enum class EPS_I_Defaults_2
{
  // Least Significant Bit
  Output_1_Default = 0, // State on power up of output OUT 1
  Output_2_Default = 1, // State on power up of output OUT 2
  Output_3_Default = 2, // State on power up of output OUT 3
  Output_4_Default = 3, // State on power up of output OUT 4
  Output_5_Default = 4, // State on power up of output OUT 5
  Output_6_Default = 5, // State on power up of output OUT 6
  Output_7_Default = 6, // State on power up of output OUT 7
  Output_8_Default = 7, // State on power up of output OUT 8
                        // 8 unused
                        // 9 unused
                        // 10 unused
                        // 10 unused
                        // 11 unused
                        // 12 unused
                        // 13 unused
                        // 14 unused
                        // 15 unused
                        // Most Significant Bit
};

/**
 * @brief EPS Write Command
 *
 */
enum class EPS_I_Write_Command
{
  // ESPS Command = I2C Command
  // EPS Parameter
  // Default State
  // Controlled Feature
  // Tables and footnotes refer to Eudurosat Electrical Power System EPS I
  // & EPS I Plus User Manual, Version 5.1, August 2022

  QUERYCONTROLS_AND_TOGGLEOUTPUT00 = 0x00,
  // SWSelfLock
  // 0x00-OFF / 0x01-ON
  // Self Lock Switch

  QUERYCONTROLS_AND_TOGGLEOUTPUT01 = 0x01,
  // VBATTEN
  // 0x00-OFF / 0x01-ON
  // Battery BUS

  QUERYCONTROLS_AND_TOGGLEOUTPUT02 = 0x02,
  // BCROutEN
  // 0x00-OFF / 0x01-ON
  // BCR BUS

  QUERYCONTROLS_AND_TOGGLEOUTPUT03 = 0x03,
  // SHD_3V3
  // 0x00-OFF / 0x01-ON
  // 3V3 BUS

  QUERYCONTROLS_AND_TOGGLEOUTPUT04 = 0x04,
  // SHD_5V
  // 0x00-OFF / 0x01-ON
  // 5V BUS

  QUERYCONTROLS_AND_TOGGLEOUTPUT05 = 0x05,
  // LUP3V3
  // 0x00-ON / 0x01-OFF
  // Latch-up protected 3V3 BUS

  QUERYCONTROLS_AND_TOGGLEOUTPUT06 = 0x06,
  // LUP5V
  // See CMD 0x31 bit0
  // Latch-up protected 5V BUS

  QUERYCONTROLS_AND_TOGGLEOUTPUT07 = 0x07,
  // SHDChrg
  // See CMD 0x31 bit1
  // Battery Charger Suppression / shutdown

  QUERYCONTROLS_AND_TOGGLEOUTPUT08 = 0x08,
  // Chrg_I1
  // See CMD 0x32 bit0
  // Fast/Slow Battery Charge 1

  QUERYCONTROLS_AND_TOGGLEOUTPUT09 = 0x09,
  // Chrg_I2
  // See CMD 0x32 bit1
  // Fast/Slow Battery Charge 2

  QUERYCONTROLS_AND_TOGGLEOUTPUT0A = 0x0A,
  // OUT1
  // See CMD 0x33
  // Output 1 / Payload

  QUERYCONTROLS_AND_TOGGLEOUTPUT0B = 0x0B,
  // OUT2
  // See CMD 0x34
  // Output 2

  QUERYCONTROLS_AND_TOGGLEOUTPUT0C = 0x0C,
  // OUT3
  // See CMD 0x35
  // Output 3

  QUERYCONTROLS_AND_TOGGLEOUTPUT0D = 0x0D,
  // OUT4
  // See CMD 0x36
  // Output 4 / OBC

  QUERYCONTROLS_AND_TOGGLEOUTPUT0E = 0x0E,
  // OUT5
  // See CMD 0x37
  // Output 5 / UHF

  QUERYCONTROLS_AND_TOGGLEOUTPUT0F = 0x0F,
  // OUT6
  // See CMD 0x38
  // Output 6

  QUERYCONTROLS_AND_TOGGLEOUTPUT10 = 0x10,
  // Heater 1
  // 0x00 - OFF
  // Battery Heater 1

  QUERYCONTROLS_AND_TOGGLEOUTPUT11 = 0x11,
  // Heater 2
  // 0x00 - OFF
  // Battery Heater 2

  QUERYCONTROLS_AND_TOGGLEOUTPUT12 = 0x12,
  // Heater 3
  // 0x00 - OFF
  // Battery Heater 3

  QUERYCONTROLS_AND_TOGGLEOUTPUT13 = 0x13,
  // 10k I2C pull up
  // See CMD 0x39 bit0
  // 10kΩ I2C pull-up resistor

  QUERYCONTROLS_AND_TOGGLEOUTPUT14 = 0x14,
  // 4k7 I2C pull up
  // See CMD 0x39 bit1
  // 4k7Ω I2C pull-up resistor

  QUERYCONTROLS_AND_TOGGLEOUTPUT15 = 0x15,
  // Rs485 Termination Resistor
  // See CMD 0x39 bit2
  // Enable the 120Ω Termination Resistor at RS485 so the differential resistance from A to B is 120Ω

  QUERYCONTROLS_AND_TOGGLEOUTPUT16 = 0x16,
  // OUT7
  // See CMD 0x40
  // Output 7

  QUERYCONTROLS_AND_TOGGLEOUTPUT17 = 0x17,
  // OUT8
  // See CMD 0x41
  // Output 8

  TOGGLEOUTPUT18 = 0x18,
  // Reset_MPPT
  // N/A
  // Resets All MPPT Chargers

  QUERYDEFAULTS31 = 0x31,
  // LUP3V3, LUP5V
  // ON, ON
  // Default for Latch-up protected 3.3V (0x00-ON / 0x01-OFF) & 5V BUSES

  QUERYDEFAULTS32 = 0x32,
  // Chrg_I1, Chrg_I2
  // ON, OFF
  // Default for Fast/Slow Battery Charge 1 & 2 (0x00-OFF / 0x01-ON)

  QUERYDEFAULTS33 = 0x33,
  // OUT1
  // OFF
  // Default for Output 1 (0x00-OFF / 0x01-ON)

  QUERYDEFAULTS34 = 0x34,
  // OUT2
  // OFF
  // Default for Output 2 (0x00-OFF / 0x01-ON)

  QUERYDEFAULTS35 = 0x35,
  // OUT3
  // OFF
  // Default for Output 3 (0x00-OFF / 0x01-ON)

  QUERYDEFAULTS36 = 0x36,
  // OUT4
  // OFF
  // Default for Output 4 (0x00-OFF / 0x01-ON)

  QUERYDEFAULTS37 = 0x37,
  // OUT5
  // OFF
  // Default for Output 5 (0x00-OFF / 0x01-ON)

  QUERYDEFAULTS38 = 0x38,
  // OUT6
  // OFF
  // Default for Output 6 (0x00-OFF / 0x01-ON)

  QUERYDEFAULTS39 = 0x39,
  // 10k pull up 4k7 I2C pull up RS485 120R,
  // OFF ON ON
  // Default for 10kΩ, 4k7 I2C pull-up resistors, Termination resistor RS485 (0x01-OFF / 0x00-ON)

  QUERYDEFAULTS40 = 0x40,
  // OUT7
  // OFF
  // Default for Output 7 (0x00-OFF / 0x01-ON)

  QUERYDEFAULTS = 0x41,
  // OUT8
  // OFF
  // Default for Output 8 (0x00-OFF / 0x01-ON)

  QUERYWATCHDOG_NEW_TIMER = 0x70,
  // Watchdog timeout
  // 30(min)
  // Time to execute watchdog reset after commands resetWatchdogTimer (0x72)

  QUERYWATCHDOG_NEW_TYPE = 0x71,
  // Type watchdog
  // Payload Auto
  // Disable/Payload Auto/Payload ON/System Auto/System ON See Note 3

  RESETWATCHDOG = 0x72,
  // Postpone WD reset
  // Resets the watchdog timer. Postpones the Watchdog reset on timeout

  RESETPOWERSUPPLY = 0x73,
  // Request EPS Reset
  // Request Kill/ Hard Reset/ Soft Reset/ Payload Reset See Note 4

  HELLMODEWRITE_VLOW = 0x74,
  // VBattLow HellMode
  // 3.51 V 187 (RoundDown(3.51 V / 0.01871582))
  // Battery Voltage level to enter Hell mode

  HELLMODEWRITE_VHIGH = 0x75,
  // VBattHigh HellMode
  // 3.90 V 207 (RoundDown(3.90 V / 0.01871582))
  // Battery Voltage level to exit Hell mode

  HELLMODEWRITE_TLOW = 0x76,
  // TLow HellMode
  // 45°C
  // EPS temperature to Exit Hell mode

  HELLMODEWRITE_THIGH = 0x77,
  // THigh HellMode
  // 55°C
  // EPS temperature to Enter Hell mode

  HEATERSSETTINGSWRITE_T1_LOW = 0x78,
  // TLow Heater1
  // 5°C
  // Battery temperature at which to start heater 1

  HEATERSSETTINGSWRITE_HYSTERESIS1 = 0x79,
  // Hysteresis1
  // 3°C
  // Hysteresis of Heater 1 settings

  HEATERSSETTINGSWRITE_T2_LOW = 0x7A,
  // TLow Heater2
  // 1°C
  // Battery temperature at which to start heater 2

  HEATERSSETTINGSWRITE_HYSTERESIS2 = 0x7B,
  // Hysteresis2
  // 3°C
  // Hysteresis of Heater 2 settings

  HEATERSSETTINGSWRITE_T3_LOW = 0x7C,
  // TLow Heater3
  // -2°C
  // Battery temperature in at which to start heater 3

  HEATERSSETTINGSWRITE_HYSTERESIS3 = 0x7D,
  // Hysteresis3
  // 3°C
  // Hysteresis of Heater 3 settings

  TOGGLEOUTPUT7E = 0x7E,
  // Toggle Timeout
  // 2s
  // Time to toggle an output (State=5 for CMD 0x00-0x19)

  QUERYLAUNCHSTATE_REQUESTED = 0x80,
  // Enable PowerUp Delay
  // OFF
  // Enable Delay for Power Lines after PowerUp

  QUERYLAUNCHSTATE_POWER_UP_DELAY = 0x81,
  // PowerUp Delay
  // 5 min
  // Waiting time for the power lines to be enabled after Power Up [min]
};

/**
 * @brief Write command states for 0x00 to 0x17
 *
 * 0x18 accepts only 5, toggle
 *
 */
enum class EPS_I_Write_State
{
  OFF = 0,            // turns in ON or OFF temporarily (until the next command, reset or internal algorithm are required to change it)
  ON = 1,             // turns in ON or OFF temporarily (until the next command, reset or internal algorithm are required to change it)
  FORCED_OFF = 2,     // turns it ON or OFF regardless of internal algorithms (until the next command or reset)
  FORCED_ON = 3,      // turns it ON or OFF regardless of internal algorithms (until the next command or reset)
  TOGGLE = 5,         // toggles the state of an output for the time set by the 0x7E command (default: 2 seconds)
  SET_TO_DEFAULT = 6, // sets the output temporarily to the default state
};

/**
 * @brief Note 3 constants
 *
 */
enum class EPS_I_Query_Watchdog_New_Type
{
  Ignore = 0,       // Used only for ESPS I to read current values.
  Disable = 1,      // The Watchdog is turned off, not in use.
  Payload_Auto = 2, // The Watchdog resets only the payload. Starts automatically, after first command resetWatchdogTimer (0x72).
  Payload_ON = 3,   // The Watchdog resets only the payload. Starts immediately after power ON.
  System_Auto = 4,  // The Watchdog resets the whole system. Starts automatically, after first command resetWatchdogTimer (0x72).
  System_ON = 5,    // The Watchdog resets the whole system. Starts immediately after power ON.
};

/**
 * @brief Note 4 constants
 *
 */
enum class EPS_I_Reset_Power_Supply
{
  security_key0 = 0x00, // Payload reset (power failure simulation)
  security_key1 = 0x12, // Soft MCU reset - waits for critical tasks to be done first
  security_key2 = 0x5A, // Hard MCU reset - resets the MCU faster, however still tries to send a response
  security_key3 = 0xDE, // ’Kill It!’ - resets MCU ASAP, no response is almost guaranteed.
};

/**
 * @brief EPS_I class declaration
 *
 */

class EPS_I final
{

public:
  /**
   * @brief Construct a new EPS I::EPS I object
   *
   */

  EPS_I();

  /**
   * @brief Set up the hardware and initialize I2C
   *
   */

  bool begin(uint8_t i2c_address, TwoWire *wire);

  /**
   * @brief Get the battery voltage
   *
   */

  float getBatteryVoltage(void) const;

  /**
   * @brief Get the battery current
   *
   */

  float getBatteryCurrent(void) const;

  /**
   * @brief Get the temperature at sensor 1
   *
   */

  float getTemperatureSensor1(void) const;

  /**
   * @brief Get the temperature at sensor 2
   *
   */

  float getTemperatureSensor2(void) const;

  /**
   * @brief Get the temperature at sensor 3
   *
   */

  float getTemperatureSensor3(void) const;

  /**
   * @brief Get the Z negative panel current
   *
   */

  float getZNegativeCurrent(void) const;

  /**
   * @brief Get the 5 volt current
   *
   */

  float get5VCurrent(void) const;

  /**
   * @brief Get the heater 1 state
   *
   */

  bool getHeater1State(void) const;

  /**
   * @brief Get the heater 2 state
   *
   */

  bool getHeater2State(void) const;

  /**
   * @brief Get the heater 3 state
   *
   */

  bool getHeater3State(void) const;

private:
  /**
   * @brief Initialization code for EPS I
   *
   */

  bool _init(void);

  /**
   * @brief Read 16 bits of data from the EPS I
   *
   */

  uint16_t read_value(EPS_I_Read_Command command) const;

  /**
   * @brief Write an 8-bit command and 8-bit state to the EPS I
   *
   */

  void write_command(EPS_I_Write_Command command, uint8_t state);

  Adafruit_I2CDevice *i2c_dev;
};