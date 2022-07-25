/**
 * @file test_command.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test the SilverSat command class
 * @version 1.0.0
 * @date 2022-07-25
 *
 *
 */

#include "command.h"

void setup()
{

    const String NoOperate{"NoOperate"};

    Serial.begin(115200);
    while (!Serial)
    {
    };
    Serial.println("Testing Command class");

    /**
     * @brief NoOperate command
     *
     */
    
    Command command_no_op;
    Serial.print("NoOperate: ");
    Serial.print(command_no_op.get_operation());
    if (command_no_op.get_operation() == Command::no_operate)
    {
        Serial.println("OK");
    }
    else
    {
        Serial.println("Error");
    };

    Serial.println("Command class test complete");
};

void loop(){};