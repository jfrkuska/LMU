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
	int index = 0;
	/* update chassis */
	Travel(rover->chassis.index, (enum LMUMovement)rover->chassis.direction);
	
	/* update feedback data */
	da_rover_lmu::Update();
	
	/* main modbus loop*/
	if(mbs.update((int*)rover, registerCount)) {
	
		wdog = millis();
	
		/* update sensors */
		index = rover->sensor.index;
		if (index < GetSensorCnt()) {
			DA_DEBUG_MTR("Updating Sensor\r\n");
			GetSensor(index)->Sample();
			rover->sensor.data = GetSensor(index)->GetRawCount();
		}
		
		/* update motor */
		index = rover->motor.index;
		if ((index < GetMotorCnt()) &&
				(rover->motor.throttle != GetMotor(index)->GetThrottle())) {
			DA_DEBUG_MTR("Updating Throttle\r\n");
			GetMotor(index)->SetVector((uint)rover->motor.throttle,
					(enum LMUMovement)rover->motor.direction);
		}
		
		/* update switch */
		index = rover->sw.index;
		if ((index < GetSwitchCnt()) &&
				(rover->sw.state != GetSwitch(index)->getState())) {
			DA_DEBUG_MTR("Updating Switch\r\n");
			GetSwitch(index)->setState((enum switch_state)rover->sw.state);
		}
	}	 
	
	/* update delta time */
	rover->chassis.delta = millis() - wdog;
	
	/* if no comm in TIMEOUT msec */
	if ((timeout != 0) && (rover->chassis.delta > timeout))  {
		DA_DEBUG_MTR("Rover Comm timeout\r\n");
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
	DA_DEBUG_MTR("Rover Initialized\r\n");
}
