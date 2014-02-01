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
#include <ModbusSlave.h>

/* L298N Motor Driver Pins */
#define M0_EN_PIN 10
#define M0_P0_PIN 12
#define M0_P1_PIN 13
#define M1_EN_PIN 9
#define M1_P0_PIN 8
#define M1_P1_PIN 11
  
/* create a modbus slave instance */
ModbusSlave mbs;
/* create our chassis with 2 motors */
uchar da_motor::tot_num_mtrs = 0;
da_dc_brushed motors[] = {
  da_dc_brushed(CW,255, M0_EN_PIN, M0_P0_PIN, M0_P1_PIN),
  da_dc_brushed(CW,255, M1_EN_PIN, M1_P0_PIN, M1_P1_PIN)
};
da_lmu chassis(motors);

/* modbus slave registers */
enum {        
  MB_MTR_TARGET,     /* motor index to apply common settings to */
  MB_MTR_DIR,        /* BRAKE=0, FORWARD=1, REVERSE=-1 */
  MB_MTR_THROTTLE,   /* 0x00 - 0xFF */
  MB_REGS	     /* total number of registers on slave */
};

int regs[MB_REGS];

unsigned long wdog = 0;         /* watchdog */
unsigned long tprev = 0;        /* previous time*/

void setup() 
{
  /* Modbus slave configuration parameters */
  const unsigned char SLAVE = 1;
  const long BAUD = 115200;
  const char PARITY = 'e';
  const char TXENPIN = 0;

  /* MBS: configure */
  mbs.configure(SLAVE,BAUD,PARITY,TXENPIN);
}

void loop()
{
  /* main modbus loop*/
  if(mbs.update(regs, MB_REGS))
    wdog = millis();

  if ((millis() - wdog) > 5000)  { /* if no comm in 5 sec */
    /* handle timeout */
  }        

  /* update motor throttle */
  if (regs[MB_MTR_TARGET] < da_motor::get_mtr_cnt())
    motors[regs[MB_MTR_TARGET]].setThrottle(regs[MB_MTR_THROTTLE], (travel)regs[MB_MTR_DIR]);
}

