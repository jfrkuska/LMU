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
#define MMA8452_MAX_G		8		/* 8g */

/* defaults chosen to provide stable low noise hi res output */
#define MMA8452_DEF_GSEL	2		/* +/- 2g */
#define MMA8452_DEF_ODR		400		/* 400 Hz */
#define MMA8453_DEF_POWERMODE	2	/* Hi Res */

//MMA8452 registers
#define OUT_X_MSB 		0x01
#define XYZ_DATA_CFG  	0x0E
#define WHO_AM_I   		0x0D
#define CTRL_REG1  		0x2A
#define CTRL_REG2  		0x2B
#define CTRL_REG3		0x2C
#define CTRL_REG4		0x2D
#define CTRL_REG5		0x2E
#define OFF_X			0x2F
#define OFF_Y			0x30
#define OFF_Z			0x31

/******************************************************************************
 * Includes
 ******************************************************************************/
 #include "da_types.h"
 #include "da_i2c_sensor.h"
 
/******************************************************************************
 * Classes
 ******************************************************************************/
class da_mma8452q_sensor: public da_i2c_sensor {
public:
	enum PowerMode
	{
		Normal = 0,
		LoNoiseLoPower,
		HiResolution,
		LoPower
	};
	enum ODR
	{
		ODR_800 = 0,
		ODR_400,
		ODR_200,
		ODR_100,
		ODR_50,
		ODR_12_5,
		ODR_6_25,
		ODR_1_56
	};
private:
	int *sampleData;
	void ReadAccelData(int *destination);
	byte gsel, powermode;
public:
	da_mma8452q_sensor(int *sampleData, uint rate = MMA8452_MAX_RATE,
			byte slaveAddress = MMA8452_ADDRESS, byte gsel = MMA8452_DEF_GSEL,
			byte powermode = MMA8453_DEF_POWERMODE):
				sampleData(sampleData),
				gsel(gsel),
				powermode(powermode),
				da_i2c_sensor(slaveAddress,
						WHO_AM_I,
						rate,
						MMA8452_MAX_RATE) { }
	
	void Init(void);
	void Connect(void);
	void Disconnect(void);
	void Calibrate(void) {}
	void SetRate(uint) {}
	void Sample(void);
};

#endif