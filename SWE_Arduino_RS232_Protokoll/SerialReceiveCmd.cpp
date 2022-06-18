/*
 * SerialReceiveCmd.cpp
 *
 *  Created on: 14.06.2020
 *      Author: GS
 */
#include "SerialCmd.h"

void ExecuteRecSerialCommand();

const int DEBUG_PIN = 12;

uint8_t gbRecState = 0;             // Receive State
uint8_t gbaRxBuffer[20];


//------------------------------------------------------------------------
// Function: RS233RcvCmd
//------------------------------------------------------------------------
// Description:
// This function is called from the UART Interrupt Service Routine
// and receives a Command from the PC. After a complete command is received
// the global Flag "gbNewCmdReceived" is set to '1'
//------------------------------------------------------------------------
// PC Command Fromat: (PC to Reader)
// gbaRxBuffer:       0      1     2      3     ..      n
//                 --------------------------------------------
//                 | SOH | Cmd | Len | Data[0] .. Data[Len-1] |
//                 --------------------------------------------
//------------------------------------------------------------------------
void serialReceiveCmd(void)
{
    static unsigned char pRecBuffer;

    // Command State Machine
    switch(gbRecState)
    {
        case 0: //  Receive Start of Header
            gbaRxBuffer[0] = Serial.read();

            // Check if we have received the Start of Header (SOH)
            if(gbaRxBuffer[0] == COM_SOH)
            {
            	gbRecState = 1;
            }
            else
            {
                gbRecState = 0;
            }
            break;

        case 1: //  Receive Command Byte
            gbaRxBuffer[1] = Serial.read();
            gbRecState = 2;
            break;

         case 2: //  Receive LEN Byte
            gbaRxBuffer[2] = Serial.read();

            if( gbaRxBuffer[2] == 0)
            {
                gbRecState = 0;
                ExecuteRecSerialCommand();
            }
            else
            {
                pRecBuffer = 0;
                gbRecState = 3;
             }
             break;

        case 3:  // Receive Data Bytes
              gbaRxBuffer[(3 + pRecBuffer)] = Serial.read();
              pRecBuffer++;

              //
              if(pRecBuffer >= (gbaRxBuffer[2])   )
              {
                gbRecState = 0;
                ExecuteRecSerialCommand();
              }
              break;
    }
}



