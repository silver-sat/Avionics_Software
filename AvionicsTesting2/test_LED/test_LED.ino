/**
 * @file test_LED.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test LED on Avionics Board
 * @version 1.0.0
 * @date 2022-10-13
 *
 * Based on Arduino blink.ino
 */
#include <Arduino.h>
constexpr unsigned TXLED{32u};
void setup()
{
    Serial.begin(115200);
    while (!Serial)
    {
    }
    Serial.println("Starting LED test");
    pinMode(TXLED, OUTPUT);
}

void loop()
{
    digitalWrite(TXLED, HIGH); // turn the LED on (HIGH is the voltage level)
    delay(1000);               // wait for a second
    digitalWrite(TXLED, LOW);  // turn the LED off by making the voltage LOW
    delay(1000);               // wait for a second
}