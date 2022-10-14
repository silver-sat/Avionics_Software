This folder contains the variant files for the Adafruit Metro M0 Express to add 2 extra HW serial ports (3 total) and 1 extra wire port (2 total).

Put these in the appropriate variants folder.  For example on my system it was:

C:\Users\conra\AppData\Local\arduino15\packages\adafruit\hardware\samd\1.7.10\variants\metro_m0

The fritzing file "MetroVariantTest.fzz", shows roughly (I used cables instead of FTDI modules) how I connected to the Metro M0 to test the new ports.

I will be adding code (Arduino) later that supports the test.

I chose the two I2C devices simply based on what was lying on my bench at the moment, so there's nothing special about them.

For this variant:
Serial0 is on D11 (txd) and D13 (rxd)
Serial1 is on D1 (txd) and D0 (rxd) (default config)
Serial2 is on D6 (txd) and D7 (rxd) 
Wire uses SCL and SDA (by default, obviously)
Wire1 is on D4 (SDA) and D3 (SCL)