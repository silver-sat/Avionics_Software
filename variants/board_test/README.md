This folder contains the variant.cpp and variant.h files for the SilverSat Avionics Board. 

To build Arduino sketches for the Avionics Board, git clone or download a .zip file containing these files to your development computer. 
Create a hardware folder in your Arduino sketch folder as documented 
at https://arduino.github.io/arduino-cli/0.21/platform-specification/#hardware-folders-structure, copying the Adafruit Metro M0 Express
files as the hardware configuration template.

Rename the appropriate folders and make the necessary changes to boards.txt in the new folder structure. Copy variant.cpp and variant.h
into that folder structure, replacing the Metro M0 Express files with the same names.

As an example, on Ubuntu, create a "hardware" folder in your "Arduino" folder. Create an "avionics" folder in "hardware."
Copy the "samd/[version]" folder containing the Metro M0 definitions located at ".arduino15/packages/adafruit/hardware/samd/[version]" to 
your new "hardware" folder and rename it to "samd." (That is, drop the version level of the folder structure.) Rename the "metro_m0" folder in the 
"variants" folder and edit "boards.txt" to reflect the new name. Replace "variant.cpp" and "variant.h" in the renamed folder with the
downloaded files.

If you do not have the Metro M0 Express definitions on your development computer, you can download them using the procedure
documented at https://learn.adafruit.com/adafruit-metro-m0-express/arduino-ide-setup.

After you have setup the definitions for the Avionics Board, open your development environment, select the new board configuration, 
build your sketch, and upload it to the Avionics Board.