//
// Mock MPU6050 for demonstration and testing
// Lee A. Congdon
// 26 June 2022
//

#ifndef SILVERSAT_MPU6050_MOCK_H
#define SILVERSAT_MPU6050_MOCK_H

#include <Adafruit_MPU6050.h>

class MPU6050 : public Adafruit_MPU6050
{
public:
    bool begin() const {return true;}

};

#endif