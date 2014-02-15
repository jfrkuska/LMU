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
#ifndef da_modbus_lmu_h
#define da_modbus_lmu_h

/* Modbus slave configuration parameters */
#define MB_SLAVE     1
#define MB_BAUD      115200
#define MB_PARITY    'e'
#define MB_TXENPIN   0

/******************************************************************************
 * Includes
 ******************************************************************************/
 #include "da_types.h"
 #include "da_motor.h"
 #include "da_sensor.h"
 #include "da_switch.h"
#include "da_lmu.h"
#include <ModbusSlave.h>
 
/******************************************************************************
 * Classes
 ******************************************************************************/
/* modbus slave registers */
enum {        
  MB_MTR_IDX,        /* motor index to set */
  MB_MTR_DIR,        /* BRAKE, FORWARD, REVERSE */
  MB_MTR_THROTTLE,   /* 0x00 - 0xFF */
  MB_SW_IDX,         /* switch index to set */
  MB_SW_STATE,       /* switch state */
  MB_SENSR_IDX,      /* sensor index to set */
  MB_SENSR_REG,      /* sensor setting */
  MB_SENSR_VAL,      /* sensor value */
  MB_REGS	     /* total number of registers on slave */
};

class da_modbus_lmu: public da_lmu {
private:
	int regs[MB_REGS];
	ModbusSlave mbs;
	unsigned long wdog;         /* watchdog */
public:
  da_modbus_lmu(): mbs(), wdog(0), da_lmu() {}

  void Configure(uchar slave = MB_SLAVE, uint baud = MB_BAUD, char parity = MB_PARITY, uchar pin = MB_TXENPIN);
  void Update(void);
};

#endif