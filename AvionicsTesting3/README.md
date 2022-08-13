# Test Process Loop

The AvionicsTesting3 folder contains test drivers for the functions of the Avionics Board. These drivers can be used to verify and exercise the functions of the board such as device setup, telemetry collection, beacon transmission, and command processing.

The test process loop is the main process loop to test the SilverSat Avionics Board.
 
The hardware devices on the Avionics Board are implemented as classes interfacing to real hardware. The other SilverSat boards: Power, Radio, and Payload are implemented as mock devices in software for these tests. Each mock board performs a subset of the functionality provided by the actual board, as needed to test the Avionics Board.

The beacon message which Avionics sends to the Radio Board, the command messages the Radio
Board sends to Avionics, and the messages Avionics sends to the Radio Board are also represented as classes.

To execute this test, clone the respository to your machine or download a zip file and extract the folders. Connect the watchdog, realtime clock, the inertial measurement unit, and the FRAM. Upload the test_process_loop.ino file to your microcontroller.

You can then use the serial port to send commands to the Avionics Board using the Arduino IDE Serial Monitor, the VS Code Arduino extension Serial Monitor, a terminal emulator such as tio, or a Python program. A sample Python program is provided. The Avionics test software sends log data, messages, and beacons to the serial port.

A set of python unit test progams that can be run in a terminal session or invoked via pytest are in the directory.
