################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tinyusb/lib/fatfs/source/diskio.c \
../tinyusb/lib/fatfs/source/ff.c \
../tinyusb/lib/fatfs/source/ffsystem.c \
../tinyusb/lib/fatfs/source/ffunicode.c 

OBJS += \
./tinyusb/lib/fatfs/source/diskio.o \
./tinyusb/lib/fatfs/source/ff.o \
./tinyusb/lib/fatfs/source/ffsystem.o \
./tinyusb/lib/fatfs/source/ffunicode.o 

C_DEPS += \
./tinyusb/lib/fatfs/source/diskio.d \
./tinyusb/lib/fatfs/source/ff.d \
./tinyusb/lib/fatfs/source/ffsystem.d \
./tinyusb/lib/fatfs/source/ffunicode.d 


# Each subdirectory must supply rules for building sources it contributes
tinyusb/lib/fatfs/source/%.o: ../tinyusb/lib/fatfs/source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/media/leechunhei/Data/MounRiver/tinyusb/Debug" -I"/media/leechunhei/Data/MounRiver/tinyusb/Core" -I"/media/leechunhei/Data/MounRiver/tinyusb/User" -I"/media/leechunhei/Data/MounRiver/tinyusb/Peripheral/inc" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/include" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/portable/Common" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/portable/GCC/RISC-V" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/portable/GCC/RISC-V/chip_specific_extensions/RV32I_PFIC_no_extensions" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/portable/MemMang" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


