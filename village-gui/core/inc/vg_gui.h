//###########################################################################
// vg_gui.h
// Declarations of the functions that manage village gui
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_GUI_H__
#define __VG_GUI_H__

/// @brief include draw headers
#include "vg_draw_arc.h"
#include "vg_draw_image.h"
#include "vg_draw_label.h"
#include "vg_draw_line.h"
#include "vg_draw_mask.h"
#include "vg_draw_rect.h"
#include "vg_draw_triangle.h"

/// @brief include layout headers
#include "vg_flex.h"
#include "vg_grid.h"

/// @brief include wedgets headers
#include "vg_button.h"
#include "vg_label.h"
#include "vg_listbox.h"
#include "vg_menu.h"
#include "vg_msgbox.h"
#include "vg_navbar.h"
#include "vg_scrollbar.h"
#include "vg_tabbar.h"
#include "vg_table.h"
#include "vg_textbox.h"
#include "vg_toolbar.h"
#include "vg_window.h"

/// @brief include cmd headers
#include "vg_input_cmd.h"
#include "vg_relay_cmd.h"

/// @brief include grahics headers
#include "vg_devices.h"
#include "vg_timer.h"
#include "vg_input.h"
#include "vg_screen.h"
#include "vg_group.h"


/// @brief VillageGUI
class VillageGUI
{
public:
	//Members
	VgDevices  devices;
	VgTimer    timer;
	VgInput    input;
	VgScreen   screen;
	VgGroup    group;
public:
	//Methods
	VillageGUI();
	~VillageGUI();
	void Setup();
	void Execute();
	void Exit();
};

#endif //!__VG_GUI_H__
