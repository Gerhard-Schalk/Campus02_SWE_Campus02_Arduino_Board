/*
 * BitConverter.h
 *
 *  Created on: 14.06.2020
 *      Author: GS
 */
#ifndef BITCONVERTER_H_
#define BITCONVERTER_H_

#include <Arduino.h>

void intToBytes(int iValue, uint8_t *baValue, bool reverseEndian);
void floatToBytes(float dValue, uint8_t *baValue, bool reverseEndian);
int bytesToInt(int iValue, uint8_t *baValue, bool reverseEndian);
float bytesToFloat(uint8_t *baValue, bool reverseEndian);


#endif /* BITCONVERTER_H_ */
