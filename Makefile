###########################################################################
# Makefile
# The Top Makefile of village-target project
#
# $Copyright: Copyright (C) village
############################################################################
-include .config

######################################
# target
######################################
TARGET := village

######################################
# building variables
######################################
# optimization
OPT ?= $(CONFIG_OPT:"%"=%)

# debug build?
ifeq ($(CONFIG_DEBUG), y)
  DEBUG ?= 1
else
  DEBUG ?= 0
endif

# silence build
ifeq ($(CONFIG_VERBOSE_MODE), y)
  Q = 
else
  Q = @
endif

export Q


#######################################
# paths
#######################################
# Build path
BUILD_DIR     := vk.build
APPS_DIR      := $(BUILD_DIR)/applications
MODULES_DIR   := $(BUILD_DIR)/modules
LIBRARIES_DIR := $(BUILD_DIR)/libraries

# Rootfs path
ROOTFS_DIR    ?= $(CONFIG_ROOTFS:"%"=%)


######################################
# include other makefile
######################################
-include vk.application/Makefile
-include vk.bootloader/Makefile
-include vk.kernel/Makefile
-include vk.gui/Makefile
-include vk.filesystem/Makefile
-include vk.network/Makefile
-include vk.library/Makefile
-include vk.hardware/Makefile



#######################################
# tasks
#######################################
# default action: build all
all:
ifeq ($(CONFIG_GENERATED_LIB), y)
	$(Q)$(MAKE) library
endif
ifeq ($(CONFIG_BOOTSECTION), y)
	$(Q)$(MAKE) bootsection
endif
ifeq ($(CONFIG_BOOTLOADER), y)
	$(Q)$(MAKE) bootloader
endif
ifeq ($(CONFIG_KERNEL), y)
	$(Q)$(MAKE) kernel
endif
ifeq ($(CONFIG_GENERATED_MOD), y)
	$(Q)$(MAKE) module
endif
ifeq ($(CONFIG_GENERATED_APP), y)
	$(Q)$(MAKE) application
endif
ifeq ($(CONFIG_GENERATED_IMG), y)
	$(Q)$(MAKE) osImage
endif


# flash firmware
flash:
	openocd $(FLASH_CFG) -c "program $(BUILD_DIR)/village-kernel.bin verify reset exit 0x08000000"


#######################################
# cross compile tool
#######################################
GCC_PREFIX ?= $(CONFIG_CROSS_COMPILE:"%"=%)
CXX = $(GCC_PREFIX)g++
CC  = $(GCC_PREFIX)gcc
AS  = $(GCC_PREFIX)gcc -x assembler-with-cpp
AR  = $(GCC_PREFIX)ar
LD  = $(GCC_PREFIX)ld
CP  = $(GCC_PREFIX)objcopy
SZ  = $(GCC_PREFIX)size
ST  = $(GCC_PREFIX)strip
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S


#######################################
# setting build environment
#######################################
INCLUDES  = $(addprefix -I, $(inc-y) $(inc-m))
VPATH     = $(addprefix $(BUILD_DIR)/, $(src-y) $(src-m)) $(LIBRARIES_DIR) $(src-y) $(src-m)
LIBS      = -L$(LIBRARIES_DIR) $(addprefix -l, $(libs-y))


#######################################
# compiler flags
#######################################
ifeq ($(DEBUG), 1)
CFLAGS    += -g -gdwarf-2 -DDEBUG
endif

ifneq ($(CONFIG_ENVIRONMENT), y)
CFLAGS    += -DKBUILD_NO_ENVIRONNEMNT
endif


#######################################
# mixed compiling
#######################################
%.o: %.s
	$(Q)echo Compiling $@
	$(Q)mkdir -p $(BUILD_DIR)/$(dir $<)
	$(Q)$(AS) -c $(CFLAGS) $< -o $(BUILD_DIR)/$(dir $<)/$@

%.o: %.c
	$(Q)echo Compiling $@
	$(Q)mkdir -p $(BUILD_DIR)/$(dir $<)
	$(Q)$(CC) -c $(CFLAGS) $< -o $(BUILD_DIR)/$(dir $<)/$@

%.o: %.cpp
	$(Q)echo Compiling $@
	$(Q)mkdir -p $(BUILD_DIR)/$(dir $<)
	$(Q)$(CXX) -c $(CXXFLAGS) $< -o $(BUILD_DIR)/$(dir $<)/$@

%.hex: %.elf
	$(Q)echo output $@
	$(Q)$(HEX) $< $@

%.bin: %.elf
	$(Q)echo output $@
	$(Q)$(BIN) $< $@


#######################################
# build the libraries
#######################################
library: 
	$(Q)mkdir -p $(LIBRARIES_DIR)
	$(Q)$(foreach name, $(libs-y), \
		$(MAKE) $(objs-$(name)-y); \
		$(MAKE) $(LIBRARIES_DIR)/lib$(name).a  objs="$(objs-$(name)-y)"; \
		$(MAKE) $(LIBRARIES_DIR)/lib$(name).so objs="$(objs-$(name)-y)"; \
	)

$(LIBRARIES_DIR)/%.a: $(objs)
	$(Q)echo output $@
	$(Q)$(AR) rcs $@ $^

$(LIBRARIES_DIR)/%.so: $(objs)
	$(Q)echo output $@
	$(Q)$(LD) -shared -fPIC $^ -o $@


#######################################
# build the bootsection
#######################################
bootsection: $(objs-bs-y)
	$(Q)$(MAKE) $(BUILD_DIR)/$(TARGET)-bs.elf
	$(Q)$(MAKE) $(BUILD_DIR)/$(TARGET)-bs.hex
	$(Q)$(MAKE) $(BUILD_DIR)/$(TARGET)-bs.bin

$(BUILD_DIR)/$(TARGET)-bs.elf: $(objs-bs-y)
	$(Q)echo output $@
	$(Q)$(CXX) $(BSLDFLAGS) $^ -o $@
	$(Q)$(SZ) $@


#######################################
# build the bootloader
#######################################
bootloader: $(objs-bl-y)
	$(Q)$(MAKE) $(BUILD_DIR)/$(TARGET)-bl.elf
	$(Q)$(MAKE) $(BUILD_DIR)/$(TARGET)-bl.hex
	$(Q)$(MAKE) $(BUILD_DIR)/$(TARGET)-bl.bin

$(BUILD_DIR)/$(TARGET)-bl.elf: $(objs-bl-y)
	$(Q)echo output $@
	$(Q)$(CXX) $(BLDFLAGS) $^ -o $@ $(LIBS)
	$(Q)$(SZ) $@


#######################################
# build the kernel
#######################################
kernel: $(objs-y)
	$(Q)$(MAKE) $(BUILD_DIR)/$(TARGET)-kernel.elf
	$(Q)$(MAKE) $(BUILD_DIR)/$(TARGET)-kernel.hex
	$(Q)$(MAKE) $(BUILD_DIR)/$(TARGET)-kernel.bin

$(BUILD_DIR)/$(TARGET)-kernel.elf: $(objs-y)
	$(Q)echo output $@
	$(Q)$(CXX) $(KLDFLAGS) $^ -o $@ $(LIBS)
	$(Q)$(SZ) $@


#######################################
# build the modules
#######################################
module:
	$(Q)mkdir -p $(MODULES_DIR)
	$(Q)$(foreach object, $(objs-m), \
		$(MAKE) $(object); \
		$(MAKE) $(MODULES_DIR)/$(object:.o=.mo) objs="$(object)"; \
	)

$(MODULES_DIR)/%.mo: $(objs)
	$(Q)echo output $@
	$(Q)$(LD) -shared -fPIC $^ -o $@
	$(Q)$(SZ) $@


#######################################
# build the applications
#######################################
application: 
	$(Q)mkdir -p $(APPS_DIR)
	$(Q)$(foreach name, $(apps-y), \
		$(MAKE) $(objs-$(name)-y); \
		$(MAKE) $(APPS_DIR)/$(name).exec objs="$(objs-$(name)-y)" libs="$(libs-$(name)-y)"; \
	)

$(APPS_DIR)/%.exec: $(objs)
	$(Q)echo output $@
	$(Q)$(CXX) $(APPLDFLAGS) $^ -o $@ -L$(LIBRARIES_DIR) $(addprefix -l, $(libs))
	$(Q)$(SZ) $@


#######################################
# generate the os image
#######################################
osImage:
	$(Q)echo generated village kernel image
	$(Q)dd if=/dev/zero                       of=$(BUILD_DIR)/village-os.img bs=512 count=2880
	$(Q)dd if=$(BUILD_DIR)/village-bs.bin     of=$(BUILD_DIR)/village-os.img bs=512 seek=0 conv=notrunc
#	$(Q)dd if=$(BUILD_DIR)/village-bl.bin     of=$(BUILD_DIR)/village-os.img bs=512 seek=1 conv=notrunc
	$(Q)dd if=$(BUILD_DIR)/village-kernel.bin of=$(BUILD_DIR)/village-os.img bs=512 seek=1 conv=notrunc


#######################################
# copy to rootfs
#######################################
rootfs:
	$(Q)mkdir -p $(ROOTFS_DIR)/applications $(ROOTFS_DIR)/libraries $(ROOTFS_DIR)/modules
	$(Q)cp -rf $(BUILD_DIR)/applications/*.exec $(ROOTFS_DIR)/applications
	$(Q)cp -rf $(BUILD_DIR)/libraries/*.so      $(ROOTFS_DIR)/libraries
	$(Q)cp -rf $(BUILD_DIR)/modules/*.mo        $(ROOTFS_DIR)/modules
	

#######################################
# menuconfig
#######################################
Scripts      := ./vk.scripts
Kconfig      := ./Kconfig

menuconfig: $(Scripts)/kconfig/mconf
	$(Q)$< $(Kconfig)

silentoldconfig: $(Scripts)/kconfig/conf
	$(Q)mkdir -p include/config include/generated
	$(Q)$< -s --$@ $(Kconfig)

$(Scripts)/kconfig/mconf:
	$(Q)$(MAKE) -C $(Scripts)/kconfig

$(Scripts)/kconfig/conf:
	$(Q)$(MAKE) -C $(Scripts)/kconfig


#######################################
# clean up
#######################################
clean:
	$(Q)rm -rf $(BUILD_DIR)
	$(Q)rm -rf $(MODULES_DIR)
	$(Q)rm -rf include

clean-mod:
	$(Q)rm -rf $(MODULES_DIR)

clean-app:
	$(Q)rm -rf $(APPS_DIR)
	$(Q)rm -rf $(BUILD_DIR)/vk.application

distclean: clean
	$(Q)$(MAKE) -C $(Scripts)/kconfig clean
