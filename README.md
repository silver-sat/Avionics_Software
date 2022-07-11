# Avionics_Software
SilverSat Avionics board code base, including software for team meeting discussions

## Mock Hardware Drivers

The AvionicsTesting1 folder contains mock hardware drivers for the components on the Avionics Board. These drivers act as simulated and simplified interfaces for the hardware on the board. 

You can install these libraries by cloning the repository using git or by downloading a zip file containing the libraries and extracting the folders. Copy the desired libraries into your Ardunio/libraries folder.

The interfaces to the mock hardware are designed to be similar to those planned for the flight software. You can write tests and application software in anticipation of using very similar driver interfaces for the actual hardware.

Each library contains an example using the interface to access the mock device. The repository also includes a sketch that exercises each of the mock interfaces.
