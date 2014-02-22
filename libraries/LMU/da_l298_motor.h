/*
 This library provides the core organizational classes of the LocoMotionUnit 
 for Arduino based platforms.
 
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

#ifndef da_l298_motor_h
#define da_l298_motor_h

/******************************************************************************
 * Includes
 ******************************************************************************/
#include "Arduino.h"
#include "da_types.h"
#include "da_motor_driver.h"

class da_l298_motor: public da_motor_driver {
private:
	byte enablePin;
	byte pin0;
	byte pin1;
public:
	da_l298_motor(
		byte en, 
		byte p0, 
		byte p1,
		uint mask = 0xFFFF): da_motor_driver(mask), enablePin(en), pin0(p0), pin1(p1) {
			pinMode(enablePin, OUTPUT);
			pinMode(pin0, OUTPUT);
			pinMode(pin1, OUTPUT);
	}
	
	void On(void) { analogWrite(enablePin, throttle); }
	void Off(void) { analogWrite(enablePin, 0); }
	void SetVector(uint amount, enum LMUMovement movement);
	void Init(void) { }
};

#endif