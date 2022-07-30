/**
 * @file timestamp.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Helper function to display test timestamps
 * @version 1.0.0
 * @date 2022-07-30
 * 
 * 
 */

#include "AvionicsBoard.h"

void timestamp()
{
    extern AvionicsBoard avionics;
    if (avionics.get_external_rtc_is_set())
    {
        Serial.print(avionics.get_year(), DEC);
        Serial.print('/');
        Serial.print(avionics.get_month(), DEC);
        Serial.print('/');
        Serial.print(avionics.get_day(), DEC);
        Serial.print(' ');
        Serial.print(avionics.get_hour(), DEC);
        Serial.print(':');
        Serial.print(avionics.get_minute(), DEC);
        Serial.print(':');
        Serial.print(avionics.get_second(), DEC);
        Serial.print(" UTC ");
    }

    Serial.print("[");
    Serial.print(micros());
    Serial.print("] ");
};
