/**
 * @file memory_leak.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Demonstrate memory leak
 * @version 1.0.0
 * @date 2023-01-06
 *
 *
 */

constexpr long serial_speed{115200};
constexpr size_t m{1024};
byte* p{nullptr};

void setup()
{
    Serial.begin(serial_speed);
    while (!Serial)
    {
    }
}

void loop()
{
    p = new byte[m];
    Serial.println("Allocated 1024 bytes");
}