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

#include "da_l9110_motor.h"

/* set dc mtr throttle and direction */
void da_l9110_motor::SetVector(uint value, enum LMUMovement rot)
{
	
    if (throttle == value)
		return;
		
    throttle = value & throttleMask;
    
    analogWrite(pin0, 0);
    analogWrite(pin1, 0);
   
    switch(rot) {
    case LMU_CW:
    	analogWrite(pin0, value);
    	break;
    case LMU_CCW:
    	analogWrite(pin1, value);
    case LMU_STOP:
    default:
    	break;
    }
}
