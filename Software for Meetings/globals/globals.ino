/**
 * @file globals.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Demonstrate global variables
 * @version 1.0.0
 * @date 2022-11-19
 *
 *
 */
int a{ 20 };
int b{ 22 };

// the local variables a and b shadow the global variables
int add(int a, int b) {
  ::a = 10;
  ::b = 5;
  return a + b;
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {}

// global variables a and b
  Serial.print("a: ");
  Serial.print(a);
  Serial.print(" b: ");
  Serial.println(b);
  Serial.println();
  
// call the add function with copies of the global variables
  Serial.print("sum: ");
  Serial.println(add(a, b));
  Serial.println();
  
// the global variables are unchanged by the assignments in add
  Serial.print("a: ");
  Serial.print(a);
  Serial.print(" b: ");
  Serial.println(b);
  Serial.println();
}

void loop() {}
