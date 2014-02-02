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

class da_motor* da_lmu::get_motor(uchar motor_num) 
{
	if (motors)
		return &motors[motor_num];
	else
		return NULL;
}

class da_sensor* da_lmu::get_sensor(uchar sensor_num)
{
	if (sensors)
		return &sensors[sensor_num];
	else
		return NULL;
}

class da_switch* da_lmu::get_switch(uchar switch_num) 
{
	if (switches)
		return &switches[switch_num];
	else
		return NULL;
}
 