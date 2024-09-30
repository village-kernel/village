###########################################################################
# Makefile
# The Makefile of vk.kernel
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# libraries
######################################
oslibs-$(CONFIG_VKGUI)                  += vkgui


######################################
# paths
######################################
inc-$(CONFIG_VKGUI)                     += village-os/libraries/vkgui/core/inc
inc-$(CONFIG_VKGUI)                     += village-os/libraries/vkgui/font/inc
inc-$(CONFIG_VKGUI)                     += village-os/libraries/vkgui/wedget/inc

src-$(CONFIG_VKGUI)                     += village-os/libraries/vkgui/core/src
src-$(CONFIG_VKGUI)                     += village-os/libraries/vkgui/wedget/src


######################################
# objects
######################################
objs-vkgui-$(CONFIG_VKGUI)              += VkGUI.o
objs-vkgui-$(CONFIG_VKGUI)              += Display.o

objs-vkgui-$(CONFIG_VKGUI)              += Wedget.o
objs-vkgui-$(CONFIG_VKGUI_BUTTON)       += Button.o
objs-vkgui-$(CONFIG_VKGUI_CURSOR)       += Cursor.o
objs-vkgui-$(CONFIG_VKGUI_FRAME)        += Frame.o
objs-vkgui-$(CONFIG_VKGUI_LABEL)        += Label.o
objs-vkgui-$(CONFIG_VKGUI_LISTBOX)      += ListBox.o
objs-vkgui-$(CONFIG_VKGUI_MENU)         += Menu.o
objs-vkgui-$(CONFIG_VKGUI_MSGBOX)       += MsgBox.o
objs-vkgui-$(CONFIG_VKGUI_TABBAR)       += Tabbar.o
objs-vkgui-$(CONFIG_VKGUI_TEXTBOX)      += TextBox.o
objs-vkgui-$(CONFIG_VKGUI_TOOLBAR)      += Toolbar.o
objs-vkgui-$(CONFIG_VKGUI_WINDOW)       += Window.o
