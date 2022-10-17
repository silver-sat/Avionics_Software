/**
 * @file Test_SAMD21.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test the SAMD21
 * @version 1.0.0
 * @date 2022-07-21
 *
 *
 */

#include "test_SAMD21.h"

constexpr unsigned GPIO_A{14u};

void setup(void)
{

    // Run the tests

    Serial.begin(115200);
    while (!Serial)
        ;
    auto start_time = millis();
    Serial.println();
    Serial.println("Starting SAMD21 Test");
    SAMD21 samd21{};

    // Store and load

    Serial.println("Testing store and load operations");
    samd21.store(1, 42);
    if (samd21.load(1) == 42)
    {
        Serial.println("Store and load successful");
    }
    else
    {
        Serial.println("Store and load failed");
    };

    Serial.println("Store and load operation test complete");

    // Add and multiply

    Serial.println("Testing add and multiply operations");
    if (samd21.add(2, 2) == 4)
    {
        Serial.println("Addition test successful");
    }
    else
    {
        Serial.println("Addition test failed");
    };
    if (samd21.multiply(6, 7) == 42)
    {
        Serial.println("Multiplication test successful");
    }
    else
    {
        Serial.println("Multiplication test failed");
    };

    Serial.println("Add and multiply test complete");

    // Read timer

    Serial.println("Testing timer");
    auto now = samd21.read_timer();
    delay(10);
    if ((samd21.read_timer() - now) > 0)
    {
        Serial.println("Timer test successful");
    }
    else
    {
        Serial.println("Timer test failed");
    };

    Serial.println("Timer test complete");

    // Digital I/O

    Serial.println("Testing digital I/O");
    for (auto count = 1; count < 6; count++)

    // use built in led to verify digital writes

    {
        Serial.print(".");
        samd21.write_digital(GPIO_A, HIGH);
        delay(1000);
        samd21.write_digital(GPIO_A, LOW);
        delay(1000);
    }
    Serial.println("\nDigital write successful");

    // connect J1 pin 5 to ground and J1 pin 6 to +3.3V

    auto pin_J1_5 = samd21.read_digital(9u);
    Serial.print("J1 Pin 5: ");
    Serial.println(pin_J1_5);
    auto pin_J1_6 = samd21.read_digital(19u);
    Serial.print("J1 Pin 6: ");
    Serial.println(pin_J1_6);
    Serial.println("Digital read successful");
    Serial.println("Digital I/O test complete");

    // End of test

    Serial.print("Completed SAMD21 Test Suite in ");
    Serial.print((millis() - start_time) / 1000.0, 3);
    Serial.println(" seconds");
}

void loop(void)
{
}