/**
 * @file SilverSat_MPU6050_mock.h
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Mock MPU6050 for demonstration and testing
 * @version 1.0.0
 * @date 2022-06-27
 * 
 * 
 */

// This is a header only implementation

#ifndef SILVERSAT_MPU6050_MOCK_H
#define SILVERSAT_MPU6050_MOCK_H

#include <Adafruit_MPU6050.h>

class MPU6050 : public Adafruit_MPU6050
{
public:
    bool begin() const {return true;}

};

#endif