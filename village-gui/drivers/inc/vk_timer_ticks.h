//###########################################################################
// vk_timer_ticks.h
// Declarations of the functions that manage ticks
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_TIMER_TICKS_H__
#define __VK_TIMER_TICKS_H__

#include "vg_ticks.h"


/// @brief VkTicks
class VkTicks : public Ticks
{
public:
	//Methods
	void Setup();
	void Exit();

	//Ticks Methods
	int GetTicks();
};

#endif //!__VK_TIMER_TICKS_H__
