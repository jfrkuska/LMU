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
#include "da_modbus_rover.h"

void da_modbus_rover::Update(void)
{ 	
	/* update chassis */
	Travel(regs[chassisIdx], (enum LMUMovement)regs[chassisIdx+1]);
	
	/* update feedback data */
	da_rover_lmu::Update();
	
	/* main modbus loop*/
	if(mbs.update(regs, registerCount)) {
	
		wdog = millis();
	
		/* update sensors */
		if ((sensorIdx != INVALID_IDX) && regs[sensorIdx] < GetSensorCnt())
			GetSensor(regs[sensorIdx])->Sample();
		
		/* update motor */
		if ((motorIdx != INVALID_IDX) &&
				(regs[motorIdx] < GetMotorCnt()) &&
				(regs[motorIdx+2] != GetMotor(regs[motorIdx])->GetThrottle()))
			GetMotor(regs[motorIdx])->SetVector((uint)regs[motorIdx+2], (enum LMUMovement)regs[motorIdx+1]);
			 
		/* update switch */
		if ((switchIdx != INVALID_IDX) &&
				(regs[switchIdx] < GetSwitchCnt()) &&
				(regs[switchIdx+1] != GetSwitch(regs[switchIdx])->getState()))
			GetSwitch(regs[switchIdx])->setState((enum switch_state)regs[switchIdx+1]);
	}	 
	
	/* update delta time */
	regs[chassisIdx+5] = millis() - wdog;
	
	/* if no comm in TIMEOUT msec */
	if ((timeout != 0) && (regs[chassisIdx+5] > timeout))  {
		DA_DEBUG_MTR("Rover Comm timeout\r");
	  /* handle timeout */
	  /* halt motors */
	  /* turn off switches */
	}
	   
}

void da_modbus_rover::Init(void)
{
	mbs.configure(MB_SLAVE, baudrate, MB_PARITY, MB_TXENPIN);
	da_rover_lmu::Init();
	wdog = millis();
	DA_DEBUG_MTR("Rover Initialized\r");
}
