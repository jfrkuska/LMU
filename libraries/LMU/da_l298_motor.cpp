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

#include "da_l298_motor.h"

/* set dc mtr throttle and direction */
void da_l298_motor::SetThrottle(uint value)
{
	
	enum MotorRotation dir = GetRotation();
	
    if (throttle == value)
		return;
		
    throttle = value & throttleMask;
    
    digitalWrite(pin0, LOW);
    digitalWrite(pin1, LOW);
   
    switch(dir) {
    case MTR_CW:
    	digitalWrite(pin0, HIGH);
    	break;
    case MTR_CCW:
        digitalWrite(pin1, HIGH);
    case MTR_BRAKE:
    default:
    	break;
    }

    analogWrite(enablePin, throttle);
}
