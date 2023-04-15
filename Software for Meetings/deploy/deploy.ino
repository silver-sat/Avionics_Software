/***************************************************************************
  This is a library for the BMP280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BMP280 Breakout
  ----> http://www.adafruit.com/products/2651

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

#define BMP_SCK (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS (10)

Adafruit_BMP280 bmp; // I2C
                     // Adafruit_BMP280 bmp(BMP_CS); // hardware SPI
                     // Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

float altitudeFactor{1013.25};

/* Reading data */
float reading1{};
float reading2{};
float reading3{};
float altitudeMaximum{0.0};     // initially less than the maximum
float altitudeMinimum{10000.0}; // initially more than the minimum

void setup()
{
    Serial.begin(9600);
    while (!Serial)
        delay(100); // wait for native usb
    Serial.println(F("Deploy test"));
    unsigned status;
    // status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
    status = bmp.begin();
    if (!status)
    {
        Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                         "try a different address!"));
        Serial.print("SensorID was: 0x");
        Serial.println(bmp.sensorID(), 16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1)
            delay(10);
    }

    /* Default settings from datasheet. */
    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                    Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                    Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                    Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                    Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

    // set initial values
    reading2 = bmp.readAltitude(altitudeFactor);
    reading3 = bmp.readAltitude(altitudeFactor);
}

void loop()
{
    reading1 = reading2; // discard oldest reading
    reading2 = reading3;
    reading3 = bmp.readAltitude(altitudeFactor); // store newest reading

    float altitude = (reading1 + reading2 + reading3) / 3.0; // current smoothed average
    if (altitude > altitudeMaximum)
        altitudeMaximum = altitude; // this will increase until mid flight
    if (altitude < altitudeMinimum) // could compute once in setup() if confident sensor is stable from the start or use zero if close to sea level
        altitudeMinimum = altitude;

    float height{altitudeMaximum - altitudeMinimum}; // distance from ground to highest altitude so far
    float triggerDistance{height * .10};             // choose your value, 10% here

    // check to insure higher than 20 meters to prevent a problem with variable readings at low height, again, choose your value
    // and vehicle is now 10% below its maximum
    if ((height > 20) && (altitude < (altitudeMaximum - triggerDistance)))
    {
        // deploy parachute
    }
}
