###########################################################################
# Makefile
# The Top Makefile of village project
#
# $Copyright: Copyright (C) village
############################################################################
VERSION = 0.0.5

######################################
# include config
######################################
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
BUILD_DIR     := build
APPS_DIR      := $(BUILD_DIR)/output/applications
MODULES_DIR   := $(BUILD_DIR)/output/modules
LIBRARIES_DIR := $(BUILD_DIR)/output/libraries

# Rootfs path
ROOTFS_DIR    ?= $(CONFIG_ROOTFS:"%"=%)


######################################
# include other makefile
######################################
-include village-boot/Makefile
-include village-kernel/Makefile
-include village-os/Makefile


#######################################
# tasks
#######################################
# default action: build all
all:
ifeq ($(CONFIG_GENERATED_LIB), y)
	$(Q)$(MAKE) library
endif
ifeq ($(CONFIG_GENERATED_MOD), y)
	$(Q)$(MAKE) module
endif
ifeq ($(CONFIG_KERNEL), y)
	$(Q)$(MAKE) kernel
endif
ifeq ($(CONFIG_BOOTLOADER), y)
	$(Q)$(MAKE) bootloader
endif
ifeq ($(CONFIG_GENERATED_APP), y)
	$(Q)$(MAKE) application
endif
ifeq ($(CONFIG_GENERATED_IMG), y)
	$(Q)$(MAKE) osImage
endif


#######################################
# host compile tool
#######################################
HOST_GCC_PREFIX ?= $(CONFIG_HOST_COMPILE_PREFIX:"%"=%)
HOST_GCC_SUFFIX ?= $(CONFIG_HOST_COMPILE_SUFFIX:"%"=%)
HOST_CXX = $(HOST_GCC_PREFIX)g++$(HOST_GCC_SUFFIX)
HOST_CC  = $(HOST_GCC_PREFIX)gcc$(HOST_GCC_SUFFIX)
HOST_AS  = $(HOST_GCC_PREFIX)gcc$(HOST_GCC_SUFFIX) -x assembler-with-cpp


#######################################
# cross compile tool
#######################################
GCC_PREFIX ?= $(CONFIG_CROSS_COMPILE_PREFIX:"%"=%)
GCC_SUFFIX ?= $(CONFIG_CROSS_COMPILE_SUFFIX:"%"=%)
CXX = $(GCC_PREFIX)g++$(GCC_SUFFIX)
CC  = $(GCC_PREFIX)gcc$(GCC_SUFFIX)
AS  = $(GCC_PREFIX)gcc$(GCC_SUFFIX) -x assembler-with-cpp
AR  = $(GCC_PREFIX)ar$(GCC_SUFFIX)
LD  = $(GCC_PREFIX)ld$(GCC_SUFFIX)
CP  = $(GCC_PREFIX)objcopy$(GCC_SUFFIX)
SZ  = $(GCC_PREFIX)size$(GCC_SUFFIX)
ST  = $(GCC_PREFIX)strip$(GCC_SUFFIX)
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S


#######################################
# setting build environment
#######################################
INCLUDES  += $(addprefix -I, $(inc) $(inc-y))
VPATH     += $(addprefix $(BUILD_DIR)/, $(src) $(src-y)) $(src) $(src-y)
LIBS      += -L$(LIBRARIES_DIR) $(addprefix -l, $(libs))


#######################################
# compiler flags
#######################################
ifeq ($(DEBUG), 1)
CFLAGS    += -g -gdwarf-2 -DDEBUG
endif

ifneq ($(CONFIG_ENVIRONMENT), y)
CFLAGS    += -DKBUILD_NO_ENVIRONNEMNT
endif

ifeq ($(CONFIG_GENERATED_STATIC_APP), y)
APPLDFLAGS += -Wl,-static
endif


#######################################
# build version flags
#######################################
GIT_SHA = $(shell git rev-parse HEAD)
ifneq ($(GIT_SHA), )
CXXFLAGS += -DGIT_COMMIT='"$(GIT_SHA)"'
else
CXXFLAGS += -DGIT_COMMIT='"unknown"'
endif
CXXFLAGS += -DBUILD_VER='"V$(VERSION)"'


#######################################
# mixed compiling
#######################################
%.o: %.s
	$(Q)echo Compiling $@
	$(Q)mkdir -p $(BUILD_DIR)/$(dir $<)
	$(Q)$(AS) -c $(CFLAGS) $< -o $(BUILD_DIR)/$(<:.s=.o)

%.o: %.c
	$(Q)echo Compiling $@
	$(Q)mkdir -p $(BUILD_DIR)/$(dir $<)
	$(Q)$(CC) -c $(CFLAGS) $< -o $(BUILD_DIR)/$(<:.c=.o)

%.o: %.cpp
	$(Q)echo Compiling $@
	$(Q)mkdir -p $(BUILD_DIR)/$(dir $<)
	$(Q)$(CXX) -c $(CXXFLAGS) $< -o $(BUILD_DIR)/$(<:.cpp=.o)

%.a: $(objs)
	$(Q)echo output $@
	$(Q)$(AR) rcs $@ $^

%.so: $(objs)
	$(Q)echo output $@
	$(Q)$(LD) $(MCUEM) -shared -fPIC $^ -o $@
	$(Q)$(SZ) $@

%.mo: $(objs)
	$(Q)echo output $@
	$(Q)$(LD) $(MCUEM) -shared -fPIC $^ -o $@
	$(Q)$(SZ) $@

%.elf: $(objs)
	$(Q)echo output $@
	$(Q)$(CXX) $(LDFLAGS) $^ -o $@ $(LIBS)
	$(Q)$(SZ) $@

%.hex: %.elf
	$(Q)echo output $@
	$(Q)$(HEX) $< $@

%.bin: %.elf
	$(Q)echo output $@
	$(Q)$(BIN) $< $@

%.exec: $(objs)
	$(Q)echo output $@
	$(Q)$(CXX) $(LDFLAGS) $^ -o $@ $(LIBS)
	$(Q)$(SZ) $@

%.hex: %.exec
	$(Q)echo output $@
	$(Q)$(HEX) $< $@

%.bin: %.exec
	$(Q)echo output $@
	$(Q)$(BIN) $< $@


#######################################
# build the libraries
#######################################
library: 
	$(Q)mkdir -p $(LIBRARIES_DIR)
	$(Q)echo "#prepare libraries" > $(LIBRARIES_DIR)/_load_.rc;
	$(Q)$(foreach name, $(libs-y), \
		$(MAKE) $(objs-$(name)-y); \
		$(MAKE) $(LIBRARIES_DIR)/lib$(name).a  objs="$(objs-$(name)-y)"; \
		$(MAKE) $(LIBRARIES_DIR)/lib$(name).so objs="$(objs-$(name)-y)"; \
		echo /libraries/lib$(name).so >> $(LIBRARIES_DIR)/_load_.rc; \
	)
	$(Q)$(foreach name, $(oslibs-y), \
		$(MAKE) $(objs-$(name)-y);   \
		$(MAKE) $(LIBRARIES_DIR)/lib$(name).a  objs="$(objs-$(name)-y)"; \
		$(MAKE) $(LIBRARIES_DIR)/lib$(name).so objs="$(objs-$(name)-y)"; \
	)


#######################################
# build the modules
#######################################
module:
	$(Q)mkdir -p $(MODULES_DIR)
	$(Q)echo "#prepare modules" > $(MODULES_DIR)/_load_.rc;
	$(Q)$(foreach object, $(objs-m), \
		$(MAKE) $(object); \
		$(MAKE) $(MODULES_DIR)/$(object:.o=.mo) objs="$(object)"; \
		echo /modules/$(object:.o=.mo) >> $(MODULES_DIR)/_load_.rc; \
	)


#######################################
# build the kernel
#######################################
kernel: $(objs-y)
	$(Q)$(MAKE) $(BUILD_DIR)/$(TARGET)-kernel.elf \
		objs="$(objs-y)"  \
		libs="$(libs-y)"  \
		LDFLAGS="$(KLDFLAGS)";
	$(Q)$(MAKE) $(BUILD_DIR)/$(TARGET)-kernel.hex
	$(Q)$(MAKE) $(BUILD_DIR)/$(TARGET)-kernel.bin


#######################################
# build the bootloader
#######################################
bootloader:
	$(Q)$(MAKE) $(objs-boot-y) \
		inc="$(inc-boot-y)"    \
		src="$(src-boot-y)";
	$(Q)$(MAKE) $(BUILD_DIR)/$(TARGET)-boot.elf \
		inc="$(inc-boot-y)"    \
		src="$(src-boot-y)"    \
		objs="$(objs-boot-y)"  \
		libs="$(libs-boot-y)"  \
		LDFLAGS="$(BLDFLAGS)";
	$(Q)$(MAKE) $(BUILD_DIR)/$(TARGET)-boot.hex
	$(Q)$(MAKE) $(BUILD_DIR)/$(TARGET)-boot.bin


#######################################
# build the applications
#######################################
application: crt0_app.o
	$(Q)mkdir -p $(APPS_DIR)
	$(Q)$(foreach name, $(apps-y),          \
		$(MAKE) $(objs-$(name)-y)           \
		inc="$(inc-$(name)-y)"              \
		src="$(src-$(name)-y)";             \
		$(MAKE) $(APPS_DIR)/$(name).exec    \
		inc="$(inc-$(name)-y)"              \
		src="$(src-$(name)-y)"              \
		objs="crt0_app.o $(objs-$(name)-y)"  \
		libs="$(libs-$(name)-y)"            \
		LDFLAGS="$(APPLDFLAGS)";            \
	)
ifeq ($(CONFIG_CREATE_APP_HEX_FILE), y)
	$(Q)$(foreach name, $(apps-y), $(MAKE) $(APPS_DIR)/$(name).hex;)
endif
ifeq ($(CONFIG_CREATE_APP_BIN_FILE), y)
	$(Q)$(foreach name, $(apps-y), $(MAKE) $(APPS_DIR)/$(name).bin;)
endif


#######################################
# generate the os image
#######################################
osImage:
	$(Q)echo generated village kernel image
	$(Q)dd if=/dev/zero                       of=$(BUILD_DIR)/village-os.img bs=512 count=2880
	$(Q)dd if=$(BUILD_DIR)/village-boot.bin   of=$(BUILD_DIR)/village-os.img bs=512 seek=0 conv=notrunc
	$(Q)dd if=$(BUILD_DIR)/village-kernel.bin of=$(BUILD_DIR)/village-os.img bs=512 seek=1 conv=notrunc


#######################################
# copy to rootfs
#######################################
rootfs:
	$(Q)cp -rf $(BUILD_DIR)/output/*    $(ROOTFS_DIR)/
	

#######################################
# menuconfig
#######################################
Scripts      := ./village-scripts
Kconfig      := ./Kconfig

menuconfig: $(Scripts)/kconfig/mconf
	$(Q)$< $(Kconfig)

silentoldconfig: $(Scripts)/kconfig/conf
	$(Q)mkdir -p include/config include/generated
	$(Q)$< -s --$@ $(Kconfig)

$(Scripts)/kconfig/mconf:
	$(Q)$(MAKE) -C $(Scripts)/kconfig HOST_CC=$(HOST_CC)

$(Scripts)/kconfig/conf:
	$(Q)$(MAKE) -C $(Scripts)/kconfig HOST_CC=$(HOST_CC)


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
	$(Q)rm -rf $(APPS_DIR) $(BUILD_DIR)/village-os/applications

distclean: clean
	$(Q)$(MAKE) -C $(Scripts)/kconfig clean
