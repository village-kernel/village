//###########################################################################
// vg_indev.h
// Declarations of the functions that manage indev
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_INDEV_H__
#define __VG_INDEV_H__

#include "vg_data.h"


/// @brief Indev
class Indev
{
public:
	//Methods
	virtual void Setup() = 0;
	virtual void Exit() = 0;

	//Data Methods
	virtual void Read(IndevData* data) = 0;
};

#endif //!__VG_INDEV_H__
