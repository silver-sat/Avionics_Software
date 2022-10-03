/**
 * @file rollover_signed.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Demonstrate rollover of counter, signed arithmetic
 * @version 1.0.0
 * @date 2022-10-03
 *
 *
 */

void print_variables(String status, int8_t counter, int8_t start, int8_t difference)
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

    int8_t counter{'\xFE'};
    int8_t start{'\xEE'};
    int8_t difference{counter - start};
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