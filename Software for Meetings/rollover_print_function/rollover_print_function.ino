/**
 * @file rollover_print_function.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Demonstrate rollover of counter with print function
 * @version 1.0.0
 * @date 2022-10-03
 *
 *
 */

void print_variables(String status, uint8_t counter, uint8_t start, uint8_t difference)
{
    Serial.println(status);
    Serial.print("counter: ");
    Serial.print(counter);
    Serial.print(" (0x");
    Serial.print(counter, HEX);
    Serial.println(")");
    Serial.print("start: ");
    Serial.print(start);
    Serial.print(" (0x");
    Serial.print(start, HEX);
    Serial.println(")");
    Serial.print("difference: ");
    Serial.print(difference);
    Serial.print(" (0x");
    Serial.print(difference, HEX);
    Serial.println(")");
    return;
}

void setup()
{
    Serial.begin(115200);
    while (!Serial)
    {
    }

    // Difference before rollover

    uint8_t counter{'\xFE'};
    uint8_t start{'\xEE'};
    uint8_t difference{counter - start};
    print_variables("Before rollover", counter, start, difference);

    // Difference with rollover

    counter += 15;
    difference = counter - start;
    print_variables("After rollover", counter, start, difference);

    // Difference after start updated

    start = counter;
    counter += 17;
    difference = counter - start;
    print_variables("After start updated", counter, start, difference);
}

void loop() {}