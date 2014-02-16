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

/* 
* Name: enum forward_rotation
* This sets the way the motor turns in order to progress linearly forward */
enum MotorRotation {
	MTR_CW,
	MTR_CCW,
	MTR_BRAKE,
};

class da_motor_driver {
private:
	uint trim;
	enum MotorRotation spinOrientation;
protected:
	uint throttle;
	uint throttleMask;
public:
	da_motor_driver(uint mask): throttle(0), trim(0), spinOrientation(MTR_BRAKE), throttleMask(mask) { }
	
	virtual void On(void) = 0;
	virtual void Off(void) = 0;
	virtual void SetThrottle(uint) = 0;

	/* trim should not be more than half the mask value */
	void SetTrim(uint value) { trim = value & (throttleMask >> 1); }
	uint GetTrim(void) { return trim; }
	uint GetThrottle(void) { return throttle; }
	enum MotorRotation GetRotation(void) { return spinOrientation; }
	void SetRotation(enum MotorRotation spin) { spinOrientation = spin; }
};

#endif