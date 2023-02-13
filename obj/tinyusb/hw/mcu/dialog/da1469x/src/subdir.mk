################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tinyusb/hw/mcu/dialog/da1469x/src/da1469x_clock.c \
../tinyusb/hw/mcu/dialog/da1469x/src/hal_gpio.c \
../tinyusb/hw/mcu/dialog/da1469x/src/hal_system.c \
../tinyusb/hw/mcu/dialog/da1469x/src/hal_system_start.c \
../tinyusb/hw/mcu/dialog/da1469x/src/system_da1469x.c 

OBJS += \
./tinyusb/hw/mcu/dialog/da1469x/src/da1469x_clock.o \
./tinyusb/hw/mcu/dialog/da1469x/src/hal_gpio.o \
./tinyusb/hw/mcu/dialog/da1469x/src/hal_system.o \
./tinyusb/hw/mcu/dialog/da1469x/src/hal_system_start.o \
./tinyusb/hw/mcu/dialog/da1469x/src/system_da1469x.o 

C_DEPS += \
./tinyusb/hw/mcu/dialog/da1469x/src/da1469x_clock.d \
./tinyusb/hw/mcu/dialog/da1469x/src/hal_gpio.d \
./tinyusb/hw/mcu/dialog/da1469x/src/hal_system.d \
./tinyusb/hw/mcu/dialog/da1469x/src/hal_system_start.d \
./tinyusb/hw/mcu/dialog/da1469x/src/system_da1469x.d 


# Each subdirectory must supply rules for building sources it contributes
tinyusb/hw/mcu/dialog/da1469x/src/%.o: ../tinyusb/hw/mcu/dialog/da1469x/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/media/leechunhei/Data/MounRiver/tinyusb/Debug" -I"/media/leechunhei/Data/MounRiver/tinyusb/Core" -I"/media/leechunhei/Data/MounRiver/tinyusb/User" -I"/media/leechunhei/Data/MounRiver/tinyusb/Peripheral/inc" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/include" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/portable/Common" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/portable/GCC/RISC-V" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/portable/GCC/RISC-V/chip_specific_extensions/RV32I_PFIC_no_extensions" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/portable/MemMang" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


