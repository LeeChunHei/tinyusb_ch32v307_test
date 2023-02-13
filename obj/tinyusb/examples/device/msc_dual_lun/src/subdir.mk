################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tinyusb/examples/device/msc_dual_lun/src/main.c \
../tinyusb/examples/device/msc_dual_lun/src/msc_disk_dual.c \
../tinyusb/examples/device/msc_dual_lun/src/usb_descriptors.c 

OBJS += \
./tinyusb/examples/device/msc_dual_lun/src/main.o \
./tinyusb/examples/device/msc_dual_lun/src/msc_disk_dual.o \
./tinyusb/examples/device/msc_dual_lun/src/usb_descriptors.o 

C_DEPS += \
./tinyusb/examples/device/msc_dual_lun/src/main.d \
./tinyusb/examples/device/msc_dual_lun/src/msc_disk_dual.d \
./tinyusb/examples/device/msc_dual_lun/src/usb_descriptors.d 


# Each subdirectory must supply rules for building sources it contributes
tinyusb/examples/device/msc_dual_lun/src/%.o: ../tinyusb/examples/device/msc_dual_lun/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/media/leechunhei/Data/MounRiver/tinyusb/Debug" -I"/media/leechunhei/Data/MounRiver/tinyusb/Core" -I"/media/leechunhei/Data/MounRiver/tinyusb/User" -I"/media/leechunhei/Data/MounRiver/tinyusb/Peripheral/inc" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/include" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/portable/Common" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/portable/GCC/RISC-V" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/portable/GCC/RISC-V/chip_specific_extensions/RV32I_PFIC_no_extensions" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/portable/MemMang" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


