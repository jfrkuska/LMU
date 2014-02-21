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

void da_rover_lmu::Calibrate(void)
{
	DA_DEBUG_MTR("Calibrating");

	/* wait CALIBRATE_DELAY seconds */
	delay(CALIBRATE_DELAY);
	
	/* calibrate motion sensor */
	
	/* roll forward and adjust trim */
	
	/* roll backwards and calibrate sensors */
	
	/* rotate 180 degrees */
}

void da_rover_lmu::Init(void) {
	
	int i;
	
	DA_DEBUG_MTR("ROVER LMU INIT");
	
	/* Init all feedback sensors */
	for (i = 0; i < fbSensorCount; i++)
		fbSensors[i].Init();
	
	/* Init all wheels */	
	for (i = 0; i < wheelCount[LMU_ROVER_LEFT]; i++)
			wheels[LMU_ROVER_LEFT][i].Init();
	for (i = 0; i < wheelCount[LMU_ROVER_RIGHT]; i++)
			wheels[LMU_ROVER_RIGHT][i].Init();
	
	da_lmu::Init();
}

void da_rover_lmu::ConfigureChassis(da_wheel *leftWheels, byte leftWheelCount,
		  da_wheel *rightWheels, byte rightWheelCount)
{
	  wheels[LMU_ROVER_LEFT] = leftWheels;
	  wheelCount[LMU_ROVER_LEFT] = leftWheelCount;
	  wheels[LMU_ROVER_RIGHT] = rightWheels;
	  wheelCount[LMU_ROVER_RIGHT] = rightWheelCount;
}
 