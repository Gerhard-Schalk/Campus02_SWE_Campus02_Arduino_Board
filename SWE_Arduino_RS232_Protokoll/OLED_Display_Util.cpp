/*
 * OLED_Display_Util.cpp
 *
 *  Created on: 14.06.2020
 *      Author: GS
 */
#include "OLED_Display_Util.h"

void oled_PrintIntValue(U8G2 u8g2, uint8_t x, uint8_t y, char* sPrefix,  int value, char* sUnit) {
  char sText[40]; // String-Puffer

  int n = sprintf(sText, sPrefix);
  n = sprintf(&sText[n], "%4d", value);
  sprintf(&sText[n + 5], sUnit);

  u8g2.drawUTF8(x, y, sText );
}



void oled_PrintFloatValue(U8G2 u8g2, uint8_t x, uint8_t y, char* sPrefix,  double value, char* sUnit) {
  char sText[40]; // String-Puffer

  int n = sprintf(sText, sPrefix);
  dtostrf(value, 5, 2, &sText[n]);
  sprintf(&sText[n + 5], sUnit);

  u8g2.drawUTF8(x, y, sText );
}

