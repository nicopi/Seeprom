# Seeprom library
**Seeprom** is an Arduino library for interfacing to small electrically erasable programmable read-only memories (e.g. the 24Cxx series) on the I2C bus.

***
### How to connect the EEPROM to the Arduino board

The EEPROM must be connected to Arduino by considering the following configuration.
|EEPROM|Arduino|
|------|-------|
|pin 1 [GND] | GND |
|pin 2 [Vcc] | 5v |
|pin 3 [SDA] | Analog pin 4 |
|pin 4 [SCL] | Analog pin 5 |
|pin 5 [WP]  | GND (to not hardware protect data) |
|pin 6 [A0]  | GND |
|pin 7 [A1]  | GND |
|pin 8 [A2]  | GND |

## List of methods
* `Seeprom(byte devaddr, unsigned length)`
* `void writeByte(int epaddr, byte data)`
* `void writePage(int epaddr, const byte * data, byte length)`
* `int readByte(int epaddr)`
* `int readBuffer(int epaddr, byte * buffer, byte length)`
* `void dump(int epaddr)`
* `void writeInt(int epaddr, int int16)`
* `int readInt(int epaddr)`
* `void writeLong(int epaddr, long long32)`
* `long readLong(int epaddr)`
* `void clearPage(int epaddr)`
* `void clearAll()`

## Example
```
#include <Seeprom.h>

const byte DEVADDR = 0x50; //Address of the EEPROM
Seeprom eeprom(DEVADDR, 2048); //create the eeprom object

value = eeprom.readInt(0); //Read integer from EEPROM at address 0x00
eeprom.writeInt(0,value+2); //Write integer value+2 at the same address
```
