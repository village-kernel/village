###########################################################################
# Makefile
# The Makefile of vkgui
#
# $Copyright: Copyright (C) village
############################################################################
ifeq ($(CONFIG_VKGUI), y)

######################################
# libraries
######################################
oslibs-y                                += vkgui


######################################
# paths
######################################
inc-y                                   += village-gui/binding/inc
inc-y                                   += village-gui/core/inc
inc-y                                   += village-gui/draw/inc
inc-y                                   += village-gui/drivers/if
inc-y                                   += village-gui/drivers/inc
inc-y                                   += village-gui/font/inc
inc-y                                   += village-gui/layout/inc
inc-y                                   += village-gui/misc/inc
inc-y                                   += village-gui/wedget/inc

src-y                                   += village-gui/binding/src
src-y                                   += village-gui/core/src
src-y                                   += village-gui/draw/src
src-y                                   += village-gui/drivers/src
src-y                                   += village-gui/layout/src
src-y                                   += village-gui/misc/src
src-y                                   += village-gui/wedget/src


######################################
# objects
######################################
objs-vkgui-y                            += vg_graphics.o
objs-vkgui-y                            += vg_timer.o
objs-vkgui-y                            += vg_input.o
objs-vkgui-y                            += vg_display.o
objs-vkgui-y                            += vg_object.o

objs-vkgui-y                            += vg_relay_cmd.o

objs-vkgui-y                            += vg_layer.o

objs-vkgui-y                            += vk_disp_lcddev.o
objs-vkgui-y                            += vk_event_indev.o
objs-vkgui-y                            += vk_timer_ticks.o

objs-vkgui-y                            += vg_draw_arc.o
objs-vkgui-y                            += vg_draw_image.o
objs-vkgui-y                            += vg_draw_label.o
objs-vkgui-y                            += vg_draw_line.o
objs-vkgui-y                            += vg_draw_mask.o
objs-vkgui-y                            += vg_draw_rect.o
objs-vkgui-y                            += vg_draw_triangle.o

objs-vkgui-y                            += vg_flex.o
objs-vkgui-y                            += vg_grid.o

objs-vkgui-y                            += vg_wedget.o
objs-vkgui-$(CONFIG_VKGUI_BUTTON)       += vg_button.o
objs-vkgui-$(CONFIG_VKGUI_CURSOR)       += vg_cursor.o
objs-vkgui-$(CONFIG_VKGUI_LABEL)        += vg_label.o
objs-vkgui-$(CONFIG_VKGUI_LISTBOX)      += vg_listbox.o
objs-vkgui-$(CONFIG_VKGUI_MENU)         += vg_menu.o
objs-vkgui-$(CONFIG_VKGUI_MSGBOX)       += vg_msgbox.o
objs-vkgui-$(CONFIG_VKGUI_NAVBAR)       += vg_navbar.o
objs-vkgui-$(CONFIG_VKGUI_SCROLLBAR)    += vg_scrollbar.o
objs-vkgui-$(CONFIG_VKGUI_TABBAR)       += vg_tabbar.o
objs-vkgui-$(CONFIG_VKGUI_TABLE)        += vg_table.o
objs-vkgui-$(CONFIG_VKGUI_TEXTBOX)      += vg_textbox.o
objs-vkgui-$(CONFIG_VKGUI_TOOLBAR)      += vg_toolbar.o
objs-vkgui-$(CONFIG_VKGUI_WINDOW)       += vg_window.o

endif
