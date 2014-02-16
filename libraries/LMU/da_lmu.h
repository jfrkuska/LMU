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
#ifndef da_lmu_h
#define da_lmu_h

/******************************************************************************
 * Includes
 ******************************************************************************/
 #include "da_types.h"
 #include "da_motor.h"
 #include "da_sensor.h"
 #include "da_switch.h"
 
/******************************************************************************
 * Classes
 ******************************************************************************/
class da_lmu: public da_rover_lmu {
private:
  da_motor *motors;
  da_sensor *sensors;
  da_switch *switches;
  uchar motor_cnt;
  uchar sensor_cnt;
  uchar switch_cnt;
  unsigned int operation_time_s;	/* time in operation in seconds */
  uint timeout;

public:
  da_lmu(uint timeout = 5000): timeout(timeout), motors(0), sensors(0), switches(0), operation_time_s(0) {}
  
  virtual void Rotate(uint throttle, enum RotationOrientation) = 0;
  virtual void Travel(uint throttle, enum TravelDirection) = 0;
	
  class da_motor* get_motor(uchar motor_num);
  class da_sensor* get_sensor(uchar sensor_num);
  class da_switch* get_switch(uchar switch_num);
  void set_sensors(da_sensor *sensors) { sensors = sensors; }
  void set_motors(da_motor *motors) { motors = motors; }
  void set_switches(da_switch *switches) { switches = switches; }
  uint getTimeout(void) { return timeout; }
};

#endif