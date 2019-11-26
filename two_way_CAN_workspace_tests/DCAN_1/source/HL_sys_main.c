/** @file HL_sys_main.c 
*   @brief Application main file
*   @date 11-Dec-2018
*   @version 04.07.01
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com  
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "HL_sys_common.h"

/* USER CODE BEGIN (1) */
#include "stdio.h"
#include "HL_can.h"
#include "HL_sys_common.h"
#include "HL_system.h"
#include "HL_sci.h"

#include "HL_esm.h"
#include "HL_sys_core.h"
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
#define D_SIZE 7

uint8  tx_data[D_SIZE]  = {'A','L','B','E','R','T','A','\0'};

uint8_t rx_data[D_SIZE] = {0};
uint32_t error = 0;

/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */

    //init can
    canInit();
    fprintf(stderr, "Initialized.\n");

    //transmit on can 4, using msg box 1 because we're sending data
    canTransmit(canREG4, canMESSAGE_BOX1, tx_data);
    fprintf(stderr, "Sent.\n");

    // wait for a reply back using msg box 2 because we're receiving data
    while(!canIsRxMessageArrived(canREG4, canMESSAGE_BOX2));
    canGetData(canREG4, canMESSAGE_BOX2, rx_data);  /* receive on can4  */
    fprintf(stderr, "Received:\n");

    // output the received data
    int i;
    for (i = 0; i < D_SIZE; i++) {
        fprintf(stderr, "%c", rx_data[i]);
    }

    fprintf(stderr, "\nDone.");

    //run forever
    while(1);

/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */

void performBusyWork()
{
    int i;
    for(i = 0; i < 100000000; i++) {
        int a = 8000;
        int b = 2911;
        float c = a / b;
        c = c + 1;
    }
    return;

}
/* USER CODE END */
