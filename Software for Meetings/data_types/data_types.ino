/**
 * @file data_types.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Demonstrate data types
 * @version 1.0.0
 * @date 2022-11-19
 *
 *
 */


void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  Serial.println("Data types");


  // variables can't be declared as type void

  size_t st{};
  Serial.print("size_t ");
  Serial.print("st: ");
  Serial.print(st);
  Serial.print(" size: ");
  Serial.println(sizeof(st));

  bool b{ true };
  Serial.print("bool ");
  Serial.print("b: ");
  Serial.print(b);
  Serial.print(" size: ");
  Serial.println(sizeof(b));

  // boolean is a non-standard alias for bool
  boolean bn{ true };
  Serial.print("boolean ");
  Serial.print("bn: ");
  Serial.print(bn);
  Serial.print(" size: ");
  Serial.println(sizeof(bn));

  byte y{ 0xFF };
  Serial.print("byte ");
  Serial.print("y: ");
  Serial.print(y);
  Serial.print(" size: ");
  Serial.println(sizeof(y));

  unsigned char uc{ 'b' };
  Serial.print("unsigned char ");
  Serial.print("uc: ");
  Serial.print(uc);
  Serial.print(" size: ");
  Serial.println(sizeof(uc));

  char c{ 'b' };
  Serial.print("char ");
  Serial.print("c: ");
  Serial.print(c);
  Serial.print(" size: ");
  Serial.println(sizeof(c));

  word w{ 42 };
  Serial.print("word ");
  Serial.print("w: ");
  Serial.print(w);
  Serial.print(" size: ");
  Serial.println(sizeof(w));

  short s{ -42 };
  Serial.print("short ");
  Serial.print("s: ");
  Serial.print(s);
  Serial.print(" size: ");
  Serial.println(sizeof(s));

  unsigned int ui{ 42 };
  Serial.print("unsigned int ");
  Serial.print("ui: ");
  Serial.print(ui);
  Serial.print(" size: ");
  Serial.println(sizeof(ui));

  int i{ -42 };
  Serial.print("int ");
  Serial.print("i: ");
  Serial.print(i);
  Serial.print(" size: ");
  Serial.println(sizeof(i));

  unsigned long ul{ 2e9 };
  Serial.print("unsigned long ");
  Serial.print("ul: ");
  Serial.print(ul);
  Serial.print(" size: ");
  Serial.println(sizeof(ul));

  long l{ -2e9 };
  Serial.print("long ");
  Serial.print("l: ");
  Serial.print(l);
  Serial.print(" size: ");
  Serial.println(sizeof(l));

  float f{ 42.0 };
  Serial.print("float ");
  Serial.print("f: ");
  Serial.print(f);
  Serial.print(" size: ");
  Serial.println(sizeof(f));

  double d{ 42.0 };
  Serial.print("double ");
  Serial.print("d: ");
  Serial.print(d);
  Serial.print(" size: ");
  Serial.println(sizeof(d));

  char cstr[]{ "test string" };
  Serial.print("string ");
  Serial.print("cstr: ");
  Serial.print(cstr);
  Serial.print(" size: ");
  Serial.println(sizeof(cstr));

  String string{ "test string" };
  Serial.print("String ");
  Serial.print("string: ");
  Serial.print(string);
  Serial.print(" size: ");
  Serial.println(sizeof(string));

  // an array is a collection of variables of the same type
  int a[]{ 4, 3, 5, 7, 2 };
  Serial.print("int array ");
  Serial.print("a: ");
  for (size_t item : a) {
    Serial.print(item);
    Serial.print(" ");
  }
  Serial.print(" size: ");
  Serial.println(sizeof(a));
}


void loop() {}
