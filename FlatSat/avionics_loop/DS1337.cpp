
#include "DS1337.h"
#include <RTClib.h>

#define DS1337_ADDRESS 0x68   ///< I2C address for DS1337
#define DS1337_TIME 0x00      ///< Time register
#define DS1337_ALARM1 0x07    ///< Alarm 1 register
#define DS1337_ALARM2 0x0B    ///< Alarm 2 register
#define DS1337_CONTROL 0x0E   ///< Control register
#define DS1337_STATUSREG 0x0F




bool RTC_DS1337::begin(TwoWire *wireInstance)
{
  if (i2c_dev)
    delete i2c_dev;
  // todo: verify I2C device not already present
  i2c_dev = new Adafruit_I2CDevice(DS1337_ADDRESS, wireInstance);
  if (!i2c_dev->begin(false))
    return false;
  return true;
}

void RTC_DS1337::adjust(const DateTime &dt)
{
  uint8_t buffer[8] = {DS1337_TIME,
                       bin2bcd(dt.second()),
                       bin2bcd(dt.minute()),
                       bin2bcd(dt.hour()),
                       bin2bcd(dowToDS1337(dt.dayOfTheWeek())),
                       bin2bcd(dt.day()),
                       bin2bcd(dt.month()),
                       bin2bcd(dt.year() - 2000U)};
  i2c_dev->write(buffer, 8);

  uint8_t statreg = read_register(DS1337_STATUSREG);
  statreg &= ~0x80; // flip OSF bit
  write_register(DS1337_STATUSREG, statreg);
}

DateTime RTC_DS1337::now()
{
  uint8_t buffer[7];
  buffer[0] = 0;
  i2c_dev->write_then_read(buffer, 1, buffer, 7);

  return DateTime(bcd2bin(buffer[6]) + 2000U, bcd2bin(buffer[5] & 0x7F),
                  bcd2bin(buffer[4]), bcd2bin(buffer[2]), bcd2bin(buffer[1]),
                  bcd2bin(buffer[0] & 0x7F));
}

/**
 * @brief Read the SQW pin mode
 * @return Pin mode, see Ds1337SqwPinMode enum
 *
 */
