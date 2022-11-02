/*
 * @file print_input.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Demonstrate function return for user input
 * @version 1.0.0
 * @date 2022-11-02
 * 
 */

int get_input() {
  while (!Serial.available()) {}
  return Serial.read();
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {}
}

void loop() {
  int incomingByte{ get_input() };
  Serial.print("Received: ");
  Serial.println(incomingByte, DEC);
}