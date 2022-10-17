/**
 * @file test_Serial1.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Test Serial1 connectivity
 * @version 1.0.0
 * @date 2022-10-17
 *
 * Based on Arduino MultiSerial.ino
 *
 */
/*
  Multiple Serial test

  Receives from the main serial port, sends to the others.
  Receives from serial port 1, sends to the main serial (Serial 0).

  This example works only with boards with more than one serial like Arduino Mega, Due, Zero etc.

  The circuit:
  - any serial device attached to Serial port 1
  - Serial Monitor open on Serial port 0

  created 30 Dec 2008
  modified 20 May 2012
  by Tom Igoe & Jed Roach
  modified 27 Nov 2015
  by Arturo Guadalupi

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/MultiSerialMega
*/
constexpr unsigned EN_RADIO_SERIAL{10u}; /**< enable radio serial @hideinitializer */

void setup()
{
  // initialize both serial ports:
  Serial.begin(115200);
  pinMode(EN_RADIO_SERIAL, OUTPUT);
  digitalWrite(EN_RADIO_SERIAL, HIGH);
  Serial1.begin(115200);
}

void loop()
{
  // read from port 1, send to port 0:
  if (Serial1.available())
  {
    int inByte = Serial1.read();
    Serial.write(inByte);
  }

  // read from port 0, send to port 1:
  if (Serial.available())
  {
    int inByte = Serial.read();
    Serial1.write(inByte);
  }
}
