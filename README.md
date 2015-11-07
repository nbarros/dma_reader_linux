# dma_reader_linux
Small utility to dump the DMA contents from the uZed.

The __master__ branch implements a simple dump of the 128 bits of the DMA. No configuration memory mapped registers are present.

## How to build:

1. From inside the linux system on the microzed:
  1. go into the Debug directory and do ```make```
2. From another linux PC:
  1. Setup Xilinx tools:
  ``` source $XILINX_DIR/settings64.sh```
  2. Define the cross compile variable:
  ``` export CROSS_COMPILE=arm-xilinx-linux-gnueabi-
  ```
  3. Go into the debug directory and do ```make```.

__NOTE__: This tool requires the ```xdma``` driver for DMA access.

##Revision history:

05-11-2015: Initial revision merging pieces of several projects to dump the DMA and configure using memory mapped registers.
