/*
  Seeprom.h - small EEPROM library for Arduino.
  Created by Nicola Piovesan, September 2013. 
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
  Released into the public domain.
*/
  
#include <Arduino.h>
#include "Seeprom.h"
#include <Wire.h>

Seeprom::Seeprom(byte devaddr, unsigned length)
{
  _devaddr = devaddr;
  _length = length;
  Wire.begin();
}

void Seeprom::writeByte(int epaddr, byte data)
{
    byte devaddr = _devaddr | ((epaddr >> 8) & 0x07);
    Wire.beginTransmission(devaddr);
    Wire.write(epaddr);
    Wire.write(int(data));
    Wire.endTransmission();
    delay(10);
}

void Seeprom::writePage(int epaddr, const byte * data, byte length)
{
    byte devaddr = _devaddr | ((epaddr >> 8) & 0x07);
    Wire.beginTransmission(devaddr);
    Wire.write(epaddr);
    for (int i = 0; i < length; i++) {
        Wire.write(data[i]);
    }
    Wire.endTransmission();
    delay(10);
}

int Seeprom::readByte(int epaddr)
{
    byte rdata = -1;
    byte devaddr = _devaddr | ((epaddr >> 8) & 0x07);
    Wire.beginTransmission(devaddr);
    Wire.write(epaddr);
    Wire.endTransmission();
    Wire.requestFrom(int(devaddr), 1);
    if (Wire.available()) {
        rdata = Wire.read();
    }
    return rdata;
}

int Seeprom::readBuffer(int epaddr, byte * buffer, byte length)
{
    byte devaddr = _devaddr | ((epaddr >> 8) & 0x07);
    Wire.beginTransmission(devaddr);
    Wire.write(epaddr);
    Wire.endTransmission();
    Wire.requestFrom(devaddr, length);
    int i;
    for (i = 0; i < length && Wire.available(); i++) {
        buffer[i] = Wire.read();
    }
    return i;
}

void Seeprom::dump(int epaddr)
{
    int startaddr = epaddr & (~0x0f);
    int stopaddr  = (epaddr + _length + 0x0f) & (~0x0f);

    for (int i = startaddr; i < stopaddr; i += 16) {
        byte buffer[16];
        char outbuf[6]; 
        sprintf(outbuf, "%03x: ", i);
        Serial.print(outbuf);
        readBuffer(i, buffer, 16);
        for (int j = 0; j < 16; j++) {
            if (j == 8) {
                Serial.print(" ");
            }
            sprintf(outbuf, "%02x ", buffer[j]);
            Serial.print(outbuf);            
        }
        Serial.print(" |");
        for (int j = 0; j < 16; j++) {
            if (isprint(buffer[j])) {
                Serial.print(buffer[j]);
            }
            else {
                Serial.print('.');
            }
        }
        Serial.println("|");
    }
}

void Seeprom::writeInt(int epaddr, int int16){
    byte data[2];
    data[0] = (byte) (int16 & 0xFF);
    data[1] = (byte) ((int16 >> 8) & 0xFF);
    writePage(epaddr, data, 2);
}

int Seeprom::readInt(int epaddr){
    byte buffer[2];
    int val;
    readBuffer(0, buffer, 2);
    
    val=buffer[1];
    val=((val << 8) | buffer[0]);
    return val;
}

void Seeprom::clearPage(int epaddr){
    byte buffer[16] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    writePage(epaddr, buffer, 16);
}

void Seeprom::clearAll(){
    int startaddr = 0xff;
    int stopaddr  = (startaddr + _length + 0x0f) & (~0x0f);

    for (int i = startaddr; i < stopaddr; i += 16) {
        clearPage(i);
        }
}