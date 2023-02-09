/**
 * @file arrays.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Array example for meeting
 * @version 1.0.0
 * @date 2023-02-07
 *
 *
 */

constexpr int max_tokens{10};

void setup()
{
    Serial.begin(19200);
    while (!Serial) {}
    Serial.println("Starting array example");
    
    String tokens[max_tokens]{};

    tokens[0] = "SetClock";
    tokens[1] = "2023";
    tokens[2] = "2";
    tokens[3] = "11";
    tokens[4] = "10";
    tokens[5] = "10";
    tokens[6] = "00";

    for (auto i = 0; i < 7; ++i)
    {
        Serial.print("tokens[");
        Serial.print(i);
        Serial.print("] contains: ");
        Serial.println(tokens[i]);
    }
}

void loop()
{
}