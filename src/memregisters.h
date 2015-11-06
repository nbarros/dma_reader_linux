/*
 * memregisters.h
 *
 *  Created on: Jul 28, 2015
 *      Author: nbarros
 */

#ifndef MEMREGISTERS_H_
#define MEMREGISTERS_H_

typedef struct gpio_dev {
	uint32_t base_addr;
	uint32_t high_addr;
	uint32_t dev_id;
	uint32_t has_intr;
	uint32_t is_dual;
} gpio_dev;

typedef struct mem_dev {
	uint32_t base_addr;
	uint32_t high_addr;
	uint32_t dev_id;
	uint32_t n_regs;
	uint32_t reg_offset;
} mem_dev;
#define XPAR_MEMORY_MAPPER_0_S00_AXI_BASEADDR 0x43C00000
#define XPAR_MEMORY_MAPPER_0_S00_AXI_HIGHADDR 0x43C0FFFF

// Register offset in bytes
#define REGISTER_OFFSET 4
//
///// -- Some definitions for the GPIO inputs
///* Definitions for driver GPIO */
//#define XPAR_XGPIO_NUM_INSTANCES 3
//
///* Definitions for peripheral AXI_GPIO_0 */
//#define XPAR_AXI_GPIO_0_BASEADDR 0x41200000
//#define XPAR_AXI_GPIO_0_HIGHADDR 0x4120FFFF
//#define XPAR_AXI_GPIO_0_DEVICE_ID 0
//#define XPAR_AXI_GPIO_0_INTERRUPT_PRESENT 0
//#define XPAR_AXI_GPIO_0_IS_DUAL 1
//
//
///* Definitions for peripheral AXI_GPIO_1 */
//#define XPAR_AXI_GPIO_1_BASEADDR 0x41210000
//#define XPAR_AXI_GPIO_1_HIGHADDR 0x4121FFFF
//#define XPAR_AXI_GPIO_1_DEVICE_ID 1
//#define XPAR_AXI_GPIO_1_INTERRUPT_PRESENT 0
//#define XPAR_AXI_GPIO_1_IS_DUAL 1
//
//
///* Definitions for peripheral AXI_GPIO_2 */
//#define XPAR_AXI_GPIO_2_BASEADDR 0x41220000
//#define XPAR_AXI_GPIO_2_HIGHADDR 0x4122FFFF
//#define XPAR_AXI_GPIO_2_DEVICE_ID 2
//#define XPAR_AXI_GPIO_2_INTERRUPT_PRESENT 0
//#define XPAR_AXI_GPIO_2_IS_DUAL 1
//
//
//#define XGPIO_CHAN_OFFSET  8
//
//#define XGPIO_DATA_OFFSET	0x0   /**< Data register for 1st channel */
//#define XGPIO_TRI_OFFSET	0x4   /**< I/O direction reg for 1st channel */
//#define XGPIO_DATA2_OFFSET	0x8   /**< Data register for 2nd channel */
//#define XGPIO_TRI2_OFFSET	0xC   /**< I/O direction reg for 2nd channel */
//
//
////// -- Reset GPIO
//
///* Definitions for peripheral GPIO_CMD */
//#define XPAR_GPIO_CMD_BASEADDR 0x41230000
//#define XPAR_GPIO_CMD_HIGHADDR 0x4123FFFF
//#define XPAR_GPIO_CMD_DEVICE_ID 2
//#define XPAR_GPIO_CMD_INTERRUPT_PRESENT 0
//#define XPAR_GPIO_CMD_IS_DUAL 0
//



// How to read a GPIO register:
/**
 * 	return XGpio_ReadReg(InstancePtr->BaseAddress,
			      ((Channel - 1) * XGPIO_CHAN_OFFSET) + XGPIO_DATA_OFFSET);


#define XGpio_ReadReg(BaseAddress, RegOffset) \
	XGpio_In32((BaseAddress) + (RegOffset))


 *
 */

// How to set the direction
/**
 * 	XGpio_WriteReg(InstancePtr->BaseAddress,
			((Channel - 1) * XGPIO_CHAN_OFFSET) + XGPIO_TRI_OFFSET,
			DirectionMask);

#define XGpio_WriteReg(BaseAddress, RegOffset, Data) \
	XGpio_Out32((BaseAddress) + (RegOffset), (u32)(Data))

 *
 */

#endif /* MEMREGISTERS_H_ */
