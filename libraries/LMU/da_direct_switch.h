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

#ifndef da_direct_switch_h
#define da_direct_switch_h

/******************************************************************************
 * Includes
 ******************************************************************************/
#include "Arduino.h"
#include "da_types.h"
#include "da_switch.h"
  
/******************************************************************************
 * Classes
 ******************************************************************************/
class da_direct_switch : public da_switch {
private:
	uchar pin;
public:
	da_direct_switch(uchar pin, enum switch_state init_state = SW_OFF, uchar on_state = HIGH): 
	da_switch(on_state) { pinMode(pin, OUTPUT); (init_state == SW_ON) ? on() : off(); }
	void on(void) { digitalWrite(pin, getOnState()); }
	void off(void) { digitalWrite(pin, !getOnState()); }
	enum switch_state getState(void) { return (digitalRead(pin) == getOnState()) ? SW_ON : SW_OFF; }
};

#endif