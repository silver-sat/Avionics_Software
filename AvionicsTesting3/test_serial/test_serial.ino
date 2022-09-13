/**
 * @file test_serial.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test second Arduino serial port
 * @version 1.0.0
 * @date 2022-09-13
 * 
 * 
 */

void setup() {
    Serial.begin(115200);
    while (!Serial) {};
    Serial.println("Serial connected");
    Serial1.println("Serial connected");
    Serial1.begin(115200);
    while (!Serial1) {};
    Serial.println("Serial1 connected");
    Serial1.println("Serial1 connected");
}

void loop() {

}