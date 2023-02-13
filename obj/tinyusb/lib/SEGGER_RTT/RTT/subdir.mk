################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tinyusb/lib/SEGGER_RTT/RTT/SEGGER_RTT.c \
../tinyusb/lib/SEGGER_RTT/RTT/SEGGER_RTT_printf.c 

S_UPPER_SRCS += \
../tinyusb/lib/SEGGER_RTT/RTT/SEGGER_RTT_ASM_ARMv7M.S 

OBJS += \
./tinyusb/lib/SEGGER_RTT/RTT/SEGGER_RTT.o \
./tinyusb/lib/SEGGER_RTT/RTT/SEGGER_RTT_ASM_ARMv7M.o \
./tinyusb/lib/SEGGER_RTT/RTT/SEGGER_RTT_printf.o 

S_UPPER_DEPS += \
./tinyusb/lib/SEGGER_RTT/RTT/SEGGER_RTT_ASM_ARMv7M.d 

C_DEPS += \
./tinyusb/lib/SEGGER_RTT/RTT/SEGGER_RTT.d \
./tinyusb/lib/SEGGER_RTT/RTT/SEGGER_RTT_printf.d 


# Each subdirectory must supply rules for building sources it contributes
tinyusb/lib/SEGGER_RTT/RTT/%.o: ../tinyusb/lib/SEGGER_RTT/RTT/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/media/leechunhei/Data/MounRiver/tinyusb/Debug" -I"/media/leechunhei/Data/MounRiver/tinyusb/Core" -I"/media/leechunhei/Data/MounRiver/tinyusb/User" -I"/media/leechunhei/Data/MounRiver/tinyusb/Peripheral/inc" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/include" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/portable/Common" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/portable/GCC/RISC-V" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/portable/GCC/RISC-V/chip_specific_extensions/RV32I_PFIC_no_extensions" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/portable/MemMang" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

tinyusb/lib/SEGGER_RTT/RTT/%.o: ../tinyusb/lib/SEGGER_RTT/RTT/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross Assembler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -x assembler-with-cpp -I"/media/leechunhei/Data/MounRiver/tinyusb/Startup" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/include" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/portable/Common" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/portable/GCC/RISC-V" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/portable/GCC/RISC-V/chip_specific_extensions/RV32I_PFIC_no_extensions" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/portable/MemMang" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


