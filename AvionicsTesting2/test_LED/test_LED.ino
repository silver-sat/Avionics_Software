/**
 * @file test_LED.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test LED on Avionics Board
 * @version 1.0.0
 * @date 2022-10-13
 *
 * Based on Arduino blink.ino
 * 
 * Connect LED in series with a 220 ohm resistor to J1 ground and GPIO_A pin
 */
#include <Arduino.h>
constexpr unsigned GPIO_A{14u};
void setup()
{
    Serial.begin(115200);
    while (!Serial)
    {
    }
    Serial.println("Starting LED test");
    pinMode(GPIO_A, OUTPUT);
}

void loop()
{
    digitalWrite(GPIO_A, HIGH); // turn the LED on (HIGH is the voltage level)
    delay(1000);               // wait for a second
    digitalWrite(GPIO_A, LOW);  // turn the LED off by making the voltage LOW
    delay(1000);               // wait for a second
}