#Seeprom library#
**Seeprom** is an Arduino library to use small EEPROM like 24Cxx on the I2C bus.

***
###How to connect the EEPROM to the Arduino board###
You can use this configuration:

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
