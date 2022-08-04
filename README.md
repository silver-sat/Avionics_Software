# Avionics_Software
SilverSat Avionics board code base, including software for team meeting discussions

## Mock Hardware Drivers

The AvionicsTesting1 folder contains mock hardware drivers for the components on the Avionics Board. These drivers act as simulated and simplified interfaces for the hardware on the board. 

You can install these libraries by cloning the repository using git or by downloading a zip file containing the libraries and extracting the folders. Copy the desired libraries into your Ardunio/libraries folder.

The interfaces to the mock hardware are designed to be similar to those planned for the flight software. You can write tests and application software in anticipation of using very similar driver interfaces for the actual hardware.

Each library contains an example using the interface to access the mock device. The repository also includes a sketch that exercises each of the mock interfaces.

## Hardware Unit Test Drivers

The AvionicsTesting2 folder contains hardware test drivers for the components on the Avionics Board. These drivers can be used to verify and exercise the hardware devices on the board.

You can install these drivers by cloning the repository using git or by downloading a zip file containing the drivers and extracting the sketches.

You can exercise individual hardware components by building the related sketch (e.g. test_imu) and uploading it to the Avonics Board. Note that some external libraries are required, for example to support the MPU6050 hardware. Install these libraries following the normal Ardunino procedure.

You can execute all of the hardware tests in sequence using a bash script provided in the AvionicsTesting2 folder. This script requires the Arduino CLI, which can be installed from the Arduino.cc web site. To execute all of the hardware unit tests, insure the script is executable, connect a serial monitor to the appropriate port, open a terminal window, and execute the script. Follow the prompts and observe the results in the serial monitor.

## Test Process Loop

The AvionicsTesting3 folder contains test drivers for the functions of the Avionics Board. These drivers can be used to verify and exercise the functions of the board such as device setup, telemetry collection, beacon transmission, and command processing.

The test process loop is the main process loop to test the SilverSat Avionics Board.
 
The hardware devices on the Avionics Board are implemented as classes interfacing to real hardware. The other SilverSat boards: Power, Radio, and Payload are implemented as mock devices in software for these tests. Each mock board performs a subset of the functionality provided by the actual board, as needed to test the Avionics Board.

The beacon message which Avionics sends to the Radio Board, the command messages the Radio
Board sends to Avionics, and the messages Avionics sends to the Radio Board are also represented as classes.

To execute this test, clone the respository to your machine or download a zip file and extract the folders. Upload the test_process_loop.ino file to your microcontroller.

You can then use the serial port to send commands to the Avionics Board using the Arduino IDE Serial Monitor, the VS Code Arduino extension Serial Monitor, a terminal emulator such as tio, or a Python program. A sample Python program is provided. The Avionics test software sends log data, messages, and beacons to the serial port.
