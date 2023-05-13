/**
 * @file DateStruct.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Example date structure
 * @version 1.0.0
 * @date 2023-05-13
 *
 *
 */

#include <Arduino.h>

class DateStruct
{
public:
    DateStruct(int year, byte month, byte day, byte hour, byte minute, byte second)
    {
        if (year < 2000 || year > 2100)
            Serial.println("Year error!");
        m_year = year;
        m_month = month;
        m_day = day;
        m_hour = hour;
        m_minute = minute;
        m_second = second;
    }
int getYear();
bool printYear();

private:
int m_year;
byte m_month;
byte m_day;
byte m_hour;
byte m_minute;
byte m_second;
}
;
