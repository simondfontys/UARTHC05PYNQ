/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xuartlite.h"
#include "xparameters.h"
#include "xstatus.h"
#include "xuartlite_l.h"



#define UARTLITE_DEVICE_ID  XPAR_UARTLITE_0_DEVICE_ID


int main() {
	XUartLite uart_rtl;
	u8 rxBuffer[16]; // Buffer for receiving data
    // Initialize UART
    XUartLite_Initialize(&uart_rtl, UARTLITE_DEVICE_ID);
    //XUartLite_SetRecvTimeout(&uart_rtl, 0);

    while (1) {
        // Receive data via UART
        int bytesRead = 0;
        int numberReceived = 0;

        while (1) {
            bytesRead = XUartLite_Recv(&uart_rtl, &rxBuffer[numberReceived], 1);
            if (bytesRead > 0) {
                if (rxBuffer[numberReceived] == '\n') {
                    rxBuffer[numberReceived] = '\0'; // Null-terminate the received data
                    unsigned long receivedNumber;
                    sscanf((const char*)rxBuffer, "%lu", &receivedNumber);
                    xil_printf("Received number: %lu\r\n", receivedNumber);
                    break;
                }
                numberReceived += bytesRead;
            }
        }
    }

//

//int main() {
//    XUartLite uart_rtl;
//    u8 txBuffer[16]; // Buffer for transmitting data
//    u32 number = 60;
//
//    // Initialize UART
//    XUartLite_Initialize(&uart_rtl, UARTLITE_DEVICE_ID);
//    // Seed the random number generator
//    //srand(time(NULL));
//    while (1) {
//        // Generate a random number between 50 and 90
//        u32 number = rand() % 41 + 50;
//        // Convert number to string
//        //sprintf((char*)txBuffer, "%lu\r\n", number);
//        sprintf((char*)txBuffer, "%lu\r\n", (unsigned long) number);
//       // printf("%lu\r\n", number);
//
//        // Send data via UART
//        XUartLite_Send(&uart_rtl, txBuffer, strlen((char*)txBuffer));
//        //XUartLite_Send(&uart_rtl, txBuffer, 1));
//
//        //xil_printf("Data sent: %s\r\n", txBuffer); // Print the sent data
//        xil_printf("%s\r", txBuffer); // Print the sent data
//
//        // Delay for a period of time
//        for (int i = 0; i < 10000000; i++);  // Adjust the delay value as needed
//    }

    return 0;
}

