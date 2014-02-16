




/*
 Copyright (C) 2013 Joshua Frkuska  DigitalArtisans.Org

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include <MemoryFree.h>
#include <Wire.h>
#include <ModbusSlave.h>


#include <da_l298_motor.h>

#define M0_EN_PIN 10
#define M0_P0_PIN 12
#define M0_P1_PIN 13

da_l298_motor motor(M0_EN_PIN, M0_P0_PIN, M0_P1_PIN);

void setup() 
{
  Serial.print("freeMemory()=");
  Serial.println(freeMemory());
}

void loop()
{
}

