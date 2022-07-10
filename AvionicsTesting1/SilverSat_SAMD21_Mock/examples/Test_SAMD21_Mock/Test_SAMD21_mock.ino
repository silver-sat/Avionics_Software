/**
 * @file Test_SAMD21_Mock.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test the mock SAMD21
 * @version 1.0.0
 * @date 2022-07-10
 *
 *
 */

#include <SilverSat_SAMD21_mock.h>

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

    // Reset

    Serial.println("Testing the reset function");
    Serial.print("Last reset time: ");
    Serial.println(samd21.get_last_reset_time(), HEX);
    Serial.println("Resetting the device");
    samd21.reset();
    Serial.print("Last reset time: ");
    Serial.println(samd21.get_last_reset_time(), HEX);
    Serial.println("Reset function test complete");

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

    // Access USB, I2C and Serial Port

    Serial.println("Testing USB, I2C and Serial Port");
    samd21.access_usb("Accessing USB");
    samd21.access_i2c("Accessing I2C");
    samd21.access_serial("Accessing Serial Port");
    Serial.println("USB, I2C and Serial Port tests complete");

    // Digital I/O

    Serial.println("Testing digital I/O");
    samd21.write_digital(3, HIGH);
    Serial.println("Digital write successful");
    samd21.read_digital(4);
    Serial.println("Digital read successful");
    Serial.println("Digial I/O test complete");

    // Analog I/O

    Serial.println("Testing analog I/O");
    samd21.write_analog(A0, 128);
    Serial.println("Analog write successful");
    samd21.read_analog(A0);
    Serial.println("Analog read successful");
    Serial.println("Analog I/O test complete");

    // End of test

    Serial.print("Completed SAMD21 Test Suite in ");
    Serial.print((millis() - start_time) / 1000.0, 3);
    Serial.println(" seconds");
}

void loop(void)
{
}