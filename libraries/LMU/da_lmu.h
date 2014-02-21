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
 #include "da_motor_driver.h"
 #include "da_sensor.h"
 #include "da_switch.h"
 #include "da_device.h"
 
/******************************************************************************
 * Classes
 ******************************************************************************/
class da_lmu: public da_device {
private:
  da_motor_driver *motors;
  da_sensor *sensors;
  da_switch *switches;
  byte motorCount;
  byte sensorCount;
  byte switchCount;
public:
  da_lmu(da_switch *switches = 0,
		  byte wCount = 0,
		  da_sensor *sensors = 0,
		  byte sCount = 0,
		  da_motor_driver *motors = 0,
		  byte mCount = 0):\
		  motors(motors), 
		  sensors(sensors),
		  switches(switches),
		  motorCount(mCount),
		  sensorCount(sCount),
		  switchCount(wCount)
		  {}
  
  virtual void Rotate(uint throttle, enum RotationOrientation) = 0;
  virtual void Travel(uint throttle, enum TravelDirection) = 0;
  virtual void Calibrate(void) = 0;
  
  void Init(void) { /* TODO call Init on all mtrs, sensrs, switches */ }
  void Connect(void) { }
  void Disconnect(void) { /* call all */ }
  class da_motor_driver* GetMotor(byte motorNum);
  class da_sensor* GetSensor(byte sensorNum);
  class da_switch* GetSwitch(byte switchNum);
  void SetMotors(da_motor_driver *motors, byte mCount) { motors = motors; motorCount = mCount; }
  void SetSensors(da_sensor *sensors, byte sCount) { sensors = sensors; sensorCount = sCount; }
  void SetSwitches(da_switch *switches, byte wCount) { switches = switches; switchCount = wCount; }
  byte GetMotorCnt(void) { return motorCount; }
  byte GetSensorCnt(void) { return sensorCount; }
  byte GetSwitchCnt(void) { return switchCount; }
};

#endif