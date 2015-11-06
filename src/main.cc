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

#include "memregisters.h"
#include "memutils.h"

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

	// Start byt allocating the memory

    // Map the whole memory bunch
    printf("Mapping the memory needed for control and config...\n");

    mem_dev regs;
    regs.base_addr = XPAR_MEMORY_MAPPER_0_S00_AXI_BASEADDR;
    regs.high_addr = XPAR_MEMORY_MAPPER_0_S00_AXI_HIGHADDR;
    regs.dev_id = 0;
    regs.n_regs = 20;
    regs.reg_offset = 4;

    void *mappedCmd = MemoryMapping(regs.base_addr,regs.high_addr);

    printf("Mapping completed...\n");

    printf("Sending a reset to clear up any lingering trash...\n");

    mWriteReg(mappedCmd,10*REGISTER_OFFSET,0);

    sleep(1);
    printf("Reset sent. Now re-asserting the reset signal...\n");
    mWriteReg(mappedCmd,10*REGISTER_OFFSET,0);
    sleep(1);
    printf("Reset sent. Now proceeding with device setup...\n");



    printf("Starting the DMA dump\n");
	int Status;
	//u32 InputData;
	int i,j;
	// All 32 bits are used.
	u32 bitwidth = 0xFFFFFFFF;
	//u32 bitwidth = 0x0;
	// GPIO managers
	//XGpio GpioInput[XPAR_XGPIO_NUM_INSTANCES];  /* The driver instance for GPIO Device configured as I/P */


	printf("Initializing the DMA:\n");
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

	// Enabling the IPs just prior to start reading
	printf("Enabling the FPGA...\n");
	mWriteReg(mappedCmd,11*REGISTER_OFFSET,1);


	printf("Starting to read...\n");

	uint32_t baseaddr;
	int ret = 0;
	// Enter an infinite LOOP and keep reading everything
	while (1) {


		ret = xdma_perform_transaction(0,XDMA_WAIT_DST,NULL,0,dst,16);
//		printf("DMA %08X %08X %08X %08X\r\n",(unsigned int)dst[0],(unsigned int)dst[1],(unsigned int)dst[2],(unsigned int)dst[3]);
		printf("DMA %08X %08X %08X %08X\r\n",(unsigned int)dst[3],(unsigned int)dst[2],(unsigned int)dst[1],(unsigned int)dst[0]);

		// Now take the contents from the DMA


		// Don't sleep. If necessary this can be added later.
		//sleep(0.1);
	}
	printf("Preparing to exit.\n");
	xdma_exit();

    //cleanup_platform();
    return 0;
}
