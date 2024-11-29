//###########################################################################
// vg_ticks.h
// Declarations of the functions that manage ticks
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_TICKS_H__
#define __VG_TICKS_H__

#include "stddef.h"
#include "stdint.h"


/// @brief GraphicsDevices
struct GraphicsDevices;


/// @brief Ticks
class Ticks
{
public:
	//Methods
	virtual void Setup(GraphicsDevices* devices) = 0;
	virtual void Exit() = 0;

	//Ticks Methods
	virtual int GetTicks() = 0;
};

#endif //!__VG_TICKS_H__
