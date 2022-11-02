/*
 * @file functional_separation.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Demonstrate variable scopes and lifetimes
 * @version 1.0.0
 * @date 2022-11-02
 * 
 */

int add(int x, int y)  // x and y are created and enter scope here
{
  // x and y are visible/usable within this function only
  return x + y;
}  // y and x go out of scope and are destroyed here


void setup() {

  Serial.begin(115200);
  while (!Serial) {}

  int a{ 5 };  // a is created, initialized, and enters scope here
  int b{ 6 };  // b is created, initialized, and enters scope here

  // a and b are usable within this function only

  Serial.println(add(a, b));

}  // b and a go out of scope and are destroyed here

void loop() {}