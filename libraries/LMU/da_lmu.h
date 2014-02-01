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

#include "Arduino.h"

typedef unsigned char uchar;

/* 
* Name: enum forward_orientation
* This sets the way the motor turns in order to progress linearly forward */
typedef enum forward_orientation {
	CW,
	CCW
}orientation;

/* this sets the motor to either move forward or backwards linearly
 * from its current position */
typedef enum travel_direction {
	REVERSE=-1,
	BRAKE=0,
	FORWARD=1
}travel;

class da_motor {
private:
  orientation forward;			/* cw or ccw */
  travel direction;			/* present rotation direction */
  unsigned char throttle_present;       /* present motor throttle */
  unsigned char throttle_max;		/* max motor throttle count */
  static uchar tot_num_mtrs;		/* total motors derived from class */
  unsigned char set_orientation(orientation rotation) { forward = rotation; }
public:
  da_motor(orientation fwd, uchar tmax): 
  forward(fwd), throttle_max(tmax) { tot_num_mtrs++; }
  virtual int setThrottle(uchar, travel) = 0;

  unsigned char set_throttle(int value) { throttle_present = value & 0xFF; }
  unsigned char get_throttle(void) { return throttle_present; }
  orientation get_orientation(void) { return forward; }
  travel get_direction(void) { return direction; }
  void set_direction(travel new_dir) { direction = new_dir; }
  static unsigned char get_mtr_cnt(void) { return tot_num_mtrs; }
 };

class da_dc_brushed: public da_motor {
private:
	unsigned char enable_pin;
	unsigned char pin0;
	unsigned char pin1;
public:
	da_dc_brushed(orientation rot,
		uchar tmax,
		unsigned char en, 
		unsigned char p0, 
		unsigned char p1): da_motor(rot,tmax), enable_pin(en), 
pin0(p0), pin1(p1) {
	pinMode(enable_pin, OUTPUT);
	pinMode(pin0, OUTPUT);
	pinMode(pin1, OUTPUT);
}
	int setThrottle(uchar, travel);
};
  
class da_lmu {
private:
  class da_motor *motors;
  unsigned int operation_time_s;	/* time in operation in seconds */
public:
  da_lmu(class da_motor *motors): 
  motors(motors) {}
  class da_motor* motor(uchar mtr_num) { return &motors[mtr_num]; }
};
