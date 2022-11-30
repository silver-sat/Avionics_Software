/**
 * @file bytes.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Demonstrate data types
 * @version 1.0.0
 * @date 2022-11-20
 *
 *
 */


void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  Serial.println("byte comparison");

  // true (non zero) or false (zero)
  bool b{ true };
  Serial.print("bool ");
  Serial.print("b = ");
  Serial.println(b, BIN);

  // 8-bit unsigned number, 0 to 255
  byte y{ 0xAA };
  Serial.print("byte ");
  Serial.print("y = 0x");
  Serial.println(y, HEX);

  // same as byte
  unsigned char uc{ 42 };
  Serial.print("unsigned char ");
  Serial.print("uc = ");
  Serial.println(uc);

  // single character value
  char c{ 'b' };
  Serial.print("char ");
  Serial.print("c = ");
  Serial.println(c);

  // byte operations
  byte x{ y - y - 1};
  Serial.print("y - y - 1 = ");
  Serial.println(x);

  // char operations
  char z{c - 'a' + 'A' };
  Serial.print("c - 'a' + 'A' = ");
  Serial.println(z);

  // 8-bit signed number, -128 to 127
  int8_t u{126};
  for (int8_t i = 0; i < 4; i++) {
    Serial.print("u + ");
    Serial.print(i);
    Serial.print(" = ");
    Serial.println(u);
    u += 1;
  }
}


void loop() {}
