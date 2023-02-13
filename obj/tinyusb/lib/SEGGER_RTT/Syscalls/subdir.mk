################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tinyusb/lib/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_GCC.c \
../tinyusb/lib/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_IAR.c \
../tinyusb/lib/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_KEIL.c \
../tinyusb/lib/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_SES.c 

OBJS += \
./tinyusb/lib/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_GCC.o \
./tinyusb/lib/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_IAR.o \
./tinyusb/lib/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_KEIL.o \
./tinyusb/lib/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_SES.o 

C_DEPS += \
./tinyusb/lib/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_GCC.d \
./tinyusb/lib/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_IAR.d \
./tinyusb/lib/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_KEIL.d \
./tinyusb/lib/SEGGER_RTT/Syscalls/SEGGER_RTT_Syscalls_SES.d 


# Each subdirectory must supply rules for building sources it contributes
tinyusb/lib/SEGGER_RTT/Syscalls/%.o: ../tinyusb/lib/SEGGER_RTT/Syscalls/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/media/leechunhei/Data/MounRiver/tinyusb/Debug" -I"/media/leechunhei/Data/MounRiver/tinyusb/Core" -I"/media/leechunhei/Data/MounRiver/tinyusb/User" -I"/media/leechunhei/Data/MounRiver/tinyusb/Peripheral/inc" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/include" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/portable/Common" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/portable/GCC/RISC-V" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/portable/GCC/RISC-V/chip_specific_extensions/RV32I_PFIC_no_extensions" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/portable/MemMang" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


