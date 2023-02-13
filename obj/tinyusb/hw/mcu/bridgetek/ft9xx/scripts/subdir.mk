################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../tinyusb/hw/mcu/bridgetek/ft9xx/scripts/crt0.S 

OBJS += \
./tinyusb/hw/mcu/bridgetek/ft9xx/scripts/crt0.o 

S_UPPER_DEPS += \
./tinyusb/hw/mcu/bridgetek/ft9xx/scripts/crt0.d 


# Each subdirectory must supply rules for building sources it contributes
tinyusb/hw/mcu/bridgetek/ft9xx/scripts/%.o: ../tinyusb/hw/mcu/bridgetek/ft9xx/scripts/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross Assembler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -x assembler-with-cpp -I"/media/leechunhei/Data/MounRiver/tinyusb/Startup" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/include" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/portable/Common" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/portable/GCC/RISC-V" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/portable/GCC/RISC-V/chip_specific_extensions/RV32I_PFIC_no_extensions" -I"/media/leechunhei/Data/MounRiver/tinyusb/FreeRTOS/portable/MemMang" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


