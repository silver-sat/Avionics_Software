/**
 * @file DS1337.h
 * @author Ben Cohen (ben@silversat.org)
 * @brief Device driver for DS1337 Real Time Clock
 * @version 1.0.0
 * @date 2023-7-7
 *
 * Based and dependent on Adafruit RTClib
 *
 * This file declares the class that interfaces with the external realtime clock
 * 
 * RTC and IMU have the same I2C addresses but are located on different buses
 *
 */

#pragma once 

#include <RTClib.h>

class RTC_DS1337 final : RTC_I2C
{
public:
    bool begin(TwoWire *wireInstance = &Wire);
    void adjust(const DateTime &dt);
    DateTime now();
   
  
};