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

#ifdef da_debug_motor
#define DA_DEBUG_MTR(X) DA_DEBUG(X)
#define DA_DEBUG_MTR2(X,Y) DA_DEBUG2(X,Y)
#define DA_DEBUG_MTR_F(X,Y) DA_DEBUG_F(X,Y)
#else
#define DA_DEBUG_MTR(X)
#define DA_DEBUG_MTR_F(X,Y)
#define DA_DEBUG_MTR2(X,Y)
#endif


/******************************************************************************
 * Includes
 ******************************************************************************/
#include "da_types.h"
#include "da_device.h"

class da_motor_driver: public da_device {
private:
	uint trim;
protected:
	uint throttle;
	uint throttleMask;
	enum LMUMovement spinOrientation;
public:
	da_motor_driver(uint mask): throttle(0), trim(0), spinOrientation(LMU_STOP), throttleMask(mask) { }
	
	virtual void On(void) = 0;
	virtual void Off(void) = 0;
	virtual void SetVector(uint, enum LMUMovement) = 0;
	virtual void Connect(void) { }
	virtual void Disconnect(void) { }

	/* trim should not be more than half the mask value */
	void SetTrim(int value) { trim = value; }
	int GetTrim(void) { return trim; }
	uint GetThrottle(void) { return throttle; }
	enum LMUMovement GetRotation(void) { return spinOrientation; }
};

#endif