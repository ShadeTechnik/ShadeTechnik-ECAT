TARGET = shade-ecat

# lol
INC_DIRS = $(shell find . \( -name Inc -o -name Include -o -name Legacy \) | sed 's/^/-I/')
#$(info Found include directories $(INC_DIRS))

SRC = $(shell find . -name '*.c')

BIN_DIR = bin/

# It's bring your own linker scripts and startup assembly to work day.
# And also put them in the correct directory! TODO: needs smarts?
ASM = $(wildcard Core/Startup/*.[Ss]) $(wildcard ./*.[Ss])
LD_SCRIPT = $(wildcard ./*_FLASH.ld)

OBJ_DIR = obj/
OBJ     := $(SRC:%.c=$(OBJ_DIR)%.o)
ASM_OBJ := $(ASM:%.s=$(OBJ_DIR)%.o)

CC      = arm-none-eabi-gcc
LD      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
RM      = rm -rf
MKDIR   = @mkdir -p $(@D)
DEPENDS = ${OBJ:.o=.d}

CFLAGS += \
	$(INC_DIRS) \
	-mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb \
	-std=gnu11 -g3 -O0 -DDEBUG \
	-Wall -Wextra -Werror=vla -Wno-unused-parameter \
	-DUSE_HAL_DRIVER -DSTM32F446xx --specs=nano.specs \
	-ffunction-sections -fdata-sections -fstack-usage


LDFLAGS += \
	-mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb \
	-T$(LD_SCRIPT) --specs=nosys.specs --specs=nano.specs -static \
		-Wl,-Map=$(BIN_DIR)$(TARGET).map \
		-Wl,--gc-sections \
		-Wl,--start-group -lc -lm -Wl,--end-group

ASMFLAGS += \
	-mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb \
	-g3 -DDEBUG -C -x assembler-with-cpp --specs=nano.specs

all: $(BIN_DIR)/$(TARGET).bin

$(OBJ_DIR)%.o: %.c
	$(MKDIR)
	$(CC) -o $@ $(CFLAGS) -c $<

$(OBJ_DIR)%.o: %.s
	$(MKDIR)
	$(CC) $(ASMFLAGS) -o $@ -c $<

$(BIN_DIR)/$(TARGET).elf: $(OBJ) $(ASM_OBJ)
	$(MKDIR)
	$(LD) -o $@ $^ $(LDFLAGS)

$(BIN_DIR)/$(TARGET).bin: $(BIN_DIR)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@

clean:
	-$(RM) $(OBJ_DIR)
	-$(RM) $(BIN_DIR)

.PHONY: all clean

-include $(DEPENDS)
