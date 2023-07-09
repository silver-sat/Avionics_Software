/**
 * @file DS1337.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Device driver for DS1337 Real Time Clock
 * @version 1.0.0
 * @date 2022-10-17
 *
 * Based and dependent on Adafruit RTClib
 *
 * This file declares the class that interfaces with the external realtime clock
 * 
 * RTC and IMU have the same I2C addresses but are located on different buses
 *
 */

#pragma once

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wunused"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wdeprecated-copy"
#include <RTClib.h>
#pragma GCC diagnostic pop

// todo: resolve object creation location and use address constant
constexpr unsigned RTC_I2C_ADDRESS{0x68};   /**< realtime clock I2C address @hideinitializer */

/**
 * @brief DS1337 SQW pin mode settings
 *
 */
enum Ds1337SqwPinMode
{
    DS1337_OFF = 0x1C,            /**< Off */
    DS1337_SquareWave1Hz = 0x00,  /**< 1Hz Square Wave */
    DS1337_SquareWave4kHz = 0x08, /**< 4kHz Square Wave */
    DS1337_SquareWave8kHz = 0x10, /**< 8kHz Square Wave */
    DS1337_SquareWave32kHz = 0x18 /**< 32kHz Square Wave */
};

/**
 * @brief DS1337 Alarm modes for Alarm 1
 *
 */
enum Ds1337Alarm1Mode
{
    DS1337_A1_PerSecond = 0x0F, /**< Alarm once per second */
    DS1337_A1_Second = 0x0E,    /**< Alarm when seconds match */
    DS1337_A1_Minute = 0x0C,    /**< Alarm when minutes and seconds match */
    DS1337_A1_Hour = 0x08,      /**< Alarm when hours, minutes
                                     and seconds match */
    DS1337_A1_Date = 0x00,      /**< Alarm when date (day of month), hours,
                                     minutes and seconds match */
    DS1337_A1_Day = 0x10        /**< Alarm when day (day of week), hours,
                                     minutes and seconds match */
};

/**
 * @brief DS1337 Alarm modes for Alarm 2
 *
 */
enum Ds1337Alarm2Mode
{
    DS1337_A2_PerMinute = 0x7, /**< Alarm once per minute
                                    (whenever seconds are 0) */
    DS1337_A2_Minute = 0x6,    /**< Alarm when minutes match */
    DS1337_A2_Hour = 0x4,      /**< Alarm when hours and minutes match */
    DS1337_A2_Date = 0x0,      /**< Alarm when date (day of month), hours
                                    and minutes match */
    DS1337_A2_Day = 0x8        /**< Alarm when day (day of week), hours
                                    and minutes match */
};

/**
 * @brief RTC based on the DS1337 chip connected via I2C and the Wire libary
 *
 */
class RTC_DS1337 final : RTC_I2C
{
public:
    bool begin(TwoWire *wireInstance = &Wire);
    void adjust(const DateTime &dt);
    bool lostPower(void);
    DateTime now();
    Ds1337SqwPinMode readSqwPinMode();
    void writeSqwPinMode(Ds1337SqwPinMode mode);
    bool setAlarm1(const DateTime &dt, Ds1337Alarm1Mode alarm_mode);
    bool setAlarm2(const DateTime &dt, Ds1337Alarm2Mode alarm_mode);
    DateTime getAlarm1();
    DateTime getAlarm2();
    Ds1337Alarm1Mode getAlarm1Mode();
    Ds1337Alarm2Mode getAlarm2Mode();
    void disableAlarm(uint8_t alarm_num);
    void clearAlarm(uint8_t alarm_num);
    bool alarmFired(uint8_t alarm_num);
    /*!
        @brief  Convert the day of the week to a representation suitable for
                storing in the DS1337: from 1 (Monday) to 7 (Sunday).
        @param  d Day of the week as represented by the library:
                from 0 (Sunday) to 6 (Saturday).
        @return the converted value
    */
    static uint8_t dowToDS1337(uint8_t d) { return d == 0 ? 7 : d; }
};