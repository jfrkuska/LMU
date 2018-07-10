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

#ifndef da_wheel_h
#define da_wheel_h

/******************************************************************************
 * Includes
 ******************************************************************************/
 #include "da_types.h"
 #include "da_motor_driver.h"
 #include "Arduino.h"

#define CALIBRATE_DELAY 3000

/******************************************************************************
 * Classes
 ******************************************************************************/
class da_wheel {
private:
  da_motor_driver &driver;
  float diameter;
  enum LMUMovement forwardRotation;					/* rotation orientation for the wheel to move forward */
  enum LMUMovement direction;
public:
  da_wheel(da_motor_driver &driver,
		  float diameter,
		  enum LMUMovement rot):\
		  forwardRotation(rot),
		  driver(driver),
		  diameter(diameter),
		  direction(LMU_FORWARD) { }
  
  void Init(void) { driver.Init(); }
  void setVector(uint, enum LMUMovement);
 };
 
#endif