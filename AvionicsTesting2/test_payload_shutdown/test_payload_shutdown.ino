/**
 * @file test_payload_shutdown.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test Payload Board power shutdown signal on Avionics Board
 * @version 1.0.0
 * @date 2022-10-18
 *
 * Connect H2 SHUTDOWN_X to +3.3V or ground
 */
#include <Arduino.h>

#define SHUTDOWN_A 19           /**< payload shutdown A @hideinitializer */
#define SHUTDOWN_B 36           /**< payload shutdown B @hideinitializer */
#define SHUTDOWN_C 37           /**< payload shutdown C @hideinitializer */

void setup()
{
    Serial.begin(115200);
    while (!Serial)
    {
    }
    Serial.println("Starting payload shutdown test");
    pinMode(SHUTDOWN_A, INPUT);
    pinMode(SHUTDOWN_B, INPUT);
    pinMode(SHUTDOWN_C, INPUT);
}

void loop()
{
    Serial.print("SHUTDOWN_A: ");
    Serial.println(digitalRead(SHUTDOWN_A));
    Serial.print("SHUTDOWN_B: ");
    Serial.println(digitalRead(SHUTDOWN_B));
    Serial.print("SHUTDOWN_C: ");
    Serial.println(digitalRead(SHUTDOWN_C));
    delay(1000);               
}