###########################################################################
# Makefile
# The Makefile of crt0
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# paths
######################################
src-y        += village-os/framework/crt0


######################################
# link script
######################################
LDSCRIPT-APP := -T village-os/framework/crt0/crt0_app.lds


#######################################
# compiler flags
#######################################
# application ld flags
LDFLAGS-APP  += $(MCU) $(LDSCRIPT-APP)
LDFLAGS-APP  += -ffreestanding -nostdlib
LDFLAGS-APP  += -static-libgcc
LDFLAGS-APP  += -Wl,-Map=$(APPS_DIR)/$(name).map,--cref
LDFLAGS-APP  += -Wl,--gc-sections
LDFLAGS-APP  += -Wl,--no-warn-rwx-segment
LDFLAGS-APP  += -Wl,--unresolved-symbols=ignore-in-shared-libs
LDFLAGS-APP  += -pie

ifeq ($(CONFIG_X86), y)
LDFLAGS-APP  += -Wl,-m,elf_i386
endif

ifeq ($(CONFIG_GENERATED_STATIC_APP), y)
LDFLAGS-APP  += -Wl,-static
endif
