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

#ifndef da_switch_h
#define da_switch_h

/******************************************************************************
 * Includes
 ******************************************************************************/
#include "Arduino.h"
#include "da_types.h"
 
enum switch_state {
	SW_OFF = 0,
	SW_ON = 1
};
 
/******************************************************************************
 * Classes
 ******************************************************************************/
class da_switch {
private:
	uchar on_state;
    static uchar tot_num_switches;	/* total switches derived from class */
public:
	da_switch(uint on_state = SW_ON): 
	on_state(on_state) { tot_num_switches++; }

	virtual void On(void) = 0;
	virtual void Off(void) = 0;
	virtual enum switch_state State(void) = 0;
};

#endif