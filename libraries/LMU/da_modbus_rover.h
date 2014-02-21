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
#ifndef da_modbus_rover_h
#define da_modbus_rover_h

#define MB_TIMEOUT	5000 /* milliseconds */
#define INVALID_IDX	-1

/* Modbus slave configuration parameters */
#define MB_SLAVE     1
#define MB_BAUD      115200
#define MB_PARITY    'e'
#define MB_TXENPIN   0

/******************************************************************************
 * Includes
 ******************************************************************************/
//#include <Arduino.h>
#include "da_types.h"
#include "da_rover_lmu.h"
#include <ModbusSlave.h>
 
/******************************************************************************
 * Classes
 ******************************************************************************/

/* FIXME: modbus rover _IS_A_ Modbus class */
class da_modbus_rover: public da_rover_lmu {
private:
	int *regs;
	byte registerCount;
	ModbusSlave mbs;
	unsigned long wdog, timeout;         /* watchdog */
	char chassisIdx, motorIdx, sensorIdx, switchIdx;
public:
  da_modbus_rover(int *regs, byte registerCount,
		  char chassisIdx,
		  char motorIdx = INVALID_IDX,
		  char sensorIdx = INVALID_IDX,
		  char switchIdx = INVALID_IDX,
		  uint timeout = MB_TIMEOUT):\
  da_rover_lmu(),
  regs(regs),
  registerCount(registerCount),
  mbs(),
  wdog(0),
  chassisIdx(chassisIdx),
  motorIdx(motorIdx),
  sensorIdx(sensorIdx),
  switchIdx(switchIdx),
  timeout(timeout) 
  { }

  void Init(void) { ConfigureComm(MB_SLAVE, MB_BAUD, MB_PARITY, MB_TXENPIN); da_rover_lmu::Init(); }
  void ConfigureComm(uchar slave = MB_SLAVE, uint baud = MB_BAUD, char parity = MB_PARITY, uchar pin = MB_TXENPIN);
  void Update(void);
};

#endif