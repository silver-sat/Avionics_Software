/**
 * @file test_Serial_transmit.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test Serial1 transmit with loop
 * @version 1.0.0
 * @date 2022-10-19
 *
 *
 */

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
  }
  Serial.println("Starting Serial test");
}

auto counter{1};
void loop()
{
  Serial.print("Testing Serial output ");
  Serial.println(counter++);
  delay(2000);
}
