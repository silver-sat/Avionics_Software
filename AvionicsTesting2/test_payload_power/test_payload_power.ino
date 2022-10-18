/**
 * @file test_payload_power.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test Payload Board power on signal on Avionics Board
 * @version 1.0.0
 * @date 2022-10-18
 *
 * 
 */
#include <Arduino.h>

#define PLD_ON_A 17             /**< payload on A @hideinitializer */
#define PLD_ON_B 18             /**< payload on B @hideinitializer */
#define PLD_ON_C 8              /**< payload on C @hideinitializer */

void setup()
{
    Serial.begin(115200);
    while (!Serial)
    {
    }
    Serial.println("Starting payload power on test");
    pinMode(PLD_ON_A, OUTPUT);
    pinMode(PLD_ON_B, OUTPUT);
    pinMode(PLD_ON_C, OUTPUT);
}

void loop()
{
    digitalWrite(PLD_ON_A, HIGH); // turn the LED on (HIGH is the voltage level)
    digitalWrite(PLD_ON_B, HIGH); // turn the LED on (HIGH is the voltage level)
    digitalWrite(PLD_ON_C, HIGH); // turn the LED on (HIGH is the voltage level)
    delay(1000);               // wait for a second
    digitalWrite(PLD_ON_A, LOW);  // turn the LED off by making the voltage LOW
    digitalWrite(PLD_ON_B, LOW);  // turn the LED off by making the voltage LOW
    digitalWrite(PLD_ON_C, LOW);  // turn the LED off by making the voltage LOW
    delay(1000);               // wait for a second
}