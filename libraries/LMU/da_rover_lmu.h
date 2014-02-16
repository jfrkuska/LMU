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
#ifndef da_rover_lmu_h
#define da_rover_lmu_h

/******************************************************************************
 * Includes
 ******************************************************************************/
 #include "da_types.h"
 #include "da_rover_lmu.h"

enum LMURover {
	LMU_ROVER_LEFT,
	LMU_ROVER_RIGHT,
	LMU_ROVER_SIDES
}
/******************************************************************************
 * Classes
 ******************************************************************************/
class da_rover_lmu: public da_lmu {
private:
  da_wheels *wheels[LMU_ROVER_SIDES];
  byte wheelCount[LMU_ROVER_SIDES];
public:
  da_lmu(da_wheels *leftWheels, byte leftWheelCount, da_wheels *rightWheels, byte rightWheelCount, byte uint timeout = 5000){}  
  void Rotate(uint throttle);
  void Travel(uint throttle);
};

#endif