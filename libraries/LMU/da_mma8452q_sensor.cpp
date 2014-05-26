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

#include "da_mma8452q_sensor.h"

void da_mma8452q_sensor::ReadAccelData(int *destination)
{
  byte rawData[6];  // x/y/z accel register data stored here

  ReadRegisters(OUT_X_MSB, 6, rawData);  // Read the six raw data registers into data array

  // Loop to calculate 12-bit ADC and g value for each axis
  for(int i = 0; i < 3 ; i++)
  {
    int gCount = (rawData[i*2] << 8) | rawData[(i*2)+1];  //Combine the two 8 bit registers into one 12-bit number
    gCount >>= 4; //The registers are left align, here we right align the 12-bit integer

    // If the number is negative, we have to make it so manually (no 12-bit data type)
    if (rawData[i*2] > 0x7F)
    {  
      gCount = ~gCount + 1;
      gCount *= -1;  // Transform into negative 2's complement #
    }

    destination[i] = gCount; //Record this gCount into the 3 int array
  }
}

void da_mma8452q_sensor::Init()
{
  byte c = ReadRegister(WHO_AM_I);  // Read WHO_AM_I register
  if (c == 0x2A) // WHO_AM_I should always be 0x2A
  {  
	  DA_DEBUG_SENSOR("MMA8452Q is online...\n");
  }
  else
  {
    DA_DEBUG_SENSOR("Could not connect to MMA8452Q. Halting\r\n");
    while(1) ; // Loop forever if communication doesn't happen
  }

  Disconnect();  // Must be in standby to change registers

  /* set sensitivity */
  if(gsel > MMA8452_MAX_G) gsel = MMA8452_MAX_G;
  gsel >>= 2; // Neat trick, see page 22. 00 = 2G, 01 = 4A, 10 = 8G
  WriteRegister(XYZ_DATA_CFG, gsel);

  /* update output data rate */
  
  /* update powermode */
  if(gsel > LoPower) gsel = LoPower;
  WriteRegister(CTRL_REG2, powermode);

  Connect();
}

// Sets the MMA8452 to standby mode. It must be in standby to change most register settings
void da_mma8452q_sensor::Disconnect()
{
  byte c = ReadRegister(CTRL_REG1);
  WriteRegister(CTRL_REG1, c & ~(0x01)); //Clear the active bit to go into standby
}

// Sets the MMA8452 to active mode. Needs to be in this mode to output data
void da_mma8452q_sensor::Connect()
{
  byte c = ReadRegister(CTRL_REG1);
  WriteRegister(CTRL_REG1, c | 0x01); //Set the active bit to begin detection
}

void da_mma8452q_sensor::Sample()
{ 
  if (!sampleData)
	return;
  
  ReadAccelData(sampleData);
  
  // Print out values
//  DA_DEBUG_SENSOR("accel:");
//  for (int i = 0 ; i < 3 ; i++)
//  {
//	  DA_DEBUG_SENSOR(sampleData[i]);  // Print g values
//	  DA_DEBUG_SENSOR(",");  // tabs in between axes
//  }
//  DA_DEBUG_SENSOR("\n\r");

}
