/*
 * SerialCmd.h
 *
 *  Created on: 14.06.2020
 *      Author: GS
 */

#ifndef SERIALCMD_H_
#define SERIALCMD_H_

#include <Arduino.h>

#define COM_SOH   0xA5     // Start of Header

extern uint8_t gbaRxBuffer[];

void serialReceiveCmd(void);
void serialSendCmd(uint8_t cmd, uint8_t *sndBuffer, uint8_t dataLength);

#endif /* SERIALCMD_H_ */
