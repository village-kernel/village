//###########################################################################
// vg_graphics.h
// Declarations of the functions that manage village graphics
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_GRAPHICS_H__
#define __VG_GRAPHICS_H__

#include "vg_data.h"
#include "vg_timer.h"
#include "vg_input.h"
#include "vg_group.h"
#include "vg_display.h"


/// @brief VkGraphics
class VkGraphics
{
public:
	//Members
	GraphicsData     databus;
	GraphicsTimer    timer;
	GraphicsInput    input;
	GraphicsGroup    group;
	GraphicsDisplay  display;
public:
	//Methods
	VkGraphics();
	~VkGraphics();
	void Setup();
	void Execute();
	void Exit();
};

#endif //!__VG_GRAPHICS_H__
