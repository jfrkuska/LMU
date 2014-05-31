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
#include "da_lmu.h"

void da_lmu::Init(void) {
	
	int i;
	
	/* Init all sensors */
	for (i = 0; i < sensorCount; i++)
		sensors[i]->Init();
	
	/* Init all switches */
	for (i = 0; i < switchCount; i++) {
		switches[i]->Init();
	}
	
	/* Init all motors */
	for (i = 0; i < motorCount; i++)
		motors[i]->Init();

}

da_motor_driver* da_lmu::GetMotor(byte motorNum) 
{
	if (motors)
		return motors[motorNum];
	else
		return NULL;
}

da_sensor* da_lmu::GetSensor(byte sensorNum)
{
	if (sensors)
		return sensors[sensorNum];
	else
		return NULL;
}

da_switch* da_lmu::GetSwitch(byte switchNum) 
{
	if (switches)
		return switches[switchNum];
	else
		return NULL;
}
 