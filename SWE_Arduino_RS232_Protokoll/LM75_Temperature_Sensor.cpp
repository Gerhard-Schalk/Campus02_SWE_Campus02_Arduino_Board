/*
 * LM75_Temperature_Sensor.cpp
 *
 *  Created on: 14.06.2020
 *      Author: GS
 */
#include "LM75_Temperature_Sensor.h"


float LM75_getTemperature()
{
	int tempRegValue_MSB;
	int tempRegValue_LSB;
	float tempValue;

	// Set Pointer register - Temperature register
	Wire.beginTransmission(LM75_I2C_Add);
    Wire.write(LM75A_REGISTER_TEMP);
	Wire.endTransmission();

	Wire.requestFrom(LM75_I2C_Add, 2);
	if(Wire.available() )
	{
		tempRegValue_MSB = Wire.read();
		tempRegValue_LSB = Wire.read();
	}

	tempValue = (tempRegValue_MSB << 3) + (tempRegValue_LSB >> 5);
	tempValue = tempValue * 0.125;

	return tempValue;
}


