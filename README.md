# Arduino RFID Keyboard
Simple program to output RFID tag's UUID as keyboard output. :crystal_ball:

## How to use it

#### 1) Set up the circuit so as the [schematic](https://github.com/brunnotelma/arduino-rfid-keyboard/blob/master/schematic.png) shows.
#### 2) Upload source code to Arduino Pro Micro.
#### 3) Enjoy!

## IMPORTANT NOTE
If you are using _Arduino Pro Micro_ **3.3v** version, you don't need to use
the **three 1k ohms resistors** to make the [Voltage Divider](https://github.com/brunnotelma/arduino-rfid-keyboard/blob/master/voltage_divider_circuit.png) circuit. 
This is just needed because the MFRC22 takes **3.3v** as input voltage.

#

_Use wisely._ :squirrel: