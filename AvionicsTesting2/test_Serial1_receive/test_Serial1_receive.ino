/**
 * @file test_Serial1_receive.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test Serial1 receive with loop
 * @version 1.0.0
 * @date 2022-10-19
 *
 *
 */
constexpr unsigned EN_RADIO_SERIAL{10u}; /**< enable radio serial @hideinitializer */

void setup()
{
  // initialize both serial ports:
  Serial.begin(115200);
  while (!Serial)
  {
  }
  Serial.println("Starting Serial1 receive test");
  pinMode(EN_RADIO_SERIAL, OUTPUT);
  digitalWrite(EN_RADIO_SERIAL, HIGH);
  Serial1.begin(115200);
}

void loop()
{
  while (Serial1.available()) {
    Serial.write(Serial1.read());
  }
}
