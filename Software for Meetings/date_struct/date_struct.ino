/**
 * @file date_struct.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Example date structure
 * @version 1.0.0
 * @date 2023-05-13
 *
 *
 */

#include "DateStruct.h"
#include <Arduino.h>

void setup()
{
    Serial.begin(9600);
    while (!Serial)
        ;
    Serial.println("DateStruct example");
    DateStruct ds{2023, 5, 13, 17, 0, 0};
    if (ds.printYear())
        Serial.println("Success");
    else
        Serial.println("Error");
    // int year = ds.getYear();
    // Serial.println(year);
    DateStruct eds {2320, 5, 13, 17, 0, 0};
    Serial.println("Ending example");
}

void loop()
{
}