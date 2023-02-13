################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/croutine.c \
../FreeRTOS/event_groups.c \
../FreeRTOS/list.c \
../FreeRTOS/queue.c \
../FreeRTOS/stream_buffer.c \
../FreeRTOS/tasks.c \
../FreeRTOS/timers.c 

OBJS += \
./FreeRTOS/croutine.o \
./FreeRTOS/event_groups.o \
./FreeRTOS/list.o \
./FreeRTOS/queue.o \
./FreeRTOS/stream_buffer.o \
./FreeRTOS/tasks.o \
./FreeRTOS/timers.o 

C_DEPS += \
./FreeRTOS/croutine.d \
./FreeRTOS/event_groups.d \
./FreeRTOS/list.d \
./FreeRTOS/queue.d \
./FreeRTOS/stream_buffer.d \
./FreeRTOS/tasks.d \
./FreeRTOS/timers.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/%.o: ../FreeRTOS/%.c
	@	@	riscv-none-embed-gcc -march=rv32imafcxw -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -DCFG_TUSB_MCU=OPT_MCU_CH32V307 -DCFG_TUSB_OS=OPT_OS_FREERTOS -I"D:\MounRiver\tinyusb\Debug" -I"D:\MounRiver\tinyusb\Core" -I"D:\MounRiver\tinyusb\User" -I"D:\MounRiver\tinyusb\Peripheral\inc" -I"D:\MounRiver\tinyusb\FreeRTOS" -I"D:\MounRiver\tinyusb\FreeRTOS\include" -I"D:\MounRiver\tinyusb\FreeRTOS\portable\Common" -I"D:\MounRiver\tinyusb\FreeRTOS\portable\GCC\RISC-V" -I"D:\MounRiver\tinyusb\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -I"D:\MounRiver\tinyusb\FreeRTOS\portable\MemMang" -I"D:\MounRiver\tinyusb\tinyusb\src" -I"D:\MounRiver\tinyusb\lwip\src\include" -I"D:\MounRiver\tinyusb\tinyusb\lib\networking" -I"D:\MounRiver\tinyusb\lwip\port" -I"D:\MounRiver\tinyusb\lwip\src\include\lwip\apps" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

