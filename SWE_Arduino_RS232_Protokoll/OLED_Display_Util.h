/*
 * OLED_Display_Util.h
 *
 *  Created on: 14.06.2020
 *      Author: GS
 */

#ifndef OLED_DISPLAY_UTIL_H_
#define OLED_DISPLAY_UTIL_H_

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

void oled_PrintIntValue(U8G2 u8g2, uint8_t x, uint8_t y, char* sPrefix,  int value, char* sUnit);
void oled_PrintFloatValue(U8G2 u8g2, uint8_t x, uint8_t y, char* sPrefix,  double value, char* sUnit);

#endif /* OLED_DISPLAY_UTIL_H_ */
