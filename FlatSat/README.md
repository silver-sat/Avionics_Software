## Avionics Loop
The "FlatSat" folder contains the Avionics Board software for testing and operating the FlatSat configuration. 
This includes the process loop, hardware drivers, command processor, and interface software for the power, radio, and payload boards.

### Test Drivers
The "FlatSat" folder contains drivers for testing
the serial interface with the Radio Board in the "test_avionics" folder. These drivers can be used to test each of the local command implementations that require communication between the Avionics Board and the Radio Board, such as getting radio status and changing radio settings. The test drivers can be used to test the beacon functions and the halt function.

The FlatSat folder also contains
unit test drivers for the command functions of the Avionics Board in the "test_avionics" folder. These drivers can be used to verify and exercise the functions of the Avionics board such as setting the realtime clock, telemetry collection, controlling beacon transmission, and triggering the watchdog.

Also in the "test_avionics" folder are drivers to test the interface with the Payload Board, Power Board, and Antenna. These drivers are augmented by simulators in the "payload_simulator", "eps_simulator", and "antenna_simulator" folders, which contain Python programs suitable for execution on an Adafruit Metro M0 (payload) and Adafruit Grand Central (eps and antenna). When appropriately connected, these simulators respond to the interfaces similarly to the actual devices, thus allowing testing without the entire Flatsat configuration. The folders also include simple programs for testing the simulators.

### Software
The "avionics_loop.ino" sketch is the main process loop for testing and operating the Avionics Board. In avionics_loop, the hardware devices on the Avionics Board are implemented as classes interfacing to real hardware. The other SilverSat boards: Power, Radio, and Payload, are implemented as classes which interface with those boards. 

The local messages which Avionics sends to the Radio Board, the ground commands the Radio Board forwards to Avionics, and the responses Avionics sends to the Radio Board for forwarding to the ground are also represented as classes.

The Avionics Board connects to the Radio Board via the Serial1 interface. It connects to the realtime clock via the critical I2C connection. The Avionics Board connects to the IMU, the FRAM, the antenna, and the Power Board via a second I2C connection. Accessing the antenna and the Power Board require activation of an I2C switch. The Avionics Board connects to the Payload Board via digital IO lines.

### Libraries
The "FlatSat" folder includes an interface to the Arduino log library, which can be used to log status information on the Radio Board Serial interface. Adafruit libaries are used to support the I2C devices, the MPU6050, the FRAM, the real time clock,  The Arduino Crypto library is used to support command signing.

### Setup
Signed commands require that the Avionics Board and the ground share a secret. This secret is defined as a sixteen-byte array. 

Following the Arduino convention, an "arduino_secrets.h" file is required to store the secret. It must ```#define``` a sixteen-byte array named ```SECRET_HASH_KEY```, which is compiled into the sketch. DO NOT upload "arduino_secrets.h" to github or other shared locations. The software used to generate signed commands must use an identical sixteen-byte secret. For these tests, the secret is stored in "secret.txt". DO NOT upload "secret.txt" to github. The "test_signing" folder located in the "AvionicsTesting3" folder in this repository includes a Python program, "make_secret.py", which can be used to generate shared secrets. If the secrets use by the Avionics Board and the test programs or ground software are not identical, command signing will fail.

To setup a test environment, clone this repository to your computer or download a .zip file and extract the folders. Generate a secret and create an "arduino_secrets.h" file and a "secret.txt" file to store it. Add both to your ```.gitignore``` to prevent them from being uploaded to github. Install the Adafruit MPU6050 and FRAM libraries with dependencies using the Arduino Library Manager. Install the ArduinoLog and Arduino Crypto libraries by downloading and copying them into your library folder. Compile and upload the "avionics_loop.ino" sketch to the Avionics Board microcontroller using the standard Arduino tools or alternative deployment tools.

The "avionics_loop.ino" sketch has extensive logging capabilities based on the ArduinoLog utility (https://github.com/thijse/Arduino-Log/). The log level can be changed by modifying the "log.begin" method call in the "avionics_loop.ino" file. 

The "avionics_loop.ino" file has instrumentation for tracking processing time and memory usage that is enabled by ```#define INSTRUMENTATION```. The log utility is used to display the instrumentation data.

The "avionics_loop" sketch receives commands and sends messages and local commands to and from the Radion Board via the "Serial1" port. It sends log data to the "Serial" port. After uploading your sketch, verify that the Avionics Board has initialized properly by opening a terminal connection to the "Serial" port and reviewing the log entries. Terminal emulators known to work include the Arduino IDE Serial Monitor, the VS Code Arduino extension Serial Monitor, and the tio terminal emulator. (```tio -m INLCRNL [portname]```). If you are using a bootloader, be aware that use of
a serial monitor can interfere with uploading. If you aren't using the Arduino toolset, disconnect your serial monitor software before using the bootloader.

### Testing

You can use the "Serial1" port to send commands to the Avionics Board and observe the responses. The commands must be KISS formatted. Since commands in general use utf-8 single-byte printable characters, commands can typically be generated by adding FEND [0xC0] at the front and end of the command. The first FEND must be following by the appropriate command byte as defined in https://docs.google.com/document/d/1Vwpk0ab0HoC62mU7A1fQwpmhmtmZO0VwPtXjQipe0v0/edit?usp=sharing. Be aware that the command bytes are not printable characters.

The Avionics Board implements the KISS escape processing protocol, although it is not currently in use.

The "FlatSat/test_avionics" folder includes python programs for unit testing each of the Avionics Board commands and for interfacing to the rest of the satellite. These programs are designed to be managed and executed using pytest. After resetting the microcontroller you may run the entire suite of tests by entering ```pytest``` on the command line while in the "FlatSat/test_avionics" directory. (Depending on your configuration, ```python3 -m pytest``` may be required.) 

pytest also allows selective execution of tests. See https://docs.pytest.org/ for additional information. Be sure to run the ```test_00_avionics_initialization.py``` test first any time the microcontroller is restarted to process the initialization messages. You can also review the startup messages in a serial monitor and then end the serial monitor session before running automated tests. To test signed commands, the "secret.txt" file must include the same secret as the "arduino_secrets.h" file used to build "avionics_loop.ino." The "utility.py" program in "avionics_test" contains functions to issue commands and to generate signed commands. 

You can observe traffic on the Serial1 port using a USB adaptor device and tio. ```tio -x [portname]``` will display the traffice as hex bytes. Note that this will interfere with the automated tests, so should only be used when manually entering commands on the (separate) Serial port. It may also be useful to open terminals showing output from the payload simulator and the eps/antenna simulator.

### Documentation

The SilverSat Avionics Board document in the repository provides an overview of the Avionics Board hardware, software and commands.

Documentation for the software and tests can be viewed by running doxygen (https://doxygen.nl/) using the provided Doxyfile and then opening docs/index.html in a browser. Modifications to the Doxyfile may be required to reflect your directory structure.

