###########################################################################
# Makefile
# The Top Makefile of village project
#
# $Copyright: Copyright (C) village
############################################################################
VERSION        = 0.0.7


######################################
# target
######################################
TARGET        := village


#######################################
# paths
#######################################
WORKSPACE     := .
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
# include extension library makefile
#######################################
ifneq ($(L), )
include $(L)/Makefile
endif


#######################################
# include extension module makefile
#######################################
ifneq ($(M), )
include $(M)/Makefile
endif


#######################################
# include extension application makefile
#######################################
ifneq ($(A), )
include $(A)/Makefile
endif


#######################################
# Phony rules
#######################################
.PHONY: all boot libs kernel modules apps osImage rootfs
.PHONY: clean clean-boot clean-libs clean-mods clean-apps distclean
.PHONY: menuconfig silentoldconfig


#######################################
# tasks
#######################################
# default action: build all
all:
ifeq ($(CONFIG_BOOTLOADER), y)
	$(Q)$(MAKE) boot
endif
ifeq ($(CONFIG_GENERATED_LIB), y)
	$(Q)$(MAKE) libs
endif
ifeq ($(CONFIG_KERNEL), y)
	$(Q)$(MAKE) kernel
endif
ifeq ($(CONFIG_GENERATED_MOD), y)
	$(Q)$(MAKE) modules
endif
ifeq ($(CONFIG_GENERATED_APP), y)
	$(Q)$(MAKE) apps
endif
ifeq ($(CONFIG_GENERATED_IMG), y)
	$(Q)$(MAKE) osImage
endif


#######################################
# build the bootloader
#######################################
boot:
	$(Q)$(MAKE) $(objs-boot-y)                                    \
				INCS="$(inc-boot-y)"                              \
				SRCS="$(src-boot-y)"                              \
				CFLAGS="$(CFLAGS-BOOT)"                           \
				CXXFLAGS="$(CXXFLAGS-BOOT)";
ifeq ($(CONFIG_LEGACY), y)
	$(Q)$(MAKE) $(BUILD_DIR)/$(TARGET)-boot.elf                   \
				INCS="$(inc-boot-y)"                              \
				SRCS="$(src-boot-y)"                              \
				OBJS="$(objs-boot-y)"                             \
				LIBS="$(libs-boot-y)"                             \
				LDFLAGS="$(LDFLAGS-BOOT)";
	$(Q)$(MAKE) $(BUILD_DIR)/$(TARGET)-boot.hex
	$(Q)$(MAKE) $(BUILD_DIR)/$(TARGET)-boot.bin
else ifeq ($(CONFIG_UEFI), y)
	$(Q)$(MAKE) $(BUILD_DIR)/$(TARGET)-boot.efi                   \
				INCS="$(inc-boot-y)"                              \
				SRCS="$(src-boot-y)"                              \
				OBJS="$(objs-boot-y)"                             \
				LIBS="$(libs-boot-y)"                             \
				LDFLAGS="$(LDFLAGS-BOOT)"                         \
				COPYFLAGS="$(COPYFLAGS-BOOT)";
endif


#######################################
# build the libraries
#######################################
libs: 
	$(Q)mkdir -p $(LIBS_DIR)
	$(Q)echo "#prepare libraries" > $(LIBS_DIR)/_load_.rc;
	$(Q)$(foreach name, $(libs-y),                                \
		$(MAKE) $(objs-$(name)-y)                                 \
				INCS="$(inc-y)"                                   \
				SRCS="$(src-y)";                                  \
		$(MAKE) $(LIBS_DIR)/lib$(name).a                          \
				INCS="$(inc-y)"                                   \
				SRCS="$(src-y)"                                   \
				OBJS="$(objs-$(name)-y)";                         \
		$(MAKE) $(LIBS_DIR)/lib$(name).so                         \
				INCS="$(inc-y)"                                   \
				SRCS="$(src-y)"                                   \
				OBJS="$(objs-$(name)-y)";                         \
		echo /libraries/lib$(name).so >> $(LIBS_DIR)/_load_.rc;   \
	)
	$(Q)$(foreach name, $(oslibs-y),                              \
		$(MAKE) $(objs-$(name)-y)                                 \
				INCS="$(inc-y)"                                   \
				SRCS="$(src-y)";                                  \
		$(MAKE) $(LIBS_DIR)/lib$(name).a                          \
				INCS="$(inc-y)"                                   \
				SRCS="$(src-y)"                                   \
				OBJS="$(objs-$(name)-y)";                         \
		$(MAKE) $(LIBS_DIR)/lib$(name).so                         \
				INCS="$(inc-y)"                                   \
				SRCS="$(src-y)"                                   \
				OBJS="$(objs-$(name)-y)";                         \
	)


#######################################
# build the kernel
#######################################
kernel:
	$(Q)$(MAKE) $(objs-y)                                         \
				INCS="$(inc-y)"                                   \
				SRCS="$(src-y)";
	$(Q)$(MAKE) $(BUILD_DIR)/$(TARGET)-kernel.elf                 \
				INCS="$(inc-y)"                                   \
				SRCS="$(src-y)"                                   \
				OBJS="$(objs-y)"                                  \
				LIBS="$(libs-y)"                                  \
				LDFLAGS="$(LDFLAGS-KERNEL)";
	$(Q)$(MAKE) $(BUILD_DIR)/$(TARGET)-kernel.hex
	$(Q)$(MAKE) $(BUILD_DIR)/$(TARGET)-kernel.bin


#######################################
# build the modules
#######################################
modules:
	$(Q)mkdir -p $(MODS_DIR)
	$(Q)echo "#prepare modules" > $(MODS_DIR)/_load_.rc;
	$(Q)$(foreach object, $(objs-m),                              \
		$(MAKE) $(object)                                         \
				INCS="$(inc-y)"                                   \
				SRCS="$(src-y)";                                  \
		$(MAKE) $(MODS_DIR)/$(object:.o=.mo)                      \
				INCS="$(inc-y)"                                   \
				SRCS="$(src-y)"                                   \
				OBJS="$(object)";                                 \
		echo /modules/$(object:.o=.mo) >> $(MODS_DIR)/_load_.rc;  \
	)


#######################################
# build the applications
#######################################
apps:
	$(Q)mkdir -p $(APPS_DIR)
	$(Q)$(MAKE) $(C_RUNTIME_ZERO)                                 \
				INCS="$(inc-y)"                                   \
				SRCS="$(src-y)";
	$(Q)$(foreach name, $(apps-y),                                \
		$(MAKE) $(objs-$(name)-y)                                 \
				INCS="$(inc-$(name)-y) $(inc-y)"                  \
				SRCS="$(src-$(name)-y) $(src-y)";                 \
		$(MAKE) $(APPS_DIR)/$(name).exec                          \
				INCS="$(inc-$(name)-y) $(inc-y)"                  \
				SRCS="$(src-$(name)-y) $(src-y)"                  \
				OBJS="crt0_app.o $(objs-$(name)-y)"               \
				LIBS="$(libs-$(name)-y)"                          \
				LDFLAGS="$(LDFLAGS-APP)";                         \
		if [ "$(CONFIG_CREATE_APP_HEX_FILE)" = "y" ]; then        \
			$(MAKE) $(APPS_DIR)/$(name).hex;                      \
		fi;                                                       \
		if [ "$(CONFIG_CREATE_APP_BIN_FILE)" = "y" ]; then        \
			$(MAKE) $(APPS_DIR)/$(name).bin;                      \
		fi;                                                       \
	)


#######################################
# generate the os image
#######################################
osImage:
	$(Q)echo generated village kernel image
ifeq ($(CONFIG_LEGACY), y)
	$(Q)dd if=/dev/zero                       of=$(BUILD_DIR)/village-os.img bs=512 count=2880
	$(Q)dd if=$(BUILD_DIR)/village-boot.bin   of=$(BUILD_DIR)/village-os.img bs=512 seek=0 conv=notrunc
	$(Q)dd if=$(BUILD_DIR)/village-kernel.bin of=$(BUILD_DIR)/village-os.img bs=512 seek=1 conv=notrunc
endif


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

clean-boot:
	$(Q)rm -rf $(BUILD_DIR)/village-boot

clean-libs:
ifeq ($(L), )
	$(Q)rm -rf $(LIBS_DIR)
else
	$(Q)rm -rf $(LIBS_DIR)/$(libs-y).*
	$(Q)rm -rf $(LIBS_DIR)/$(oslibs-y).*
	$(Q)rm -rf $(BUILD_DIR)/$(L)
endif

clean-mods:
ifeq ($(M), )
	$(Q)rm -rf $(MODS_DIR)
else
	$(Q)rm -rf $(MODS_DIR)/$(objs-m:.o=.mo)
	$(Q)rm -rf $(BUILD_DIR)/$(M)
endif

clean-apps:
ifeq ($(A), )
	$(Q)rm -rf $(APPS_DIR)
	$(Q)rm -rf $(BUILD_DIR)/village-os/applications
else
	$(Q)rm -rf $(APPS_DIR)/$(apps-y).*
	$(Q)rm -rf $(BUILD_DIR)/$(A)
endif

distclean: clean
	$(Q)$(MAKE) -C $(Scripts)/kconfig clean
