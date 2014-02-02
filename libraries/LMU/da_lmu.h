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
class da_lmu {
private:
  class da_motor *motors;
  class da_sensor *sensors;
  class da_switch *switches;
  unsigned int operation_time_s;	/* time in operation in seconds */
public:
  da_lmu(class da_motor *mtrs, class da_sensor *snsrs = 0, class da_switch *swtchs = 0): 
  motors(mtrs), sensors(snsrs), switches(swtchs) {}
  
  class da_motor* get_motor(uchar motor_num);
  class da_sensor* get_sensor(uchar sensor_num);
  class da_switch* get_switch(uchar switch_num);
};

#endif