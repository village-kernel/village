//###########################################################################
// vk_gui_ticks.h
// Declarations of the functions that manage ticks
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_GUI_TICKS_H__
#define __VK_GUI_TICKS_H__

#include "vg_ticks.h"


/// @brief VkTicks
class VkTicks : public VgTicks
{
public:
	//Methods
	void Setup(VgDevices* devices);
	void Exit();

	//Ticks Methods
	int GetTicks();
};

#endif //!__VK_GUI_TICKS_H__
