/**
 * @file switch.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Demonstration of switch statement
 * @version 1.0.0
 * @date 2023-06-09
 *
 *
 */
void printDigitName(int value) {
  switch (value) {
    case 1:
      Serial.println("One");
      break;
    case 2:
      Serial.println("Two");
      break;
    case 3:
      Serial.println("Three");
      break;
    default:
      Serial.println("Unknown");
      break;
  }
}


void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  for (int index{ 0 }; index <= 4; ++index) {
    printDigitName(index);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
