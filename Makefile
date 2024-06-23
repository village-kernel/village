###########################################################################
# Makefile
# The Top Makefile of village project
#
# $Copyright: Copyright (C) village
############################################################################
VERSION = 0.0.7


######################################
# target
######################################
TARGET := village


#######################################
# paths
#######################################
# Build path
WORKSPACE     := $(shell pwd)
BUILD_DIR     := $(WORKSPACE)/build
MODS_DIR      := $(BUILD_DIR)/output/modules
LIBS_DIR      := $(BUILD_DIR)/output/libraries
APPS_DIR      := $(BUILD_DIR)/output/applications


#######################################
# include other makefile
#######################################
include $(WORKSPACE)/Makefile.rules
include $(WORKSPACE)/village-boot/Makefile
include $(WORKSPACE)/village-kernel/Makefile
include $(WORKSPACE)/village-os/Makefile


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
	$(Q)$(MAKE) boot
endif
ifeq ($(CONFIG_GENERATED_APP), y)
	$(Q)$(MAKE) app
endif
ifeq ($(CONFIG_GENERATED_IMG), y)
	$(Q)$(MAKE) osImage
endif


#######################################
# build the libraries
#######################################
library: 
	$(Q)mkdir -p $(LIBS_DIR)
	$(Q)echo "#prepare libraries" > $(LIBS_DIR)/_load_.rc;
	$(Q)$(foreach name, $(libs-y), \
		$(MAKE) $(objs-$(name)-y) inc="$(inc-y)" src="$(src-y)"; \
		$(MAKE) $(LIBS_DIR)/lib$(name).a  inc="$(inc-y)" src="$(src-y)" objs="$(objs-$(name)-y)"; \
		$(MAKE) $(LIBS_DIR)/lib$(name).so inc="$(inc-y)" src="$(src-y)" objs="$(objs-$(name)-y)"; \
		echo /libraries/lib$(name).so >> $(LIBS_DIR)/_load_.rc; \
	)
	$(Q)$(foreach name, $(oslibs-y), \
		$(MAKE) $(objs-$(name)-y) inc="$(inc-y)" src="$(src-y)";  \
		$(MAKE) $(LIBS_DIR)/lib$(name).a  inc="$(inc-y)" src="$(src-y)" objs="$(objs-$(name)-y)"; \
		$(MAKE) $(LIBS_DIR)/lib$(name).so inc="$(inc-y)" src="$(src-y)" objs="$(objs-$(name)-y)"; \
	)


#######################################
# build the modules
#######################################
module:
	$(Q)mkdir -p $(MODS_DIR)
	$(Q)echo "#prepare modules" > $(MODS_DIR)/_load_.rc;
	$(Q)$(foreach object, $(objs-m), \
		$(MAKE) $(object) inc="$(inc-y)" src="$(src-y)"; \
		$(MAKE) $(MODS_DIR)/$(object:.o=.mo) inc="$(inc-y)" src="$(src-y)" objs="$(object)"; \
		echo /modules/$(object:.o=.mo) >> $(MODS_DIR)/_load_.rc; \
	)


#######################################
# build the kernel
#######################################
kernel:
	$(Q)$(MAKE) $(objs-y) inc="$(inc-y)" src="$(src-y)"
	$(Q)$(MAKE) $(BUILD_DIR)/$(TARGET)-kernel.elf \
		inc="$(inc-y)"    \
		src="$(src-y)"    \
		objs="$(objs-y)"  \
		libs="$(libs-y)"  \
		LDFLAGS="$(KLDFLAGS)";
	$(Q)$(MAKE) $(BUILD_DIR)/$(TARGET)-kernel.hex
	$(Q)$(MAKE) $(BUILD_DIR)/$(TARGET)-kernel.bin


#######################################
# build the bootloader
#######################################
boot:
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
ifeq ($(CONFIG_GENERATED_STATIC_APP), y)
APPLDFLAGS += -Wl,-static
endif

app:
	$(Q)mkdir -p $(APPS_DIR)
	$(Q)$(MAKE) crt0_app.o inc="$(inc-y)" src="$(src-y)"
	$(Q)$(foreach name, $(apps-y),          \
		$(MAKE) $(objs-$(name)-y)           \
		inc="$(inc-y) $(inc-$(name)-y)"     \
		src="$(src-y) $(src-$(name)-y)";    \
		$(MAKE) $(APPS_DIR)/$(name).exec    \
		inc="$(inc-y) $(inc-$(name)-y)"     \
		src="$(src-y) $(src-$(name)-y)"     \
		objs="crt0_app.o $(objs-$(name)-y)" \
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
	$(Q)cp -rf $(BUILD_DIR)/output/*    $(CONFIG_ROOTFS:"%"=%)/


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

clean-lib:
	$(Q)rm -rf $(LIBS_DIR)

clean-mod:
	$(Q)rm -rf $(MODS_DIR)

clean-boot:
	$(Q)rm -rf $(BUILD_DIR)/village-boot

clean-app:
	$(Q)rm -rf $(APPS_DIR)
	$(Q)rm -rf $(BUILD_DIR)/village-os/applications

distclean: clean
	$(Q)$(MAKE) -C $(Scripts)/kconfig clean
