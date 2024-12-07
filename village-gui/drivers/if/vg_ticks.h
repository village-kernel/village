//###########################################################################
// vg_ticks.h
// Declarations of the functions that manage ticks
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_TICKS_H__
#define __VG_TICKS_H__

#include "vg_data.h"


/// @brief Ticks
class Ticks
{
public:
	//Methods
	virtual void Setup() = 0;
	virtual void Exit() = 0;

	//Ticks Methods
	virtual int GetTicks() = 0;
};

#endif //!__VG_TICKS_H__
