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

#ifndef da_mma8452q_sensor_h
#define da_mma8452q_sensor_h

#define MMA8452_ADDRESS 	0x1C	/* 0x1d if high 0x1C if low */
#define MMA8452_MAX_RATE	800		/* Hz */

//MMA8452 registers
#define OUT_X_MSB 		0x01
#define XYZ_DATA_CFG  	0x0E
#define WHO_AM_I   		0x0D
#define CTRL_REG1  		0x2A

/******************************************************************************
 * Includes
 ******************************************************************************/
 #include "da_types.h"
 #include "da_i2c_sensor.h"
 
/******************************************************************************
 * Classes
 ******************************************************************************/
class da_mma8452a_sensor : public da_i2c_sensor {
private:
protected:
	void ReadRegisters(uchar addr, uint bytes, uchar *dest);
	uchar ReadRegister(uchar addr);
	void WriteRegister(uchar addr, uchar data);
public:
	da_mma8452a_sensor(uchar SA0 = MMA8452_ADDRESS, uint rate = 1) : da_i2c_sensor(SA0, WHO_AM_I, rate, MMA8452_MAX_RATE): 
	{ }
	
	virtual uchar Connect(void) = 0;
	virtual uchar Disconnect(void) = 0;
	virtual uchar Calibrate(void) = 0;
	virtual uchar SetRate(uint) = 0;
	virtual void Sample(void) = 0;
};

#endif