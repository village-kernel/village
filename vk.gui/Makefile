###########################################################################
# Makefile
# The Makefile of vk.kernel
#
# $Copyright: Copyright (C) village
############################################################################

######################################
# libraries
######################################
libs-$(CONFIG_GUI)                      += gui


######################################
# paths
######################################
inc-$(CONFIG_GUI)                       += vk.gui/core/if
inc-$(CONFIG_GUI)                       += vk.gui/core/inc
inc-$(CONFIG_GUI)                       += vk.gui/font/inc
inc-$(CONFIG_GUI)                       += vk.gui/wedget/inc
src-$(CONFIG_GUI)                       += vk.gui/core/src
src-$(CONFIG_GUI)                       += vk.gui/wedget/src


######################################
# objects
######################################
objs-gui-$(CONFIG_GUI)                  += GUI.o
objs-gui-$(CONFIG_GUI)                  += Display.o

objs-gui-$(CONFIG_GUI)                  += Wedget.o
objs-gui-$(CONFIG_GUI_BUTTON)           += Button.o
objs-gui-$(CONFIG_GUI_CURSOR)           += Cursor.o
objs-gui-$(CONFIG_GUI_FRAME)            += Frame.o
objs-gui-$(CONFIG_GUI_LABEL)            += Label.o
objs-gui-$(CONFIG_GUI_LISTBOX)          += ListBox.o
objs-gui-$(CONFIG_GUI_MENU)             += Menu.o
objs-gui-$(CONFIG_GUI_MSGBOX)           += MsgBox.o
objs-gui-$(CONFIG_GUI_TABBAR)           += Tabbar.o
objs-gui-$(CONFIG_GUI_TEXTBOX)          += TextBox.o
objs-gui-$(CONFIG_GUI_TOOLBAR)          += Toolbar.o
objs-gui-$(CONFIG_GUI_WINDOW)           += Window.o
