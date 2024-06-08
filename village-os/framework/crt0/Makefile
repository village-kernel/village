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
APPLDFLAGS  += $(MCU) $(LDSCRIPT-APP)
APPLDFLAGS  += -ffreestanding -nostdlib
APPLDFLAGS  += -static-libgcc
APPLDFLAGS  += -Wl,-Map=$(APPS_DIR)/$(name).map,--cref
APPLDFLAGS  += -Wl,--gc-sections
APPLDFLAGS  += -Wl,--no-warn-rwx-segment
APPLDFLAGS  += -Wl,--unresolved-symbols=ignore-in-shared-libs
APPLDFLAGS  += -pie

ifeq ($(CONFIG_X86), y)
APPLDFLAGS  += -Wl,-m,elf_i386
endif
