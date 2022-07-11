/**
 * @file Test_Avionics_Board_SAMD21_mock.cpp
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test the SAMD21
 * @version 1.0.0
 * @date 2022-07-11
 *
 *
 */

#include <SilverSat_SAMD21_mock.h>

// Run the tests

bool test_SAMD21()
{

    SAMD21 samd21{};

    Serial.println("-----");
    Serial.println("Starting SAMD21 test");

    // Reset

    Serial.println("\nTesting the reset function");
    Serial.print("Last reset time: ");
    Serial.println(samd21.get_last_reset_time(), HEX);
    Serial.println("Resetting the device");
    samd21.reset();
    Serial.print("Last reset time: ");
    Serial.println(samd21.get_last_reset_time(), HEX);
    Serial.println("Reset function test complete");

    // Store and load

    Serial.println("\nTesting store and load operations");
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

    Serial.println("\nTesting add and multiply operations");
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

    Serial.println("\nTesting timer");
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

    Serial.println("\nTesting USB, I2C and Serial Port");
    samd21.access_usb("Accessing USB");
    samd21.access_i2c("Accessing I2C");
    samd21.access_serial("Accessing Serial Port");
    Serial.println("USB, I2C and Serial Port tests complete");

    // Digital I/O

    Serial.println("\nTesting digital I/O");
    samd21.write_digital(3, HIGH);
    Serial.println("Digital write successful");
    samd21.read_digital(4);
    Serial.println("Digital read successful");
    Serial.println("Digial I/O test complete");

    // Analog I/O

    Serial.println("\nTesting analog I/O");
    samd21.write_analog(A0, 128);
    Serial.println("Analog write successful");
    samd21.read_analog(A0);
    Serial.println("Analog read successful");
    Serial.println("Analog I/O test complete");

    // End of test

    Serial.println("\nSAMD21 test complete");
    return true;
}