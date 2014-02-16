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

#ifndef da_motor_driver_h
#define da_motor_driver_h

/******************************************************************************
 * Includes
 ******************************************************************************/
#include "da_types.h"

/* Name: enum TravelDirection
 * linear travel directions */
enum TravelDirection {
	LMU_FORWARD,
	LMU_REVERSE
};

/* 
* Name: enum RotationOrientation
* This sets the way the motor turns in order to progress linearly forward */
enum RotationOrientation {
	LMU_CW,
	LMU_CCW,
	LMU_BRAKE,
};

class da_motor_driver {
private:
	uint trim;
protected:
	uint throttle;
	uint throttleMask;
	enum RotationOrientation spinOrientation;
public:
	da_motor_driver(uint mask): throttle(0), trim(0), spinOrientation(LMU_BRAKE), throttleMask(mask) { }
	
	virtual void On(void) = 0;
	virtual void Off(void) = 0;
	virtual void SetVector(uint, enum RotationOrientation) = 0;

	/* trim should not be more than half the mask value */
	void SetTrim(uint value) { trim = value & (throttleMask >> 1); }
	uint GetTrim(void) { return trim; }
	uint GetThrottle(void) { return throttle; }
	enum RotationOrientation GetRotation(void) { return spinOrientation; }
};

#endif