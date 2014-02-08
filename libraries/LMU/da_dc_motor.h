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

#ifndef da_dc_motor_h
#define da_dc_motor_h

/******************************************************************************
 * Includes
 ******************************************************************************/
#include "Arduino.h"
#include "da_types.h"
#include "da_motor.h"

class da_dc_motor: public da_motor {
private:
	uchar enable_pin;
	uchar pin0;
	uchar pin1;
public:
	da_dc_motor(enum forward_rotation rot,
		uchar tmax,
		uchar en, 
		uchar p0, 
		uchar p1): da_motor(rot, tmax), enable_pin(en), pin0(p0), pin1(p1) {
			pinMode(enable_pin, OUTPUT);
			pinMode(pin0, OUTPUT);
			pinMode(pin1, OUTPUT);
		}
	int setVector(uchar, enum travel_direction);
};

#endif