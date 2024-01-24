###########################################################################
# Makefile
# The Makefile of vk.kernel
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# libraries
######################################
libs-$(CONFIG_GUI)                      += graphics


######################################
# paths
######################################
inc-$(CONFIG_GUI)                       += vk.graphics/core/inc
inc-$(CONFIG_GUI)                       += vk.graphics/font/inc
inc-$(CONFIG_GUI)                       += vk.graphics/wedget/inc

src-$(CONFIG_GUI)                       += vk.graphics/core/src
src-$(CONFIG_GUI)                       += vk.graphics/wedget/src


######################################
# objects
######################################
objs-graphics-$(CONFIG_GUI)             += Graphics.o
objs-graphics-$(CONFIG_GUI)             += Display.o

objs-graphics-$(CONFIG_GUI)             += Wedget.o
objs-graphics-$(CONFIG_GUI_BUTTON)      += Button.o
objs-graphics-$(CONFIG_GUI_CURSOR)      += Cursor.o
objs-graphics-$(CONFIG_GUI_FRAME)       += Frame.o
objs-graphics-$(CONFIG_GUI_LABEL)       += Label.o
objs-graphics-$(CONFIG_GUI_LISTBOX)     += ListBox.o
objs-graphics-$(CONFIG_GUI_MENU)        += Menu.o
objs-graphics-$(CONFIG_GUI_MSGBOX)      += MsgBox.o
objs-graphics-$(CONFIG_GUI_TABBAR)      += Tabbar.o
objs-graphics-$(CONFIG_GUI_TEXTBOX)     += TextBox.o
objs-graphics-$(CONFIG_GUI_TOOLBAR)     += Toolbar.o
objs-graphics-$(CONFIG_GUI_WINDOW)      += Window.o
