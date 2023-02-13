################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tinyusb/hw/bsp/ch32v307/ch32v30x_it.c \
../tinyusb/hw/bsp/ch32v307/family.c \
../tinyusb/hw/bsp/ch32v307/system_ch32v30x.c 

OBJS += \
./tinyusb/hw/bsp/ch32v307/ch32v30x_it.o \
./tinyusb/hw/bsp/ch32v307/family.o \
./tinyusb/hw/bsp/ch32v307/system_ch32v30x.o 

C_DEPS += \
./tinyusb/hw/bsp/ch32v307/ch32v30x_it.d \
./tinyusb/hw/bsp/ch32v307/family.d \
./tinyusb/hw/bsp/ch32v307/system_ch32v30x.d 


# Each subdirectory must supply rules for building sources it contributes
tinyusb/hw/bsp/ch32v307/%.o: ../tinyusb/hw/bsp/ch32v307/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/media/leechunhei/Data/MounRiver/tinyusb/Debug" -I"/media/leechunhei/Data/MounRiver/tinyusb/Core" -I"/media/leechunhei/Data/MounRiver/tinyusb/User" -I"/media/leechunhei/Data/MounRiver/tinyusb/Peripheral/inc" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/include" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/portable/Common" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/portable/GCC/RISC-V" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/portable/GCC/RISC-V/chip_specific_extensions/RV32I_PFIC_no_extensions" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/portable/MemMang" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


