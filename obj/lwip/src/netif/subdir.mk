################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwip/src/netif/bridgeif.c \
../lwip/src/netif/bridgeif_fdb.c \
../lwip/src/netif/ethernet.c \
../lwip/src/netif/lowpan6.c \
../lwip/src/netif/lowpan6_ble.c \
../lwip/src/netif/lowpan6_common.c \
../lwip/src/netif/slipif.c \
../lwip/src/netif/zepif.c 

OBJS += \
./lwip/src/netif/bridgeif.o \
./lwip/src/netif/bridgeif_fdb.o \
./lwip/src/netif/ethernet.o \
./lwip/src/netif/lowpan6.o \
./lwip/src/netif/lowpan6_ble.o \
./lwip/src/netif/lowpan6_common.o \
./lwip/src/netif/slipif.o \
./lwip/src/netif/zepif.o 

C_DEPS += \
./lwip/src/netif/bridgeif.d \
./lwip/src/netif/bridgeif_fdb.d \
./lwip/src/netif/ethernet.d \
./lwip/src/netif/lowpan6.d \
./lwip/src/netif/lowpan6_ble.d \
./lwip/src/netif/lowpan6_common.d \
./lwip/src/netif/slipif.d \
./lwip/src/netif/zepif.d 


# Each subdirectory must supply rules for building sources it contributes
lwip/src/netif/%.o: ../lwip/src/netif/%.c
	@	@	riscv-none-embed-gcc -march=rv32imafcxw -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -DCFG_TUSB_MCU=OPT_MCU_CH32V307 -DCFG_TUSB_OS=OPT_OS_FREERTOS -I"D:\MounRiver\tinyusb\Debug" -I"D:\MounRiver\tinyusb\Core" -I"D:\MounRiver\tinyusb\User" -I"D:\MounRiver\tinyusb\Peripheral\inc" -I"D:\MounRiver\tinyusb\FreeRTOS" -I"D:\MounRiver\tinyusb\FreeRTOS\include" -I"D:\MounRiver\tinyusb\FreeRTOS\portable\Common" -I"D:\MounRiver\tinyusb\FreeRTOS\portable\GCC\RISC-V" -I"D:\MounRiver\tinyusb\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -I"D:\MounRiver\tinyusb\FreeRTOS\portable\MemMang" -I"D:\MounRiver\tinyusb\tinyusb\src" -I"D:\MounRiver\tinyusb\lwip\src\include" -I"D:\MounRiver\tinyusb\tinyusb\lib\networking" -I"D:\MounRiver\tinyusb\lwip\port" -I"D:\MounRiver\tinyusb\lwip\src\include\lwip\apps" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

