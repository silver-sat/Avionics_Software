/**
 * @file DateStruct.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Implement DateStruct
 * @version 1.0.0
 * @date 2023-05-13
 * 
 * 
 */
#include "DateStruct.h"

int DateStruct::getYear() {
    return m_year;
}

/**
 * @brief Print the year
 * 
 * @return true successful
 * @return false error
 */
bool DateStruct::printYear()
{
    Serial.println("Printing from DateStruct");
    size_t status {Serial.println(m_year)};
    if (status < 4) {
        return false;
    } else {
        return true;
    }
}