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


#ifndef Seeprom_h
#define Seeprom_h

#include "Arduino.h"
#include "Wire.h"

class Seeprom
{
   public:
      Seeprom(byte devaddr);
      void writeByte(int epaddr, byte data);
      void writePage(int epaddr, const byte * data, byte length);
      int readByte(int epaddr);
      int readBuffer(int epaddr, byte * buffer, byte length);
      void dump(int epaddr, unsigned length);
   private:
      byte _devaddr;
};

#endif