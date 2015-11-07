################################################################################
# Automatically-generated file. Do not edit!
################################################################################





CC := $(CROSS_COMPILE)gcc
CXX := $(CROSS_COMPILE)g++
SIZEAPP := $(CROSS_COMPILE)size

RM := rm -rf

EXTRA_INCLUDES :=
EXTRA_LIBS :=
CC_SRCS :=
CC_DEPS :=
OBJS := 
ELFSIZE := 
USER_OBJS :=
USER_LIBS := 

CC_SRCS += \
./src/main.cc 

CC_DEPS += \
.build/main.d 

OBJS += \
.build/main.o 

XDMA_PREFIX:= /usr/local
XDMA_LIBRARY := -lxdma

## Do not touch below:
EXTRA_INCLUDES += -I$(XDMA_PREFIX)/include
EXTRA_LIBS += -L$(XDMA_PREFIX)/lib $(XDMA_LIBRARY)


# Add inputs and outputs from these tool invocations to the build variables 
ELFSIZE += \
dma_reader_linux.elf.size \


# All Target
all: builddir dma_reader_linux.elf secondary-outputs

builddir:
	-mkdir -p .build
	
# Tool invocations
dma_reader_linux.elf: $(OBJS) 
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linux g++ linker'
	$(CXX) -std=c++11 $(EXTRA_LIBS) -o "dma_reader_linux.elf" $(OBJS) $(USER_OBJS) $(USER_LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

dma_reader_linux.elf.size: dma_reader_linux.elf
	@echo 'Invoking: ARM Linux Print Size'
	$(SIZEAPP) dma_reader_linux.elf  |tee "dma_reader_linux.elf.size"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(ELFSIZE) dma_reader_linux.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE)

# Each subdirectory must supply rules for building sources it contributes
.build/%.o: ./src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Linux g++ compiler'
	$(CXX) -std=c++11 -Wall -O0 -g3 $(EXTRA_INCLUDES) -c -fmessage-length=0 -MT"$@" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


.PHONY: all clean dependents
.SECONDARY:

