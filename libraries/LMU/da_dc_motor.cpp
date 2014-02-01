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
#include "da_lmu.h"
#include "da_dc_motor.h"

/* set dc mtr throttle */
int da_dc_motor::setThrottle(uchar amount, travel dir)
{
    orientation forward = get_orientation();
    
    if ((get_throttle() == amount) && (get_direction() == dir))
		return 0;
		    
    digitalWrite(pin0, LOW);
    digitalWrite(pin1, LOW);
    
    if (dir == BRAKE) {}
    else if (dir == FORWARD) {
        if (forward == CW)
			digitalWrite(pin0, HIGH);
        else 
			digitalWrite(pin1, HIGH);
    } else if (dir == REVERSE) {
        if (forward == CW)
          digitalWrite(pin1, HIGH);
        else
          digitalWrite(pin0, HIGH); 
    } else return -1;
    
    set_direction(dir);    
    set_throttle(amount);

    analogWrite(enable_pin, amount);
    
    return 0;
}
