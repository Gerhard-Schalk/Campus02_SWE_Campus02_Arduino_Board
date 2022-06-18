/*
 * SerialSendCmd.cpp
 *
 *  Created on: 14.06.2020
 *      Author: GS
 */
#include "SerialCmd.h"

uint8_t gbaTxBuffer[20];


//------------------------------------------------------------------------
// Function: SndCmdResponse
//------------------------------------------------------------------------
// Description: This function sends a PC Command Response.
//------------------------------------------------------------------------
// Command Response Format: (Reader to PC)
//        SndBuffer:   0     1     2       3        ..      n
//                  -------------------------------------------------
//                  | SOH | Cmd | Len | Data[0] .. Data[Len-1] | EOF |
//                  -------------------------------------------------
//------------------------------------------------------------------------
void serialSendCmd(uint8_t cmd, uint8_t *sndBuffer, uint8_t dataLength)
{
    unsigned char i;

    Serial.write(COM_SOH);       // Send SOF .. Start of Frame
    Serial.write(cmd);     // Send STATUS
    Serial.write(dataLength);    //Send LEN

    for(i=0;i<dataLength;i++)
    {
      Serial.write(sndBuffer[i]);    //Send DATA
    }

    Serial.write('\n'); // EOF for Hterm

    Serial.flush();
    delay(3);
}
