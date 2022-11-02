/*
 * @file get_input.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Demonstrate function for user input
 * @version 1.0.0
 * @date 2022-11-02
 * 
 */

byte incomingByte{};

void setup() {
  Serial.begin(115200);
  while (!Serial) {}
}

void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    Serial.print("Received: ");
    Serial.println(incomingByte, DEC);
  }
}