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

#include <da_lmu.h>
#include <da_dc_motor.h>
#include <da_direct_switch.h>
#include <da_i2c_sensor.h>
#include <ModbusSlave.h>
#include <MemoryFree.h>
#include <Wire.h>

#define TIMEOUT 5000

/* L298N Motor Driver Pins */
#define M0_EN_PIN 10
#define M0_P0_PIN 12
#define M0_P1_PIN 13
#define M1_EN_PIN 9
#define M1_P0_PIN 8
#define M1_P1_PIN 11

/* Switches Pins */
#define SW_LED_PIN 13

/* Modbus slave configuration parameters */
#define MB_SLAVE     1
#define MB_BAUD      115200
#define MB_PARITY    'e'
#define MB_TXENPIN   0

/* I2C configuration parameters */
#define MMA8452_ADDRESS 0x1C  // 0x1D if SA0 is high, 0x1C if low
#define OUT_X_MSB 0x01
#define XYZ_DATA_CFG  0x0E
#define WHO_AM_I   0x0D
#define CTRL_REG1  0x2A
#define GSCALE 2

/* create a modbus slave instance */
ModbusSlave mbs;
/* create our chassis with 2 motors */
da_dc_motor motors[] = {
  da_dc_motor(MTR_CW, 255, M0_EN_PIN, M0_P0_PIN, M0_P1_PIN),
  da_dc_motor(MTR_CW, 255, M1_EN_PIN, M1_P0_PIN, M1_P1_PIN)
};

da_direct_switch switches[] = {
  da_direct_switch(SW_LED_PIN, SW_ON)
};

da_i2c_sensor sensors[] = {
  da_i2c_sensor(,)
};

da_lmu chassis(motors, 0, switches);

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
  MB_LATENCY_US,     /* time taken for current execution */
  MB_REGS	     /* total number of registers on slave */
};

int regs[MB_REGS];

unsigned long wdog = 0;         /* watchdog */
unsigned long tprev = 0;        /* previous time*/
unsigned long ptime, deltime;

void setup() 
{
  /* MBS: configure */
  mbs.configure(MB_SLAVE, MB_BAUD, MB_PARITY, MB_TXENPIN);
  
  /* I2C - Join the bus as a masterx */
  Wire.begin(); 
    
  Serial.print("freeMemory()=");
  Serial.println(freeMemory());
  
  for (int i = 0; i < da_sensor::getSensorCnt(); i++) {
    sensors[i].Init();
  }
}

void loop()
{
  ptime = micros(); /* calculate elapsed time */
  /* main modbus loop*/
  if(mbs.update(regs, MB_REGS))
    wdog = millis();

  if ((millis() - wdog) > TIMEOUT)  { /* if no comm in TIMEOUT msec */
    /* handle timeout */
    /* halt motors */
    /* turn off switches */
  }        

  /* update motor throttle */
  if ((regs[MB_MTR_IDX] < da_motor::getMotorCnt()) && (regs[MB_MTR_THROTTLE] != motors[regs[MB_MTR_IDX]].getThrottle()))
    motors[regs[MB_MTR_IDX]].setVector(regs[MB_MTR_THROTTLE], (enum travel_direction)regs[MB_MTR_DIR]);
    
  /* update switch status */
  if ((regs[MB_SW_IDX] < da_switch::getSwitchCnt()) && (regs[MB_SW_STATE] != switches[regs[MB_SW_IDX]].getState()))
    switches[regs[MB_MTR_IDX]].setState((enum switch_state)regs[MB_SW_STATE]);
    
  /* update all active sensor */
  for (int i = 0; i < da_sensor::getSensorCnt(); i++) {
    sensors[i].Sample();
  }
  
  deltime = micros() - ptime;
  regs[MB_LATENCY_US] = (int)deltime;
  
}

