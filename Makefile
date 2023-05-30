###########################################################################
# Makefile
# The Makefile of vk.kernel
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# libraries
######################################
libs-$(CONFIG_GUI)                  += gui


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
objs-gui-$(CONFIG_GUI)              += GUI.o
objs-gui-$(CONFIG_GUI)              += Display.o

objs-gui-$(CONFIG_GUI)              += Wedget.o
objs-gui-$(CONFIG_BUTTON)           += Button.o
objs-gui-$(CONFIG_FRAME)            += Frame.o
objs-gui-$(CONFIG_LISTBOX)          += ListBox.o
objs-gui-$(CONFIG_MENU)             += Menu.o
objs-gui-$(CONFIG_MSGBOX)           += MsgBox.o
objs-gui-$(CONFIG_TOOLBAR)          += Toolbar.o
objs-gui-$(CONFIG_WINDOW)           += Window.o
