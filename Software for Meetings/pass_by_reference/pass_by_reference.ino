/**
 * @file pass_by_reference.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Demonstrate pass by reference
 * @version 1.0.0
 * @date 2022-11-19
 *
 *
 */

int add(int &a, int &b) {
  a = 10;
  b = 5;    
  return a + b;
}


void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  int a{ 20 };
  int b{ 22 };
  Serial.print("a: ");
  Serial.print(a);
  Serial.print(" b: ");
  Serial.println(b);
  Serial.print("sum: ");
  Serial.println(add(a, b));
  Serial.print("a: ");
  Serial.print(a);
  Serial.print(" b: ");
  Serial.println(b);
}

void loop() {}
