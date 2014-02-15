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

template <class T>
class da_analog_sensor: public da_sensor {
private:
protected:
	T *values;
	uint value_count;
	uchar pin;
	float conversion_rate;
public:
	da_analog_sensor(uchar pin, uint rate = 1, uint maxrate = 1, T *values = 0, uint count = 0): 
	pin(pin), values(values), value_count(count), da_sensor(rate, maxrate) { }

	uchar Connect(void) { return 0; }
	uchar Disconnect(void) { return 0; }
	void Sample(void);
	void SetConversionRate(float rate) { conversion_rate = rate; }
	void SetDataContainer(T *dataptr, uint size) { values = dataptr; value_count = size; }
};

#endif