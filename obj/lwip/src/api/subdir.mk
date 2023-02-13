################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwip/src/api/api_lib.c \
../lwip/src/api/api_msg.c \
../lwip/src/api/err.c \
../lwip/src/api/if_api.c \
../lwip/src/api/netbuf.c \
../lwip/src/api/netdb.c \
../lwip/src/api/netifapi.c \
../lwip/src/api/sockets.c \
../lwip/src/api/tcpip.c 

OBJS += \
./lwip/src/api/api_lib.o \
./lwip/src/api/api_msg.o \
./lwip/src/api/err.o \
./lwip/src/api/if_api.o \
./lwip/src/api/netbuf.o \
./lwip/src/api/netdb.o \
./lwip/src/api/netifapi.o \
./lwip/src/api/sockets.o \
./lwip/src/api/tcpip.o 

C_DEPS += \
./lwip/src/api/api_lib.d \
./lwip/src/api/api_msg.d \
./lwip/src/api/err.d \
./lwip/src/api/if_api.d \
./lwip/src/api/netbuf.d \
./lwip/src/api/netdb.d \
./lwip/src/api/netifapi.d \
./lwip/src/api/sockets.d \
./lwip/src/api/tcpip.d 


# Each subdirectory must supply rules for building sources it contributes
lwip/src/api/%.o: ../lwip/src/api/%.c
	@	@	riscv-none-embed-gcc -march=rv32imafcxw -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -DCFG_TUSB_MCU=OPT_MCU_CH32V307 -DCFG_TUSB_OS=OPT_OS_FREERTOS -I"D:\MounRiver\tinyusb\Debug" -I"D:\MounRiver\tinyusb\Core" -I"D:\MounRiver\tinyusb\User" -I"D:\MounRiver\tinyusb\Peripheral\inc" -I"D:\MounRiver\tinyusb\FreeRTOS" -I"D:\MounRiver\tinyusb\FreeRTOS\include" -I"D:\MounRiver\tinyusb\FreeRTOS\portable\Common" -I"D:\MounRiver\tinyusb\FreeRTOS\portable\GCC\RISC-V" -I"D:\MounRiver\tinyusb\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -I"D:\MounRiver\tinyusb\FreeRTOS\portable\MemMang" -I"D:\MounRiver\tinyusb\tinyusb\src" -I"D:\MounRiver\tinyusb\lwip\src\include" -I"D:\MounRiver\tinyusb\tinyusb\lib\networking" -I"D:\MounRiver\tinyusb\lwip\port" -I"D:\MounRiver\tinyusb\lwip\src\include\lwip\apps" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

