//###########################################################################
// vg_data.h
// Declarations of the functions that manage data bus
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_DATA_H__
#define __VG_DATA_H__

#include "stddef.h"
#include "stdint.h"
#include "vk_fifo.h"
#include "vg_indev.h"
#include "vg_draw_defs.h"


/// @brief SystemInfo
struct SystemInfo
{
	int              ticks;
	Fifo<IndevData>  input;
	Fifo<DrawData>   draws;

	/// @brief Constructor
	SystemInfo()
		:ticks(0)
	{
		input.Setup(20);
		draws.Setup(100);
	}

	/// @brief Destructor
	~SystemInfo()
	{
		input.Exit();
		draws.Exit();
	}
};

#endif //!__VG_DATA_H__
