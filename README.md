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

The AvionicsTesting3 folder contains unit test drivers for the command functions of the Avionics Board. These drivers can be used to verify and exercise the functions of the board such as setting the realtime clock, telemetry collection, controlling beacon transmission, triggering the simulated Watchdog, and starting a Twitter session on the mock Payload Board.

The test_process_loop.ino in the test_process_loop sketch is the main process loop for testing the SilverSat Avionics Board. The other sketches are used to support development of the test loop. test_process_loop has extensive logging capabilities based on the ArduinoLog utility (https://github.com/thijse/Arduino-Log/). The log level can be changed by modifying the log.begin method call in the test_process_loop.ino file.
 
The hardware devices on the Avionics Board are implemented as classes interfacing to real hardware. The other SilverSat boards: Power, Radio, and Payload, are implemented as mock devices in software for these tests. Each mock board performs a subset of the functionality provided by the actual board as needed to test the Avionics Board.

The beacon which Avionics sends to the Radio Board, the commands the Radio
Board sends to Avionics, and the messages Avionics sends to the Radio Board are also represented as classes.

To setup a test environment, clone this respository to your computer or download a zip file and extract the folders. Compile and upload the test_process_loop sketch to the Avionics Board microcontroller using the standard Arduino tools or alternative deployment tools.

The test_process_loop sketch sends log data, messages, and beacons to the serial port. Verify that the Avionics Board has initialized properly by opening a terminal connection to the microcontroller and reviewing the log entries. Terminal emulators known to work include the Arduino IDE Serial Monitor, the VS Code Arduino extension Serial Monitor, and the tio terminal emulator. 

You can then use the serial port to send commands to the Avionics Board and observe the responses. Note that the microcontroller does not echo keystrokes. You may also close the serial connection and launch a Python program which communicates through the serial interface. A sample Python program, example.py, is provided. Attempting to use the terminal and a program simultaneously will result in errors.

The AvionicsTesting3 folder includes python programs for unit testing each of the Avionics Board commands. These programs are designed to be managed and executed using pytest. After verifying the microcontroller has initialized properly, you may run the entire suite of command unit tests by entering ```pytest``` on the command line while in the AvionicsTesting3 directory. pytest also allows selective execution of tests. See https://docs.pytest.org/ for additional information. 

Documentation for the software and tests can be viewed by opening docs/index.html in a browser.

