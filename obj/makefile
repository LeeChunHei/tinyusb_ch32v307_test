################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include tinyusb/src/portable/wch/ch32v307/subdir.mk
-include tinyusb/src/portable/valentyusb/eptri/subdir.mk
-include tinyusb/src/portable/ti/msp430x5xx/subdir.mk
-include tinyusb/src/portable/template/subdir.mk
-include tinyusb/src/portable/synopsys/dwc2/subdir.mk
-include tinyusb/src/portable/sunxi/subdir.mk
-include tinyusb/src/portable/st/synopsys/subdir.mk
-include tinyusb/src/portable/st/stm32_fsdev/subdir.mk
-include tinyusb/src/portable/sony/cxd56/subdir.mk
-include tinyusb/src/portable/renesas/usba/subdir.mk
-include tinyusb/src/portable/raspberrypi/rp2040/subdir.mk
-include tinyusb/src/portable/raspberrypi/pio_usb/subdir.mk
-include tinyusb/src/portable/ohci/subdir.mk
-include tinyusb/src/portable/nxp/transdimension/subdir.mk
-include tinyusb/src/portable/nxp/lpc_ip3511/subdir.mk
-include tinyusb/src/portable/nxp/lpc17_40/subdir.mk
-include tinyusb/src/portable/nxp/khci/subdir.mk
-include tinyusb/src/portable/nuvoton/nuc505/subdir.mk
-include tinyusb/src/portable/nuvoton/nuc121/subdir.mk
-include tinyusb/src/portable/nuvoton/nuc120/subdir.mk
-include tinyusb/src/portable/nordic/nrf5x/subdir.mk
-include tinyusb/src/portable/mindmotion/mm32/subdir.mk
-include tinyusb/src/portable/microchip/samx7x/subdir.mk
-include tinyusb/src/portable/microchip/samg/subdir.mk
-include tinyusb/src/portable/microchip/samd/subdir.mk
-include tinyusb/src/portable/microchip/pic32mz/subdir.mk
-include tinyusb/src/portable/microchip/pic/subdir.mk
-include tinyusb/src/portable/mentor/musb/subdir.mk
-include tinyusb/src/portable/espressif/esp32sx/subdir.mk
-include tinyusb/src/portable/ehci/subdir.mk
-include tinyusb/src/portable/dialog/da146xx/subdir.mk
-include tinyusb/src/portable/chipidea/ci_hs/subdir.mk
-include tinyusb/src/portable/bridgetek/ft9xx/subdir.mk
-include tinyusb/src/host/subdir.mk
-include tinyusb/src/device/subdir.mk
-include tinyusb/src/common/subdir.mk
-include tinyusb/src/class/video/subdir.mk
-include tinyusb/src/class/vendor/subdir.mk
-include tinyusb/src/class/usbtmc/subdir.mk
-include tinyusb/src/class/net/subdir.mk
-include tinyusb/src/class/msc/subdir.mk
-include tinyusb/src/class/midi/subdir.mk
-include tinyusb/src/class/hid/subdir.mk
-include tinyusb/src/class/dfu/subdir.mk
-include tinyusb/src/class/cdc/subdir.mk
-include tinyusb/src/class/bth/subdir.mk
-include tinyusb/src/class/audio/subdir.mk
-include tinyusb/src/subdir.mk
-include tinyusb/lib/networking/subdir.mk
-include lwip/src/netif/ppp/polarssl/subdir.mk
-include lwip/src/netif/ppp/subdir.mk
-include lwip/src/netif/subdir.mk
-include lwip/src/core/ipv6/subdir.mk
-include lwip/src/core/ipv4/subdir.mk
-include lwip/src/core/subdir.mk
-include lwip/src/api/subdir.mk
-include lwip/port/arch/subdir.mk
-include lwip/port/subdir.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include FreeRTOS/portable/MemMang/subdir.mk
-include FreeRTOS/portable/GCC/RISC-V/subdir.mk
-include FreeRTOS/subdir.mk
-include Debug/subdir.mk
-include Core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
tinyusb.hex \

SECONDARY_LIST += \
tinyusb.lst \

SECONDARY_SIZE += \
tinyusb.siz \


# All Target
all: tinyusb.elf secondary-outputs

# Tool invocations
tinyusb.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imafcxw -mabi=ilp32f -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -fsingle-precision-constant -Wunused -Wuninitialized  -g -T "D:\MounRiver\tinyusb\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Xlinker --print-memory-usage -Wl,-Map,"tinyusb.map" --specs=nano.specs --specs=nosys.specs -o "tinyusb.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
tinyusb.hex: tinyusb.elf
	@	riscv-none-embed-objcopy -O ihex "tinyusb.elf"  "tinyusb.hex"
	@	@
tinyusb.lst: tinyusb.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "tinyusb.elf" > "tinyusb.lst"
	@	@
tinyusb.siz: tinyusb.elf
	@	riscv-none-embed-size --format=berkeley "tinyusb.elf"
	@	@
# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) tinyusb.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
