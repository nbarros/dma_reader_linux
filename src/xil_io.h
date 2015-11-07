/*
 * xil_io.h
 *
 *  Created on: Sep 8, 2015
 *      Author: nbarros
 */

#ifndef XIL_IO_H_
#define XIL_IO_H_

#include "xil_types.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
/*****************************************************************************/
/**
*
* Performs an input operation for an 8-bit memory location by reading from the
* specified address and returning the Value read from that address.
*
* @param	Addr contains the address to perform the input operation
*		at.
*
* @return	The Value read from the specified input address.
*
* @note		None.
*
******************************************************************************/
u8 Xil_In8(u32 Addr)
{
	return *(volatile u8 *) Addr;
}

/*****************************************************************************/
/**
*
* Performs an input operation for a 16-bit memory location by reading from the
* specified address and returning the Value read from that address.
*
* @param	Addr contains the address to perform the input operation
*		at.
*
* @return	The Value read from the specified input address.
*
* @note		None.
*
******************************************************************************/
u16 Xil_In16(u32 Addr)
{
	return *(volatile u16 *) Addr;
}

/*****************************************************************************/
/**
*
* Performs an input operation for a 32-bit memory location by reading from the
* specified address and returning the Value read from that address.
*
* @param	Addr contains the address to perform the input operation
*		at.
*
* @return	The Value read from the specified input address.
*
* @note		None.
*
******************************************************************************/
u32 Xil_In32(u32 Addr)
{
	return *(volatile u32 *) Addr;
}

/*****************************************************************************/
/**
*
* Performs an output operation for an 8-bit memory location by writing the
* specified Value to the the specified address.
*
* @param	OutAddress contains the address to perform the output operation
*		at.
* @param	Value contains the Value to be output at the specified address.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void Xil_Out8(u32 OutAddress, u8 Value)
{
	*(volatile u8 *) OutAddress = Value;
}

/*****************************************************************************/
/**
*
* Performs an output operation for a 16-bit memory location by writing the
* specified Value to the the specified address.
*
* @param	OutAddress contains the address to perform the output operation
*		at.
* @param	Value contains the Value to be output at the specified address.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void Xil_Out16(u32 OutAddress, u16 Value)
{
	*(volatile u16 *) OutAddress = Value;
}

/*****************************************************************************/
/**
*
* Performs an output operation for a 32-bit memory location by writing the
* specified Value to the the specified address.
*
* @param	OutAddress contains the address to perform the output operation
*		at.
* @param	Value contains the Value to be output at the specified address.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void Xil_Out32(u32 OutAddress, u32 Value)
{
	*(volatile u32 *) OutAddress = Value;
}

/** Read a value from a register. A 32 bit read is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is read from the register. The most significant data
 * will be read as 0.
 *
 * @param   BaseAddress is the base address of the CLOCKLOGIC device.
 * @param   RegOffset is the register offset from the base to write to.
 *
 * @return  Data is the data from the register.                       **/
#define mReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))

/** Write a value to a register. A 32 bit write is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is written.
 *
 * @param   BaseAddress is the base address of the CLOCKLOGICdevice.
 * @param   RegOffset is the register offset from the base to write to.
 * @param   Data is the data written to the register.
 *
 * @return  None.                                                     **/
#define mWriteReg(BaseAddress, RegOffset, Data) \
  	Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))

/// Memory Mapping Method
void* MemoryMapping(u32 BaseAddress, u32 HighAddress)
{
  //Begin memory mapping
  int memfd;
  void *MappedBaseAddress;
  off_t dev_base = BaseAddress;

  // Open Memory location
  memfd = open("/dev/mem", O_RDWR | O_SYNC);
  if (memfd == -1){
   	printf("Can't open /dev/mem.\n");
   	exit(0);
  }

  // Map into user space the area of memory containing the device
  MappedBaseAddress = mmap(0, (HighAddress-BaseAddress), PROT_READ | PROT_WRITE, MAP_SHARED, memfd, dev_base & ~(HighAddress-BaseAddress-1));
  if (MappedBaseAddress == (void *) -1){
   	printf("Can't map the memory to user space.\n");
    exit(0);
  }

  return MappedBaseAddress;
}

#endif /* XIL_IO_H_ */
