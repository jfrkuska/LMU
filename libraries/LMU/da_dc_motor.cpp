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

#include "da_dc_motor.h"

/* set dc mtr throttle and direction */
int da_dc_motor::setVector(uint throttle, enum travel_direction dir)
{
    enum forward_rotation forward = getForwardRotation();
    
    if ((throttle == getThrottle()) && (dir == getDirection()))
		return 0;
		    
    digitalWrite(pin0, LOW);
    digitalWrite(pin1, LOW);
    
    if (dir == MTR_BRAKE) {}
    else if (dir == MTR_FORWARD) {
        if (forward == MTR_CW)
			digitalWrite(pin0, HIGH);
        else 
			digitalWrite(pin1, HIGH);
    } else if (dir == MTR_REVERSE) {
        if (forward == MTR_CW)
          digitalWrite(pin1, HIGH);
        else
          digitalWrite(pin0, HIGH); 
    } else return -1;
    
    setDirection(dir);
    setThrottle(throttle);

    analogWrite(enable_pin, throttle);
    
    return 0;
}
