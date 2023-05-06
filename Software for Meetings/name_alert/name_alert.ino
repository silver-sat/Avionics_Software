//
// Arduino Programming Workshop name_alert Challenge Problem
// Lee A. Congdon
// May 6, 2023
//
void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  Serial.println("Lee Congdon");

  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);

  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);

  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
}
