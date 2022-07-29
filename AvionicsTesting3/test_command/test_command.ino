/**
 * @file test_command.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test SilverSat command construction
 * @version 1.0.0
 * @date 2022-07-29
 *
 *
 */
#include "Command.h"

void setup()

{
    Serial.begin(115200);
    while (!Serial)
    {
    };
    Serial.println("Testing Command class");


        auto test = Command("NoOperate");
        Serial.print("NoOperate");
        Serial.print(": ");
        Serial.print(test.get_operation());
        Serial.print(", ");
        if (test.get_operation() == Command::operation::no_operate)
        {
            Serial.println("OK");
        }
        else
        {
            Serial.println("Error");
        }

    Serial.println("End Command class test");
}

void loop(){};