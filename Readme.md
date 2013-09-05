#sEEPROM library
sEEPROM is an Arduino library to use small EEPROM like 24Cxx on the I2C bus.

##How to connect the EEPROM to the Arduino board
You can use this configuration:
EEPROM pin 1 [GND] - GND
EEPROM pin 2 [Vcc] - 5v
EEPROM pin 3 [SDA] - Analog pin 4
EEPROM pin 4 [SCL] - Analog pin 5
EEPROM pin 5 [WP] - GND (to not hardware protect data)
EEPROM pin 6 [A0] - GND
EEPROM pin 7 [A1] - GND
EEPROM pin 8 [A2] - GND
---