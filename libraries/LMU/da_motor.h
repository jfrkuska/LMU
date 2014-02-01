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

/******************************************************************************
 * Includes
 ******************************************************************************/
 #include "da_types.h"

 /******************************************************************************
 * Typedefs
 ******************************************************************************/
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
	BRAKE,
	FORWARD,
	REVERSE
}travel;

/******************************************************************************
 * Classes
 ******************************************************************************/
class da_motor {
private:
  orientation forward;			/* cw or ccw */
  travel direction;				/* present rotation direction */
  uchar throttle_present;       /* present motor throttle */
  uchar throttle_max;			/* max motor throttle count */
  static uchar tot_num_motors;	/* total motors derived from class */
  uchar set_orientation(orientation rotation) { forward = rotation; }
public:
  da_motor(orientation fwd, uchar tmax): 
  forward(fwd), throttle_max(tmax) { tot_num_motors++; }
  virtual int setThrottle(uchar, travel) = 0;

  uchar set_throttle(int value) { throttle_present = value & 0xFF; }
  uchar get_throttle(void) { return throttle_present; }
  orientation get_orientation(void) { return forward; }
  travel get_direction(void) { return direction; }
  void set_direction(travel new_dir) { direction = new_dir; }
  static uchar get_mtr_cnt(void) { return tot_num_motors; }
 };