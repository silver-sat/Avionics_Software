/**
 * @file test_command.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test the SilverSat command class
 * @version 1.0.1
 * @date 2022-07-25
 *
 *
 */

#include "command.h"

/**
 * @brief test a command
 *
 */
void run_test(String operation, Command::operation action)
{

    auto test = Command::create(operation);
    Serial.print(operation);
    Serial.print(": ");
    Serial.print(test->get_operation());
    Serial.print(", ");
    if (test->get_operation() == action)
    {
        Serial.println("OK");
    }
    else
    {
        Serial.println("Error");
    }
};

void setup()
{
    const String command[]{"NoOperate",
                           "Invalid",
                           "Unknown",
                           "PayComms",
                           "ReportT",
                           "TweeSlee"};

    const Command::operation action[]{Command::operation::no_operate,
                                      Command::operation::invalid,
                                      Command::operation::unknown,
                                      Command::operation::pay_comms,
                                      Command::operation::report_t,
                                      Command::operation::twee_slee};

    Serial.begin(115200);
    while (!Serial)
    {
    };
    Serial.println("Testing Command class");

    for (auto index = 0; index < (sizeof(command) / sizeof(command[0])); index++) {
        run_test(command[index], action[index]);
    }

    Serial.println("Command class test complete");
};

void loop(){};