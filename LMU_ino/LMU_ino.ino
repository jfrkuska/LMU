




/*
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

#include <MemoryFree.h>
#include <Wire.h>
#include <ModbusSlave.h>


#include <da_l298_motor.h>
#include <da_wheel.h>
#include <da_mma8452q_sensor.h>
#include <da_modbus_rover.h>

enum {        
  MB_MTR_IDX,        /* motor index to set */
  MB_MTR_DIR,        /* BRAKE, CW, CCW */
  MB_MTR_THROTTLE,   /* 0x0000 - 0xFFFF */
  MB_SW_IDX,         /* switch index to set */
  MB_SW_STATE,       /* switch state */
  MB_SENSR_IDX,      /* sensor index to set */
  MB_SENSR_REG,      /* sensor setting */
  MB_SENSR_DATA,      /* sensor values */
  MB_CHASSIS_FB0,
  MB_CHASSIS_FB1,
  MB_CHASSIS_FB2,
  MB_CHASSIS_DELTA_TIME,
  MB_REGS   /* total number of registers on slave */
};

/* L298N Motor Driver Pins */
#define M0_EN_PIN 10
#define M0_P0_PIN 12
#define M0_P1_PIN 13
#define M1_EN_PIN 9
#define M1_P0_PIN 8
#define M1_P1_PIN 11

int regs[MB_REGS] = {};

da_l298_motor motorFR(M0_EN_PIN, M0_P0_PIN, M0_P1_PIN, 0xFF);
da_l298_motor motorBL(M1_EN_PIN, M1_P0_PIN, M1_P1_PIN, 0xFF);

da_mma8452q_sensor motion(&regs[MB_CHASSIS_FB0]);

da_wheel wheels_right[] = {
  da_wheel(motorFR, 4.2, LMU_CW),
};

da_wheel wheels_left[] = {
  da_wheel(motorBL, 4.2, LMU_CCW),
};

/* FIXME: idx assignment is still a hack */
da_modbus_rover mbRover(regs, MB_REGS, MB_CHASSIS_FB0, MB_MTR_IDX, MB_SENSR_IDX);

void setup() 
{
  Serial.begin(57600);
  Wire.begin();
  Serial.print("freeMemory()=");
  Serial.println(freeMemory());
  
  mbRover.ConfigureChassis(wheels_left, 1, wheels_right, 1);
  mbRover.ConfigureFBSensor(&motion, 1);
  mbRover.Init();
}

void loop()
{
  mbRover.Update();
}

