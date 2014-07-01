
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
#include <da_l9110_motor.h>
#include <da_wheel.h>
#include <da_mma8452q_sensor.h>
#include <da_direct_switch.h>
#include <da_modbus_rover.h>
#include <da_analog_sensor.h>

/* L298N Motor Driver Pins */
#define M0_EN_PIN 10
#define M0_P0_PIN 6
#define M0_P1_PIN 5
#define M1_EN_PIN 9
#define M1_P0_PIN 8  /* shared with S0_I2 */
#define M1_P1_PIN 16 /* shared with S0_I1 */

/* L9110S Motor Driver Pins */
#define M1_P0_PIN 9
#define M1_P1_PIN 10
#define M2_P0_PIN 5
#define M2_P1_PIN 6

/* ULN2003 Driver Pins */
#define S0_I1  16   /* shared with D16 */
#define S0_I2  8    /* shared with D8 */
#define S0_I3  14  
#define S0_I4  7  
#define S0_I5  A0  
#define S0_I6  15   /* shared with INT1 */
#define S0_I7  1    /* shared with RXI, need to set to output? or use TXO */

struct mb_rover rover_data;

//da_l298_motor motorFR(M0_EN_PIN, M0_P0_PIN, M0_P1_PIN);
//da_l298_motor motorBL(M1_EN_PIN, M1_P0_PIN, M1_P1_PIN);
da_l9110_motor motorFR(M1_P0_PIN, M1_P1_PIN);
da_l9110_motor motorBL(M2_P0_PIN, M2_P1_PIN);

da_mma8452q_sensor motion((int*)&rover_data.chassis.xyz);

da_wheel wheels_right[] = {
  da_wheel(motorFR, 4.2, LMU_CW),
};

da_wheel wheels_left[] = {
  da_wheel(motorBL, 4.2, LMU_CCW),
};

da_direct_switch switches[] = {
  da_direct_switch(S0_I1),
  da_direct_switch(S0_I2),
  da_direct_switch(S0_I3),
  da_direct_switch(S0_I4),
  da_direct_switch(S0_I5),
  da_direct_switch(S0_I6),
  da_direct_switch(S0_I7),
};

da_switch *switcharray[] = { 
  &switches[0], 
  &switches[1],
  &switches[2],
  &switches[3],
  &switches[4],
  &switches[5],
  &switches[6]
};

da_analog_sensor sensors[] = {
  da_analog_sensor(A6),
  da_analog_sensor(A1),
  da_analog_sensor(A2),
  da_analog_sensor(A3)
};

da_sensor *sensorarray[] = { 
  &sensors[0],
  &sensors[1],
  &sensors[2],
  &sensors[3],
};

da_modbus_rover mbRover(&rover_data, sizeof(rover_data)/sizeof(int), 115200, 0);

void setup() 
{
  Wire.begin();
  Serial1.begin(57600);
  while (!Serial1) ;

  Serial1.print("freeMemory()=");
  Serial1.println(freeMemory());
  
  mbRover.ConfigureChassis(wheels_left, 1, wheels_right, 1);
  mbRover.ConfigureFBSensors(&motion, 1);
  mbRover.SetSwitches(switcharray, 7);
  mbRover.SetSensors(sensorarray, 4);
  mbRover.Init();
}

void loop()
{
  mbRover.Update();
}

