###########################################################################
# Makefile
# The Makefile of crt0
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# paths
######################################
src-y        += village-os/libraries/crt0


######################################
# crt0
######################################
C_RUNTIME_ZERO := crt0_app.o


######################################
# link script
######################################
LDSCRIPT-OS  := -T village-os/libraries/crt0/crt0_app.lds
LDSCRIPT-APP := $(LDSCRIPT-OS) 
LDSCRIPT-SVC := $(LDSCRIPT-OS) 


#######################################
# compiler flags
#######################################
# vkos ld flags
LDFLAGS-OS  += -ffreestanding -nostdlib
LDFLAGS-OS  += -Wl,--gc-sections
LDFLAGS-OS  += -Wl,--no-warn-rwx-segment
LDFLAGS-OS  += -Wl,--unresolved-symbols=ignore-in-shared-libs
LDFLAGS-OS  += -pie

ifeq ($(CONFIG_IA32), y)
LDFLAGS-OS  += -Wl,-m,elf_i386
endif

ifeq ($(CONFIG_GENERATED_STATIC_PROG), y)
LDFLAGS-OS  += -Wl,-static
endif

# app ld flags
LDFLAGS-APP  += $(MCU) $(LDSCRIPT-APP)
LDFLAGS-APP  += -Wl,-Map=$(APPS_DIR)/$(name).map,--cref
LDFLAGS-APP  += $(LDFLAGS-OS)

# svc ld flags
LDFLAGS-SVC  += $(MCU) $(LDSCRIPT-SVC)
LDFLAGS-SVC  += -Wl,-Map=$(SVCS_DIR)/$(name).map,--cref
LDFLAGS-SVC  += $(LDFLAGS-OS)
