//
// Mock MPU6050 for demonstration and testing
// Lee A. Congdon
// 26 June 2022
//

#ifndef MPU6050_MOCK_H
#define MPU6050_MOCK_H

#include <Adafruit_MPU6050.h>

class MPU6050_Mock : public Adafruit_MPU6050
{
public:
    bool begin() const {return true;}
};

#endif