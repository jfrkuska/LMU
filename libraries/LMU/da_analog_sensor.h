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
 
/******************************************************************************
 * Classes
 ******************************************************************************/
class da_analong_sensor {
public:
	da_analog_sensor(uint maxrate = 0, uint samplebits = 0): 
	samplerate_max(maxrate), sample_bits(samplebits) { tot_num_sensors++; }

	uchar Connect(void);
	uchar Disconnect(void);
	t_sample* Sample(void);
};

#endif