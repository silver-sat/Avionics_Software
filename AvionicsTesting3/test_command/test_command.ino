/**
 * @file test_command.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test the SilverSat command class
 * @version 1.0.1
 * @date 2022-07-25
 *
 *
 */

#include "Command.h"

void setup()
{
    const String command0[]{
        "NoOperate",
        "Invalid",
        "Unknown",
        "PayComms",
        "ReportT",
        "TweeSlee",
        "Watchdog",
    };

    const Command::operation action0[]{
        Command::operation::no_operate,
        Command::operation::invalid,
        Command::operation::unknown,
        Command::operation::pay_comms,
        Command::operation::report_t,
        Command::operation::twee_slee,
        Command::operation::watchdog,
    };

    const String command1[]{
        "BeaconSp",
    };

    const int parameter0[]{};

    const Command::operation action1[]{
        Command::operation::beacon_sp,
    };

    const int parameter1[]{
        2 * 60,
    };

    const String command6[]{"PicTimes",
                            "SetClock"};

    const Command::operation action6[]{
        {Command::operation::pic_times},
        {Command::operation::set_clock},
    };

    const time_value parameter6[]{
        {12, 10, 2024, 10, 10, 0},
        {1, 15, 2024, 9, 15, 0}};

    Serial.begin(115200);
    while (!Serial)
    {
    };
    Serial.println("Testing Command class");

    Serial.println("Testing commands with no parameters");

    for (auto index = 0; index < (sizeof(command0) / sizeof(command0[0])); index++)
        {

            auto client = new Client(command0[index]);
            auto test = client->get_command();
            Serial.print(command0[index]);
            Serial.print(": ");
            Serial.print(test->get_operation());
            Serial.print(", ");
            if (test->get_operation() == action0[index])
            {
                Serial.println("OK");
            }
            else
            {
                Serial.println("Error");
            }
            delete client;
        };

    Serial.println("Testing commands with integer parameter");
    
    for (auto index = 0; index < (sizeof(command1) / sizeof(command1[0])); index++)
    {

        auto client = new Client(command1[index], parameter1[index]);
        auto test = client->get_command();
        Serial.print(command1[index]);
        Serial.print(": ");
        Serial.print(test->get_operation());
        Serial.print(", ");
        if (test->get_operation() == action1[index])
        {
            Serial.println("OK");
        }
        else
        {
            Serial.println("Error");
        }
        delete client;
    };

    Serial.println("Testing commands with time parameter");

    for (auto index = 0; index < (sizeof(command6) / sizeof(command6[0])); index++)
        {

            auto client = new Client(command6[index], parameter6[index]);
            auto test = client->get_command();
            Serial.print(command6[index]);
            Serial.print(": ");
            Serial.print(test->get_operation());
            Serial.print(", ");
            if (test->get_operation() == action6[index])
            {
                Serial.println("OK");
            }
            else
            {
                Serial.println("Error");
            }
            delete client;
        };

    Serial.println("Stress test");

    auto count {0};
    for (auto index = 0; index < 1000000; index++) {
        auto client = new Client(command6[0], parameter6[0]);
        auto test = client->get_command();
        count++;
        if (count >= 10000) {
            Serial.print(".");
            count = 0;
        }
        delete client;
    }
    Serial.println();
    Serial.println("Command class test complete");
};

void loop(){};