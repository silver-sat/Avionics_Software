## Test Process Loop
The AvionicsTesting3 folder contains unit test drivers for the command functions of the SilverSat Avionics Board. These drivers can be used to verify and exercise the functions of the board such as setting the realtime clock, telemetry collection, controlling beacon transmission, triggering the watchdog, and starting a Twitter session on the mock Payload Board.

The test_process_loop sketch is the main process loop for testing the Avionics Board. Software in the other subfolders is used to support development and testing of the test loop. In test_process_loop, the hardware devices on the Avionics Board are implemented as classes interfacing to real hardware. The other SilverSat boards: Power, Radio, and Payload, are implemented as mock devices in software for these tests. Each mock board performs a subset of the functionality provided by the actual board as needed to test the Avionics Board.

The beacon and other local commands which Avionics sends to the Radio Board, the ground commands the Radio Board forwards to Avionics, and the messages Avionics sends to the Radio Board for forwarding to the ground are also represented as classes.

### Setup
An "arduino_secrets.h" file is required to store the secret shared with the ground station for command signing. It must ```#define``` a sixteen-byte array named ```SECRET_HASH_KEY```, which is compiled into the sketch. DO NOT upload "arduino_secrets.h" to github. The software used to generate signed commands must use an identical sixteen-byte secret. For these tests, the secret is stored in "secret.txt". DO NOT upload "secret.txt" to github. The test_signing folder includes a Python program, "make_secret.py", which can be used to generate shared secrets. If the secrets are not identical, command signing will fail.

To setup a test environment, clone this repository to your computer or download a .zip file and extract the folders. Generate a secret and create an "arduino_secrets.h" file and a "secret.txt" file to store it. Add both to your ```.gitignore``` to prevent them from being uploaded to github. Install the Adafruit MPU6050 and FRAM libraries with dependencies using the Arduino Library Manager. Install the ArduinoLog and Arduino Crypto libraries by downloading and copying them into your library folder. Compile and upload the test_process_loop sketch to the Avionics Board microcontroller using the standard Arduino tools or alternative deployment tools.

The test_process_loop sketch has extensive logging capabilities based on the ArduinoLog utility (https://github.com/thijse/Arduino-Log/). The log level can be changed by modifying the log.begin method call in the "test_process_loop.ino" file. The "test_process_loop.ino" file has instrumentation for tracking processing time and memory usage that is enabled by ```#define INSTRUMENTATION```.

The test_process_loop sketch receives commands and sends messages and local commands via the "Serial1" port. It sends log data to the "Serial" port. After uploading your sketch, verify that the Avionics Board has initialized properly by opening a terminal connection to the "Serial" port and reviewing the log entries. Terminal emulators known to work include the Arduino IDE Serial Monitor, the VS Code Arduino extension Serial Monitor, and the tio terminal emulator. (```tio -b 115200 -m INLCRNL,ONLCRNL [portname]```). If you are using a bootloader, be aware that use of
a serial monitor can interfere with uploading. If you aren't using the Arduino toolset, stop your serial monitor before using the bootloader.

### Testing

You can use the "Serial1" port to send commands to the Avionics Board and observe the responses. The commands must have AX.25 message headers and be KISS formatted. The DireWolf (https://github.com/wb2osz/direwolf) "kissutil" program does this formatting and is useful for entering commands manually. For example, you can launch kisstutil and type ```S>D:NoOperate``` at the prompt to send a NoOperate command to the Avionics Board. 

kissutil can also send messages stored in a file. Sample unsigned and signed command files are provided in the "test_ax25/source" folder. The signed commands are examples and do not incorporate your shared secret--they will not work with your compiled test_process_loop. 
You will need to replace the example signed commands with commands generated using your shared secret for command validation to succeed. The test_signing folder includes a Python program, "sign_command.py", which can be used to generate signed commands. The "secret.txt" file must contain the same secret as the "arduino_secrets.h" file compiled into your test_process_loop sketch. Signed commands require a sequence number which can be specified as a parameter to the program.

You can then launch kissutil, specifying the ```-f``` option for the "test_ax25/active" directory, and then copy commands from the "test_ax25/source" directory to the "test_ax25/active" directory to transmit them. Command files are deleted from the "test_ax25/active" folder after transmission. 

The AvionicsTesting3/test_commands folder includes python programs for unit testing each of the Avionics Board commands. These programs are designed to be managed and executed using pytest. After resetting the microcontroller you may run the entire suite of command unit tests by entering ```pytest``` on the command line while in the AvionicsTesting3 directory. pytest also allows selective execution of tests. See https://docs.pytest.org/ for additional information. Be sure to run the ```test_avionics_initialization.py``` test first any time the microcontroller is restarted to process the initialization messages. You can also review the startup messages in a terminal and then end the terminal session before running automated tests. To test signed commands, the "secret.txt" file must include the same secret as "arduino_secrets.h."

### Documentation

Documentation for the software and tests can be viewed by running doxygen (https://doxygen.nl/) using the provided Doxyfile and then opening docs/index.html in a browser. Modifications to the Doxyfile may be required to reflect your directory structure.

