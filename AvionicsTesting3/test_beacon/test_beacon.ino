/**
 * @file test_beacon.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test the SilverSat beacon class
 * @version 1.0.0
 * @date 2022-07-25
 * 
 * 
 */

#include "beacon.h"

const String call_sign {"..--.. ..--.. ..--.. ..--.. ..--.. "};
const String default_beacon {call_sign + "..--.. ..--.. ..--.. ..--.. ..--.. "};
const String abcdf_beacon {call_sign + ".- -... -.-. -.. ..-. "};
const String ubucu_beacon {call_sign + "..--.. -... ..--.. -.-. ..--.. "};

void setup() {

Serial.begin(115200);
while(!Serial);
Serial.println("Testing Beacon class");

/**
 * @brief Default beacon
 * 
 */

Beacon beacon1 {Beacon::unknown, Beacon::unknown, Beacon::unknown, Beacon::unknown, Beacon::unknown};
Serial.print("Default: "); Serial.println(beacon1.get_code());
if (beacon1.get_code() == default_beacon) {
    Serial.println("OK");
} else {
    Serial.println("Error");
};

/**
 * @brief Status for all boards
 * 
 */

Beacon beacon2(Beacon::excellent, Beacon::good, Beacon::fair, Beacon::poor, Beacon::critical);
Serial.print("ABCDF: "); Serial.println(beacon2.get_code());
if (beacon2.get_code() == abcdf_beacon) {
    Serial.println("OK");
} else {
    Serial.println("Error");
}

/**
 * @brief Status for two boards
 * 
 */

Beacon beacon3(Beacon::unknown, Beacon::good, Beacon::unknown, Beacon::fair, Beacon::unknown);
Serial.print("UBUCU: "); Serial.println(beacon3.get_code());
if (beacon3.get_code() == ubucu_beacon) {
    Serial.println("OK");
} else {
    Serial.println("Error");
}

Serial.println("Beacon class test complete");

};

void loop(){};