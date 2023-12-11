TARGET = f1c200s_library
OPT = -Ofast
BUILD_DIR = output
CPU = -mcpu=arm926ej-s
FPU =
FLOAT-ABI = -mfloat-abi=soft
LDSCRIPT = program/link.lds
AS_DEFS = 
C_DEFS =  \
-D__ARM32_ARCH__=5 \
-D__ARM926EJS__ \
-D_POSIX_C_SOURCE

PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
BIN = $(CP) -O binary -S

######################################
# source
######################################
# C sources
C_SOURCES = \
$(wildcard *.c program/bootloader/*c) \
$(wildcard *.c program/f1cx00s_lib/src/*c) \
$(wildcard *.c program/hardware/src/*c) \
$(wildcard *.c program/myresource/src/**/*c) \
$(wildcard *.c program/system/src/*c) \
$(wildcard *.c program/third_party/cherryusb/class/hub/*c) \
$(wildcard *.c program/third_party/cherryusb/class/msc/*c) \
$(wildcard *.c program/third_party/cherryusb/core/*c) \
$(wildcard *.c program/third_party/cherryusb/osal/*c) \
$(wildcard *.c program/third_party/cherryusb/port/*c) \
$(wildcard *.c program/third_party/fatfs/*c) \
$(wildcard *.c program/third_party/lvgl/lvgl/demos/**/*c) \
$(wildcard *.c program/third_party/lvgl/lvgl/demos/**/**/*c) \
$(wildcard *.c program/third_party/lvgl/lvgl/porting/*c) \
$(wildcard *.c program/third_party/lvgl/lvgl/src/**/*c) \
$(wildcard *.c program/third_party/lvgl/lvgl/src/draw/sw/*c) \
$(wildcard *.c program/third_party/lvgl/lvgl/src/extra/**/**/*c) \
$(wildcard *.c program/third_party/rt-thread/bsp/*c) \
$(wildcard *.c program/third_party/rt-thread/components/libc/compilers/common/*c) \
$(wildcard *.c program/third_party/rt-thread/components/libc/compilers/newlib/*c) \
$(wildcard *.c program/third_party/rt-thread/libcpu/f1c100s/*c) \
$(wildcard *.c program/third_party/rt-thread/src/*c) \
$(wildcard *.c program/user/*c) \

# ASM sources
ASM_SOURCES = \
program/bootloader/memcmp.S \
program/bootloader/memcpy.S \
program/bootloader/memset.S \
program/bootloader/start_gcc.S \
program/third_party/rt-thread/libcpu/f1c100s/context_gcc.S \

# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES = \
-Iprogram/bootloader \
-Iprogram/f1cx00s_lib/inc \
-Iprogram/hardware/inc \
-Iprogram/myresource/inc \
-Iprogram/system/inc \
-Iprogram/third_party/cherryusb \
-Iprogram/third_party/cherryusb/class/hub \
-Iprogram/third_party/cherryusb/class/msc \
-Iprogram/third_party/cherryusb/common \
-Iprogram/third_party/cherryusb/core \
-Iprogram/third_party/cherryusb/osal \
-Iprogram/third_party/cherryusb/port \
-Iprogram/third_party/fatfs \
-Iprogram/third_party/lvgl \
-Iprogram/third_party/lvgl/lvgl/demos \
-Iprogram/third_party/lvgl/lvgl/porting \
-Iprogram/third_party/rt-thread/include \
-Iprogram/third_party/rt-thread/bsp \
-Iprogram/third_party/rt-thread/components/libc/compilers/common/include \
-Iprogram/third_party/rt-thread/libcpu/f1c100s \
-Iprogram/user

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

LIBS = -lgcc -lc -lnosys -lm -u _printf_float
LIBDIR = 

ASFLAGS	= -Xassembler -mimplicit-it=thumb -c
LDFLAGS = $(MCU) -specs=nano.specs -T $(LDSCRIPT) $(LIBDIR) $(LIBS) -nostartfiles -Xlinker --gc-sections -Wl,--cref,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections
MCFLAGS	= $(CPU) $(FPU) $(FLOAT-ABI) -std=gnu99 $(C_DEFS) -ffunction-sections -fdata-sections -Wall $(OPT) -MMD

all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin
#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.S=.o)))
vpath %.S $(sort $(dir $(ASM_SOURCES)))
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	@$(BIN) $< $@	
	@$(MKSUNXI) $@
	@echo building $(notdir $(<:.elf=.bin))

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	@$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	@echo Linking...
	@$(SZ) $@

$(BUILD_DIR)/%.o: %.S Makefile | $(BUILD_DIR)
	@$(AS) $(ASFLAGS) $(MCFLAGS) -MF"$(@:%.o=%.d)" -MT $@ -c $< -o $@
	@echo assembling $(notdir $(<:.S=.S...))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	@$(CC) $(C_INCLUDES) $(MCFLAGS) -MF "$(@:%.o=%.d)" -MT $@ -c $< -o $@
	@echo compiling $(notdir $(<:.c=.c...))
	
$(BUILD_DIR):
	@mkdir $@		

clean:
	@echo Cleaning...
	@rmdir /Q /S $(BUILD_DIR) 

write:
	@tools/sunxi-fel -p spiflash-write 0 $(BUILD_DIR)/$(TARGET).bin
	@tools/xfel reset

mktool:
	cd tools/mksunxiboot && make
	cd tools/mksunxi && make

MKSUNXI		:=tools/mksunxi

mkboot:
	@$(MKSUNXI) $(BUILD_DIR)/$(TARGET).bin
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)