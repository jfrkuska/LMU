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

#ifndef da_types_h
#define da_types_h

#if 1
#define DA_DEBUG(X) (Serial.print(X))
#define DA_DEBUG2(X,Y) (Serial.print(X,Y))
#define DA_DEBUG_F(X,Y) (Serial.println(X,Y))
#define da_debug
#define da_debug_motor
#define da_debug_sensor
#endif

typedef unsigned char 	uchar;
typedef unsigned int 	uint;

enum LMUMovement {
	LMU_FORWARD,
	LMU_BACKWARD,
	LMU_CW,
	LMU_CCW,
	LMU_STOP
};

/* Name: enum TravelDirection
 * linear travel directions */
// enum TravelDirection {
	// LMU_FORWARD,
	// LMU_REVERSE
// };

/* 
* Name: enum RotationOrientation
* This sets the way the motor turns in order to progress linearly forward */
// enum RotationOrientation {
	// LMU_CW,
	// LMU_CCW,
	// LMU_BRAKE,
// };

#endif