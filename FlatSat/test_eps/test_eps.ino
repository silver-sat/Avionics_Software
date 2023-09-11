/**
 * @file test_eps.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test SilverSat Power Board
 * @version 1.0.0
 * @date 2023-09-11
 *
 * This tests the SilverSat Power Board I2C interface
 *
 */

#include "EPS_I.h"

EPS_I eps_i{}; /**< Power Board */

constexpr unsigned EN_EXT_I2C{11u}; /**< enable non-critical I2C @hideinitializer */

// Raw battery voltage cutoffs for beacon character and payload session power

constexpr float battery_excellent{3.8f};
constexpr float battery_good{3.7f};
constexpr float battery_fair{3.6f};
constexpr float payload_session_minimum{3.65f};

void setup()
{
    Serial.begin(57600);
    while (!Serial)
    {
    }
    {
        Serial.println("Initializing EPS-I");
        pinMode(EN_EXT_I2C, OUTPUT);
        digitalWrite(EN_EXT_I2C, LOW); // Enable non-critical bus

        if (eps_i.begin())
        {
            Serial.println("EPS-I initialization completed");
        }
        else
        {
            Serial.println("EPS-I not initialized");
        }
    }
}

void loop()
{
    Serial.println(" BBV " + String(eps_i.getBatteryVoltage()));
    Serial.println(" BBC " + String(eps_i.getBatteryCurrent()));
    Serial.println(" TS1 " + String(eps_i.getTemperatureSensor1()));
    Serial.println(" TS2 " + String(eps_i.getTemperatureSensor2()));
    Serial.println(" 5VC " + String(eps_i.get5VCurrent()));
    Serial.println(" L5V " + String(eps_i.getLUP_5VVoltage()));
    Serial.println(" H1S " + String(eps_i.getHeater1State()));
    Serial.println(" H2S " + String(eps_i.getHeater2State()));
    Serial.println(" H3S " + String(eps_i.getHeater3State()));
    delay(2000);
}