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

/******************************************************************************
 * Includes
 ******************************************************************************/
#include "Arduino.h"
#include "da_wheel.h"

void da_wheel::setVector(uint value, enum LMUMovement dir) {
	
	direction = dir;
	enum LMUMovement reverseRotation = 
			forwardRotation == LMU_CW ? LMU_CCW : LMU_CW;
	
	DA_DEBUG_MTR("SetVector (");
	DA_DEBUG_MTR2(value, HEX);
	DA_DEBUG_MTR(", ");
	DA_DEBUG_MTR2(dir, HEX);
	DA_DEBUG_MTR(")\n");
		
	if (direction == LMU_FORWARD)
		driver.SetVector(value, forwardRotation);
	else
		driver.SetVector(value, reverseRotation);

}