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
    const String Invalid{"Invalid"};
    const String Unknown{"Unknown"};

    Serial.begin(115200);
    while (!Serial)
    {
    };
    Serial.println("Testing Command class");


    /**
     * @brief NoOperate command
     *
     */
    
    Command command_no_op {"NoOperate"};
    Serial.print(NoOperate); Serial.print(": ");
    Serial.println(command_no_op.get_operation());
    if (command_no_op.get_operation() == Command::no_operate)
    {
        Serial.println("OK");
    }
    else
    {
        Serial.println("Error");
    };

    /**
     * @brief Default constructor
     * 
     */

    Command command_default {"Invalid"};
    Serial.print(Invalid); Serial.print(": ");
    Serial.println(command_default.get_operation());
    if (command_default.get_operation() == Command::invalid)
    {
        Serial.println("OK");
    }
    else
    {
        Serial.println("Error");
    };

    /**
     * @brief Unknown command
     * 
     */

    Command command_unknown {"Unknown"};
    Serial.print(Unknown); Serial.print(": ");
    Serial.println(command_unknown.get_operation());
    if (command_unknown.get_operation() == Command::unknown)
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