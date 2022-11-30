# Avionics_Software
This is the SilverSat Avionics board test code base, including software for team meeting discussions.

The Avionics Board shares many characteristics with the 
Adafruit Metro M0 Express and in general testing can be performed on either board. However, the standard Arduino Metro M0 Express configuration has fewer serial ports and 
fewer I2C buses than the Avionics Board. Also, serial ports, I2C devices, and digital IO ports 
have different pin locations on the boards. The variants folder in this repository has instructions and configuration files for setting up Metro M0 Express boards with additional serial ports and I2C buses and for setting up the Avionics Board hardware.

## Mock Hardware Drivers
The AvionicsTesting1 folder contains mock hardware drivers for the components on the Avionics Board. These drivers act as simulated and simplified interfaces for the hardware on the board. They are configured as Arduino libraries.

You can install these libraries by cloning the repository using git or by downloading a .zip file containing the libraries and extracting the folders. Copy the desired libraries into your Ardunio libraries folder.

The interfaces to the mock hardware are designed to be similar to those planned for the flight hardware and software. You can write tests and application software with the expectation of using similar driver interfaces for the flight implementation.

Each library contains an example using the interface to access the mock device. The repository also includes a sketch that exercises each of the mock interfaces.

## Hardware Unit Test Drivers
The AvionicsTesting2 folder contains test drivers for the hardware components on the Avionics Board. These drivers can be used to verify and exercise the actual devices attached to a Metro M0 or on the board.

You can install these drivers by cloning the repository using git or by downloading a .zip file containing the drivers and extracting the sketches. Follow the instructions in the variants folder to setup the right pin configurations for your environment. If you are using the Avionics Board hardware, define ```CRYSTALLESS``` in the appropriate Arduino core ```startup.c``` file. (The Avionics Board does not have a crystal.) 

You can exercise individual hardware components by building the related sketch (e.g. ```test_imu```) and uploading it to a Metro M0 or the Avionics Board. Note that some external libraries are required, for example to support the MPU6050 hardware. A full list of libraries is in the AvionicsTesting3 folder ```README.md```. Install required libraries following the normal Arduino procedure.

You can execute all of the hardware tests in sequence using a bash script provided in the AvionicsTesting2 folder. This script requires the Arduino CLI, which can be installed following the instructions at https://arduino.github.io/arduino-cli/0.21/installation/. Make the script executable, connect a serial monitor to the appropriate port on the target board, open a terminal window on your development computer, 
and execute the script. Follow the prompts and observe the results in the serial monitor.

## Test Process Loop
The AvionicsTesting3 folder ```README.md``` describes the board testing capabilites of the test_process_loop software and provides test setup instructions. The test_process_loop sketch in the folder implements the initialization, watchdog management, beacon transmission, command processing, and payload management functions for the Avionics Board.
