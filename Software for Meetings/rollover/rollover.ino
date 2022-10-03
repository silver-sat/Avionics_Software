/**
 * @file rollover.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Demonstrate rollover of counter
 * @version 1.0.0
 * @date 2022-10-03
 *
 *
 */

void setup()
{
    Serial.begin(115200);
    while (!Serial)
    {
    }

    // Difference before rollover

    uint32_t counter{0xFFFFFFFE};
    uint32_t start{0xFFFFFFF2};
    uint32_t difference{counter - start};

    Serial.println("Before rollover");
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

    // Difference with rollover

    counter += 15;
    difference = counter - start;

    Serial.println("After rollover");
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

    // Difference after start updated

    start = counter;
    counter += 17;
    difference = counter - start;

    Serial.println("After start updated");
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
}

void loop() {}