/**
 * @file test_payload_states.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test Payload Board power states on Avionics Board
 * @version 1.0.0
 * @date 2022-10-18
 *
 * Based on Arduino blink.ino
 * 
 * Connect LED in series with a 220 ohm resistor to ground and H2 STATES_X pins
 */
#include <Arduino.h>

#define STATES_A_INT 9          /**< payload state A @hideinitializer */
#define STATES_B_INT 2          /**< payload state B @hideinitializer */
#define STATES_C_INT 5          /**< payload state C @hideinitializer */

void setup()
{
    Serial.begin(115200);
    while (!Serial)
    {
    }
    Serial.println("Starting payload states test");
    pinMode(STATES_A_INT, OUTPUT);
    pinMode(STATES_B_INT, OUTPUT);
    pinMode(STATES_C_INT, OUTPUT);
}

void loop()
{
    digitalWrite(STATES_A_INT, HIGH); // turn the LED on (HIGH is the voltage level)
    digitalWrite(STATES_B_INT, HIGH); // turn the LED on (HIGH is the voltage level)
    digitalWrite(STATES_C_INT, HIGH); // turn the LED on (HIGH is the voltage level)
    delay(1000);               // wait for a second
    digitalWrite(STATES_A_INT, LOW);  // turn the LED off by making the voltage LOW
    digitalWrite(STATES_B_INT, LOW);  // turn the LED off by making the voltage LOW
    digitalWrite(STATES_C_INT, LOW);  // turn the LED off by making the voltage LOW
    delay(1000);               // wait for a second
}