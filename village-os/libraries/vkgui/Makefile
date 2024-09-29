###########################################################################
# Makefile
# The Makefile of vk.kernel
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# libraries
######################################
oslibs-$(CONFIG_GUI)                    += vkgui


######################################
# paths
######################################
inc-$(CONFIG_GUI)                       += village-os/libraries/vkgui/core/inc
inc-$(CONFIG_GUI)                       += village-os/libraries/vkgui/font/inc
inc-$(CONFIG_GUI)                       += village-os/libraries/vkgui/wedget/inc

src-$(CONFIG_GUI)                       += village-os/libraries/vkgui/core/src
src-$(CONFIG_GUI)                       += village-os/libraries/vkgui/wedget/src


######################################
# objects
######################################
objs-vkgui-$(CONFIG_GUI)                += Graphics.o
objs-vkgui-$(CONFIG_GUI)                += Display.o

objs-vkgui-$(CONFIG_GUI)                += Wedget.o
objs-vkgui-$(CONFIG_GUI_BUTTON)         += Button.o
objs-vkgui-$(CONFIG_GUI_CURSOR)         += Cursor.o
objs-vkgui-$(CONFIG_GUI_FRAME)          += Frame.o
objs-vkgui-$(CONFIG_GUI_LABEL)          += Label.o
objs-vkgui-$(CONFIG_GUI_LISTBOX)        += ListBox.o
objs-vkgui-$(CONFIG_GUI_MENU)           += Menu.o
objs-vkgui-$(CONFIG_GUI_MSGBOX)         += MsgBox.o
objs-vkgui-$(CONFIG_GUI_TABBAR)         += Tabbar.o
objs-vkgui-$(CONFIG_GUI_TEXTBOX)        += TextBox.o
objs-vkgui-$(CONFIG_GUI_TOOLBAR)        += Toolbar.o
objs-vkgui-$(CONFIG_GUI_WINDOW)         += Window.o
