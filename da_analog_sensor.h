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

#ifndef da_analog_sensor_h
#define da_analog_sensor_h

/******************************************************************************
 * Includes
 ******************************************************************************/
 #include "da_types.h"
 #include "da_sensor.h"
 #include "Arduino.h"

/******************************************************************************
 * Classes
 ******************************************************************************/

class da_analog_sensor: public da_sensor {
private:
protected:
	uint rawcount;
	byte pin;
public:
	da_analog_sensor(byte pin, uint rate = 1, uint maxrate = 1): 
	pin(pin), rawcount(0), da_sensor(rate, maxrate) { }

	virtual void Calibrate(void) { }
	virtual void SetRate(uint) { }
	
	void Connect(void) { }
	void Disconnect(void) { }
	void Init(void) { DA_DEBUG_SENSOR("Sensor Initialized on pin="); DA_DEBUG_SENSOR(pin); DA_DEBUG_SENSOR("\n\r"); }
	void Sample(void);
	uint GetRawCount(void);
};

#endif