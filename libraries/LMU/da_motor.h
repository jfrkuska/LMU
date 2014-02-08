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

#ifndef da_motor_h
#define da_motor_h

/******************************************************************************
 * Includes
 ******************************************************************************/
 #include "da_types.h"

 /******************************************************************************
 * Typedefs
 ******************************************************************************/
/* 
* Name: enum forward_rotation
* This sets the way the motor turns in order to progress linearly forward */
enum forward_rotation {
	MTR_CW,
	MTR_CCW
};

/* Name: enum travel_direction
 * this sets the motor to either move forward or backwards linearly
 * from its current position */
enum travel_direction {
	MTR_BRAKE,
	MTR_FORWARD,
	MTR_REVERSE
};

/******************************************************************************
 * Classes
 ******************************************************************************/
class da_motor {
private:
  enum forward_rotation rotation;						/* cw or ccw */
  enum travel_direction direction;						/* present rotation direction */
  uchar throttle_present;       						/* present motor throttle */
  uint throttle_max;									/* max motor throttle count */
  static uchar tot_num_motors;							/* total motors derived from class */
  uchar setForwardRotation(enum forward_rotation rot) { rotation = rot; }
public:
  da_motor(enum forward_rotation rot, uchar tmax): 
  rotation(rot), throttle_max(tmax) { tot_num_motors++; }
  virtual int setVector(uchar, enum travel_direction) = 0;
  uchar setThrottle(int value) { throttle_present = value & 0xFF; }
  uchar getThrottle(void) { return throttle_present; }
  enum forward_rotation getForwardRotation(void) { return rotation; }
  enum travel_direction getDirection(void) { return direction; }
  void setDirection(enum travel_direction new_dir) { direction = new_dir; }
  static uchar getMtrCnt(void) { return tot_num_motors; }
 };
 
#endif