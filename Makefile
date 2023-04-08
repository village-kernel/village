###########################################################################
# Makefile
# The Makefile of vk.kernel
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# paths
######################################
inc-$(CONFIG_GUI)                   += vk.gui/core/if
inc-$(CONFIG_GUI)                   += vk.gui/core/inc
inc-$(CONFIG_GUI)                   += vk.gui/font/inc
inc-$(CONFIG_GUI)                   += vk.gui/wedget/inc
src-$(CONFIG_GUI)                   += vk.gui/core/src
src-$(CONFIG_GUI)                   += vk.gui/wedget/src


######################################
# objects
######################################
objs-$(CONFIG_GUI)                  += GUI.o
objs-$(CONFIG_GUI)                  += Display.o

objs-$(CONFIG_GUI)                  += Wedget.o
objs-$(CONFIG_BUTTON)               += Button.o
objs-$(CONFIG_FRAME)                += Frame.o
objs-$(CONFIG_LISTBOX)              += ListBox.o
objs-$(CONFIG_MENU)                 += Menu.o
objs-$(CONFIG_MSGBOX)               += MsgBox.o
objs-$(CONFIG_TOOLBAR)              += Toolbar.o
objs-$(CONFIG_WINDOW)               += Window.o
