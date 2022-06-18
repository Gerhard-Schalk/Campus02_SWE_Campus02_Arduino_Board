/*
 * LM75_Temperature_Sensor.h
 *
 *  Created on: 14.06.2020
 *      Author: GS
 */

#ifndef LM75_TEMPERATURE_SENSOR_H_
#define LM75_TEMPERATURE_SENSOR_H_

#include <Arduino.h>
#include <Wire.h>

#define LM75_I2C_Add	0x48
#define LM75A_REGISTER_TEMP			0			// Temperature register (read-only)
#define LM75A_REGISTER_CONFIG		1			// Configuration register
#define LM75A_REGISTER_THYST		2			// Hysterisis register
#define LM75A_REGISTER_TOS			3			// OS register
#define LM75A_REGISTER_PRODID		7			// Product ID register - Only valid for Texas Instruments

#define LM75_CONF_OS_COMP_INT		1			// OS operation mode selection
#define LM75_CONF_OS_POL			2			// OS polarity selection
#define LM75_CONF_OS_F_QUE			3			// OS fault queue programming

#define LM75_OS_INPUT_PIN			9

float LM75_getTemperature();

#endif /* LM75_TEMPERATURE_SENSOR_H_ */
