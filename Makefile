###########################################################################
# Makefile
# The Makefile of vk.library
#
# $Copyright: Copyright (C) village
############################################################################
ifeq ($(CONFIG_VKLIBC), y)
-include vk.library/vklibc/Makefile
-include vk.library/vklibc++/Makefile
endif
