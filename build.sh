#!/bin/bash

if [ ! -d bin/ ]; then
	mkdir -v bin/
fi

{
	rm -v bin/*.o
	rm -v bin/ecat-firmware.bin
	rm -v bin/ecat-firmware.elf
	rm -v bin/ecat-firmware.map
} 2>> /dev/null

printf "compiling c..."
arm-none-eabi-gcc \
	-mfloat-abi=soft -mthumb -mcpu=cortex-m3 \
	--specs=nano.specs --specs=nosys.specs \
	-DSTM32F103RCTx -DSTM32 -DSTM32F1 \
	-DDEBUG -O2 -ffunction-sections -fdata-sections \
	-std=gnu11 -g3 -Wall -Wextra -Werror=vla -c \
	-o bin/src.o src/main.c || exit 2
echo ok

printf "compiling asm..."
arm-none-eabi-gcc \
	-c -x assembler-with-cpp --specs=nano.specs \
	-mcpu=cortex-m3 -mfloat-abi=soft -mthumb -MMD -MP \
	-o "bin/asm.o" \
	"Startup/startup_stm32f103rctx.s" || exit 2
echo ok

printf "linking..."
arm-none-eabi-gcc \
	-mcpu=cortex-m3 -mfloat-abi=soft -mthumb -T STM32F103RCTX_FLASH.ld \
	--specs=nosys.specs --specs=nano.specs \
	-Wl,-Map=bin/ecat-firmware.map -Wl,--gc-sections -static \
	-Wl,--start-group -lc -lm -Wl,--end-group \
	bin/asm.o bin/src.o -o bin/ecat-firmware.elf || exit 2
echo ok

rm -v bin/*.o
echo

arm-none-eabi-size bin/ecat-firmware.elf
echo

arm-none-eabi-objdump -h -S bin/ecat-firmware.elf  > bin/ecat-firmware.lst
arm-none-eabi-objcopy -v -O binary bin/ecat-firmware.elf bin/ecat-firmware.bin
