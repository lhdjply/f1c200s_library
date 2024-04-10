TARGET = f1c200s_library
OPT = -Ofast
BUILD_DIR = output
CPU = -mcpu=arm926ej-s
FPU =
FLOAT-ABI = -mfloat-abi=soft
LDSCRIPT = user/link.lds
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
ifdef OS
   RM = rmdir /Q /S
else
   ifeq ($(shell uname), Linux)
      RM = rm -r
   endif
endif

######################################
# source
######################################
# C sources
C_SOURCES = \
$(wildcard *.c bootloader/*.c) \
$(wildcard *.c dsp/source/**/src/*.c) \
$(wildcard *.c f1cx00s_lib/src/*.c) \
$(wildcard *.c hardware/src/*.c) \
$(wildcard *.c myresource/src/**/*.c) \
$(wildcard *.c system/src/*.c) \
$(wildcard *.c third_party/cherryusb/class/hub/*.c) \
$(wildcard *.c third_party/cherryusb/class/msc/*.c) \
$(wildcard *.c third_party/cherryusb/core/*.c) \
$(wildcard *.c third_party/cherryusb/osal/*.c) \
$(wildcard *.c third_party/cherryusb/port/*.c) \
$(wildcard *.c third_party/fatfs/*.c) \
$(wildcard *.c third_party/lvgl/lvgl/**/*.c) \
$(wildcard *.c third_party/lvgl/lvgl/**/**/*.c) \
$(wildcard *.c third_party/lvgl/lvgl/**/**/**/*.c) \
$(wildcard *.c third_party/lvgl/lvgl/**/**/**/**/*.c) \
$(wildcard *.c third_party/rt-thread/bsp/*.c) \
$(wildcard *.c third_party/rt-thread/components/libc/compilers/common/*.c) \
$(wildcard *.c third_party/rt-thread/components/libc/compilers/newlib/*.c) \
$(wildcard *.c third_party/rt-thread/libcpu/f1c100s/*.c) \
$(wildcard *.c third_party/rt-thread/src/*.c) \
$(wildcard *.c user/*.c) \

# ASM sources
ASM_SOURCES = \
bootloader/memcmp.S \
bootloader/memcpy.S \
bootloader/memset.S \
bootloader/start_gcc.S \
third_party/rt-thread/libcpu/f1c100s/context_gcc.S \

# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES = \
-Ibootloader \
-Idsp/include \
-If1cx00s_lib/inc \
-Ihardware/inc \
-Imyresource/inc \
-Isystem/inc \
-Ithird_party/cherryusb \
-Ithird_party/cherryusb/class/hub \
-Ithird_party/cherryusb/class/msc \
-Ithird_party/cherryusb/common \
-Ithird_party/cherryusb/core \
-Ithird_party/cherryusb/osal \
-Ithird_party/cherryusb/port \
-Ithird_party/fatfs \
-Ithird_party/lvgl \
-Ithird_party/lvgl/lvgl/demos \
-Ithird_party/lvgl/lvgl/porting \
-Ithird_party/rt-thread/include \
-Ithird_party/rt-thread/bsp \
-Ithird_party/rt-thread/components/libc/compilers/common/include \
-Ithird_party/rt-thread/libcpu/f1c100s \
-Iuser

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

LIBS = -lgcc -lc -lnosys -lm -u _printf_float
LIBDIR = 

NOWALL= -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast
ASFLAGS	= -Xassembler -mimplicit-it=thumb -c
LDFLAGS = $(MCU) -specs=nano.specs -T $(LDSCRIPT) $(LIBDIR) $(LIBS) -nostartfiles -Xlinker --gc-sections -Wl,--cref,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections
MCFLAGS	= $(CPU) $(FPU) $(FLOAT-ABI) -std=gnu99 $(C_DEFS) -ffunction-sections -fdata-sections -Wall $(NOWALL) $(OPT) -MMD

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
	@$(RM) $(BUILD_DIR) 

write-to-spinor:
	@echo SPI nor write
	@tools/sunxi-fel -p spiflash-write 0 $(BUILD_DIR)/$(TARGET).bin
	@tools/xfel reset

write-to-spinand:
	@echo SPI nand write
	@tools/xfel spinand splwrite 1024 0x40000 $(BUILD_DIR)/$(TARGET).bin
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