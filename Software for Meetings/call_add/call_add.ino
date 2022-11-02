/*
 * @file call_add.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Demonstrate calling a function in another file
 * @version 1.0.0
 * @date 2022-11-02
 * 
 */

 #include "add.h"


void setup() {

  Serial.begin(115200);
  while (!Serial) {}

  int a{ 5 };  // a is created, initialized, and enters scope here
  int b{ 6 };  // b is created, initialized, and enters scope here

  // a and b are usable within this function only

  Serial.println(add(a, b));

}  // b and a go out of scope and are destroyed here

void loop() {}
