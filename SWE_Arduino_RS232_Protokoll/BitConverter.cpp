/*
 * BitConverter.cpp
 *
 *  Created on: 14.06.2020
 *      Author: GS
 */
#include "BitConverter.h"

void intToBytes(int iValue, uint8_t *baValue, bool reverseEndian) {

	union {
		int iValue;
		uint8_t baValue[2];
	} u;

	u.iValue = iValue;

	if (reverseEndian == false) {
		baValue[0] = u.baValue[0];
		baValue[1] = u.baValue[1];
	} else {
		baValue[0] = u.baValue[1];
		baValue[1] = u.baValue[0];
	}
}

void floatToBytes(float dValue, uint8_t *baValue, bool reverseEndian) {

	union {
		float fValue;
		uint8_t baValue[4];
	} u;

	u.fValue = dValue;

	if (reverseEndian == false) {
		baValue[0] = u.baValue[0];
		baValue[1] = u.baValue[1];
		baValue[2] = u.baValue[2];
		baValue[3] = u.baValue[3];
	} else {
		baValue[0] = u.baValue[3];
		baValue[1] = u.baValue[2];
		baValue[2] = u.baValue[1];
		baValue[3] = u.baValue[0];
	}
}

int bytesToInt(int iValue, uint8_t *baValue, bool reverseEndian) {
	union {
		int iValue;
		uint8_t baValue[2];
	} u;

	if (reverseEndian == false) {
		u.baValue[0] = baValue[0];
		u.baValue[1] = baValue[1];
	} else {
		u.baValue[0] = baValue[1];
		u.baValue[1] = baValue[0];
	}

	return u.iValue;
}

float bytesToFloat(uint8_t *baValue, bool reverseEndian) {
	union {
		float fValue;
		uint8_t baValue[4];
	} u;

	if (reverseEndian == false) {
		u.baValue[0] = baValue[0];
		u.baValue[1] = baValue[1];
		u.baValue[2] = baValue[2];
		u.baValue[3] = baValue[3];
	} else {
		u.baValue[0] = baValue[3];
		u.baValue[1] = baValue[2];
		u.baValue[2] = baValue[1];
		u.baValue[3] = baValue[0];
	}

	return u.fValue;
}

