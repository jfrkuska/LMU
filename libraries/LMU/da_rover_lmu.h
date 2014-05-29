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
 #include "da_wheel.h"
 #include "da_lmu.h"

enum LMURover {
	LMU_ROVER_LEFT,
	LMU_ROVER_RIGHT,
	LMU_ROVER_SIDES
};

/* TODO re-think this location */
struct fb_data {
	int x;
	int y;
	int z;
};

/******************************************************************************
 * Classes
 ******************************************************************************/
class da_rover_lmu: public da_lmu {
private:
  da_wheel *wheels[LMU_ROVER_SIDES];
  byte wheelCount[LMU_ROVER_SIDES];
  da_sensor *fbSensors;
  byte	fbSensorCount;
public:
  da_rover_lmu(da_wheel *leftWheels = 0,
		  byte leftWheelCount = 0,
		  da_wheel *rightWheels = 0,
		  byte rightWheelCount = 0,
		  da_switch *switches = 0,
		  byte wCount = 0,
		  da_sensor *sensors = 0,
		  byte sCount = 0,
		  da_motor_driver *motors = 0,
		  byte mCount = 0):\
		  da_lmu(switches, wCount, sensors, sCount, motors, mCount), 
		  fbSensors(NULL), fbSensorCount(0) { wheelCount[0] = wheelCount[1] = 0; }
  
  virtual void Init(void);
  void Travel(uint throttle, enum LMUMovement);
  void Calibrate(void);
  void ConfigureChassis(
		  da_wheel *leftWheels,
		  byte leftWheelCount,
		  da_wheel *rightWheels,
		  byte rightWheelCount);
  void ConfigureFBSensors(da_sensor *sensors, byte count);
  void Update(void);
};

#endif