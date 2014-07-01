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

#ifndef da_l9110_motor_h
#define da_l9110_motor_h

/******************************************************************************
 * Includes
 ******************************************************************************/
#include "Arduino.h"
#include "da_types.h"
#include "da_motor_driver.h"

class da_l9110_motor: public da_motor_driver {
private:
	byte pin0;
	byte pin1;
public:
	da_l9110_motor(
		byte p0, 
		byte p1,
		uint mask = 0xFF): da_motor_driver(mask), pin0(p0), pin1(p1) {}
	
	void On(void) {  }
	void Off(void) { analogWrite(pin0, 0); analogWrite(pin1, 0); }
	void SetVector(uint amount, enum LMUMovement movement);
	void Init(void) { }
};

#endif