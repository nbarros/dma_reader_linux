/*
 * Empty C++ Application
 */
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
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* XILINX CONSORTIUM BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
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

//#include <stdio.h>
//#include "platform.h"
//#include "xgpio.h"
#include <iostream>
#include <cstdio>
#include <chrono>
#include <thread>

#include "libxdma.h"

extern "C" {
#include <stdint.h>
#include "xil_io.h"
};

typedef uint32_t u32;
//void print(char *str);

using std::cout;
using std::endl;

#define XPAR_XGPIO_NUM_INSTANCES 2
#define XPAR_AXI_GPIO_0_BASEADDR 0x41200000
#define XPAR_AXI_GPIO_0_HIGHADDR 0x4120FFFF
#define XPAR_AXI_GPIO_1_BASEADDR 0x41210000
#define XPAR_AXI_GPIO_1_HIGHADDR 0x4121FFFF
#define XGPIO_CHAN_OFFSET  8
#define XGPIO_DATA_OFFSET	0x0   /**< Data register for 1st channel */



int main()
{
    //init_platform();

    printf("Starting the TS dump\n");
	int Status;
	//u32 InputData;
	int i,j;
	// All 32 bits are used.
	u32 bitwidth = 0xFFFFFFFF;
	//u32 bitwidth = 0x0;
	// GPIO managers
	//XGpio GpioInput[XPAR_XGPIO_NUM_INSTANCES];  /* The driver instance for GPIO Device configured as I/P */


	printf("Now initializing the DMA:\n");
	const int LENGTH = 1025;
	int result = 0;
	//uint32_t i;
	//uint32_t *src;
	uint32_t *dst;

	printf("Starting the DMA...\n");
	result = xdma_init();
	if (result < 0) { //xdma_init() < 0) {
		printf("DMA failed to initialize.!\n");
		exit(EXIT_FAILURE);
	} else {
		printf("DMA started!\n");
	}

	dst = (uint32_t *) xdma_alloc(LENGTH, sizeof(uint32_t));
	printf("Obtained address %u\n",(uint32_t)dst);
	// fill dst with nothing
	for (i = 0; i < LENGTH; i++) {
		dst[i] = 0;
	}


	/*
	 * Set the direction for all signals to be inputs
	 */

//	//if (i) {
//			printf("Setting direction to %08X\n",bitwidth);
//			  //XGpio_SetDataDirection(&GpioInput[i], 1, bitwidth);
//			  printf("Done channel 1\n");
//			  //XGpio_SetDataDirection(&GpioInput[i], 2, bitwidth);
//			  printf("Done channel 2\n");
//		//  } else {
//		//	  XGpio_SetDataDirection(&GpioInput[i], 1, bitwidth);
//		//  }
//			  printf("...done\n");
//	}
	printf("Starting to read...\n");

	uint32_t baseaddr;
	int ret = 0;
	// Enter an infinite LOOP and keep reading everything
	while (1) {


		ret = xdma_perform_transaction(0,XDMA_WAIT_DST,NULL,0,dst,16);
		printf("DMA %08X %08X %08X %08X\r\n",(unsigned int)dst[3],(unsigned int)dst[2],(unsigned int)dst[1],(unsigned int)dst[0]);

		// Now take the contents from the DMA


		// print the readout contents:
		//for (i = 0; i < )
		//printf("Output : CTRL : 0x%08X (%u) STAT : 0x%08X TS : 0x%08X 0x%08X PRE : 0x%08X 0x%08X \n",data[0][1],data[0][1], data[0][0],data[1][0],data[1][1],data[2][0],data[2][1]);
		sleep(0.1);
	}
	printf("Preparing to exit.\n");
	xdma_exit();

    //cleanup_platform();
    return 0;
}
