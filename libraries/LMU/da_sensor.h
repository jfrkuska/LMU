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

#ifndef da_sensor_h
#define da_sensor_h

/******************************************************************************
 * Includes
 ******************************************************************************/
 #include "da_types.h"
 
/******************************************************************************
 * Classes
 ******************************************************************************/
class da_sensor {
private:
	uint max_rate; 					/* samples per second */
	uint rate;						/* 0 <= current sample rate <= max_rate */
public:
	da_sensor(uint rate = 1, uint maxrate = 1): rate(rate), max_rate(maxrate) { }; 

	virtual uchar Connect(void) = 0;
	virtual uchar Disconnect(void) = 0;
	virtual uchar Calibrate(void) = 0;
	virtual uchar SetRate(uint) = 0;
	virtual void Sample(void) = 0;
	uint GetRate(void) { return rate; }
};

#endif