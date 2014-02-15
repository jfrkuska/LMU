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
#include "da_modbus_lmu.h"

void da_modbus_lmu::Update(void)
{ 
	/* main modbus loop*/
	if(mbs.update(regs, MB_REGS))
	wdog = millis();
	
	if ((millis() - wdog) > getTimeout())  { /* if no comm in TIMEOUT msec */
	  /* handle timeout */
	  /* halt motors */
	  /* turn off switches */
	}

//	/* update motor throttle */
//	if ((regs[MB_MTR_IDX] < da_motor::getMotorCnt()) && (regs[MB_MTR_THROTTLE] != motors[regs[MB_MTR_IDX]].getThrottle()))
//	 motors[regs[MB_MTR_IDX]].setVector(regs[MB_MTR_THROTTLE], (enum travel_direction)regs[MB_MTR_DIR]);
//	     
//	/* update switch status */
//	if ((regs[MB_SW_IDX] < da_switch::getSwitchCnt()) && (regs[MB_SW_STATE] != switches[regs[MB_SW_IDX]].getState()))
//	 switches[regs[MB_MTR_IDX]].setState((enum switch_state)regs[MB_SW_STATE]);
	 
	/* update all active sensor */
	   
}

void da_modbus_lmu::Configure(uchar slave, uint baud, char parity, uchar pin) 
{ 
	mbs.configure(slave, baud, parity, pin); 
}

