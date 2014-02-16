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
#include "da_rover_lmu.h"

void da_rover_lmu::Rotate(uint throttle, enum RotationOrientation rot) 
{
	int i;
	
	for (i = 0; i < wheelCount[LMU_ROVER_LEFT]; i++) {
		if (LMU_CW == rot)
			wheels[LMU_ROVER_LEFT][i].setVector(throttle, LMU_FORWARD);
		else
			wheels[LMU_ROVER_LEFT][i].setVector(throttle, LMU_REVERSE);
	}
	for (i = 0; i < wheelCount[LMU_ROVER_RIGHT]; i++) {
		if (LMU_CW == rot)
			wheels[LMU_ROVER_RIGHT][i].setVector(throttle, LMU_REVERSE);
		else
			wheels[LMU_ROVER_RIGHT][i].setVector(throttle, LMU_FORWARD);
	}
}

void da_rover_lmu::Travel(uint throttle, enum TravelDirection dir)
{
	int i;
	
	for (i = 0; i < wheelCount[LMU_ROVER_LEFT]; i++)
			wheels[LMU_ROVER_LEFT][i].setVector(throttle, dir);
	for (i = 0; i < wheelCount[LMU_ROVER_RIGHT]; i++)
			wheels[LMU_ROVER_RIGHT][i].setVector(throttle, dir);
}
 