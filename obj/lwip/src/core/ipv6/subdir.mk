################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwip/src/core/ipv6/dhcp6.c \
../lwip/src/core/ipv6/ethip6.c \
../lwip/src/core/ipv6/icmp6.c \
../lwip/src/core/ipv6/inet6.c \
../lwip/src/core/ipv6/ip6.c \
../lwip/src/core/ipv6/ip6_addr.c \
../lwip/src/core/ipv6/ip6_frag.c \
../lwip/src/core/ipv6/mld6.c \
../lwip/src/core/ipv6/nd6.c 

OBJS += \
./lwip/src/core/ipv6/dhcp6.o \
./lwip/src/core/ipv6/ethip6.o \
./lwip/src/core/ipv6/icmp6.o \
./lwip/src/core/ipv6/inet6.o \
./lwip/src/core/ipv6/ip6.o \
./lwip/src/core/ipv6/ip6_addr.o \
./lwip/src/core/ipv6/ip6_frag.o \
./lwip/src/core/ipv6/mld6.o \
./lwip/src/core/ipv6/nd6.o 

C_DEPS += \
./lwip/src/core/ipv6/dhcp6.d \
./lwip/src/core/ipv6/ethip6.d \
./lwip/src/core/ipv6/icmp6.d \
./lwip/src/core/ipv6/inet6.d \
./lwip/src/core/ipv6/ip6.d \
./lwip/src/core/ipv6/ip6_addr.d \
./lwip/src/core/ipv6/ip6_frag.d \
./lwip/src/core/ipv6/mld6.d \
./lwip/src/core/ipv6/nd6.d 


# Each subdirectory must supply rules for building sources it contributes
lwip/src/core/ipv6/%.o: ../lwip/src/core/ipv6/%.c
	@	@	riscv-none-embed-gcc -march=rv32imafcxw -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -DCFG_TUSB_MCU=OPT_MCU_CH32V307 -DCFG_TUSB_OS=OPT_OS_FREERTOS -I"D:\MounRiver\tinyusb\Debug" -I"D:\MounRiver\tinyusb\Core" -I"D:\MounRiver\tinyusb\User" -I"D:\MounRiver\tinyusb\Peripheral\inc" -I"D:\MounRiver\tinyusb\FreeRTOS" -I"D:\MounRiver\tinyusb\FreeRTOS\include" -I"D:\MounRiver\tinyusb\FreeRTOS\portable\Common" -I"D:\MounRiver\tinyusb\FreeRTOS\portable\GCC\RISC-V" -I"D:\MounRiver\tinyusb\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -I"D:\MounRiver\tinyusb\FreeRTOS\portable\MemMang" -I"D:\MounRiver\tinyusb\tinyusb\src" -I"D:\MounRiver\tinyusb\lwip\src\include" -I"D:\MounRiver\tinyusb\tinyusb\lib\networking" -I"D:\MounRiver\tinyusb\lwip\port" -I"D:\MounRiver\tinyusb\lwip\src\include\lwip\apps" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

