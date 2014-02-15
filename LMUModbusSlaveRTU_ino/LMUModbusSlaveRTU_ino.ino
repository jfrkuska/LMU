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

#include <da_modbus_lmu.h>
#include <da_dc_motor.h>
#include <da_direct_switch.h>
#include <da_analog_sensor.h>
#include <da_i2c_sensor.h>
#include <ModbusSlave.h>
#include <MemoryFree.h>

#define MOTOR_CNT    2
#define SENSOR_CNT    0
#define SWITCH_CNT  1


/* L298N Motor Driver Pins */
#define M0_EN_PIN 10
#define M0_P0_PIN 12
#define M0_P1_PIN 13
#define M1_EN_PIN 9
#define M1_P0_PIN 8
#define M1_P1_PIN 11

/* Switches Pins */
#define SW_LED_PIN 13

#define ARRAY_SIZE(x, y) (sizeof(x)/sizeof(y))

/* create our chassis with 2 motors */
da_dc_motor motors[] = {
  da_dc_motor(MTR_CW, 255, M0_EN_PIN, M0_P0_PIN, M0_P1_PIN),
  da_dc_motor(MTR_CW, 255, M1_EN_PIN, M1_P0_PIN, M1_P1_PIN)
};

da_direct_switch switches[] = {
  da_direct_switch(SW_LED_PIN, SW_ON)
};

da_analog_sensor <int> sensors[] = {
//  <int>da_analog_sensor (A0, 10, 1); 
}

da_modbus_lmu chassis;

unsigned long tprev = 0;        /* previous time*/

void setup() 
{
  /* I2C - Join the bus as a masterx */
  Wire.begin(); 
    
  Serial.print("freeMemory()=");
  Serial.println(freeMemory());

  chassis.Configure();
}

void loop()
{
  chassis.Update();  
}

