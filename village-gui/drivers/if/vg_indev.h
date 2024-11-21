//###########################################################################
// vg_indev.h
// Declarations of the functions that manage indev
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_INDEV_H__
#define __VG_INDEV_H__

#include "stddef.h"
#include "stdint.h"


/// @brief KeyState
enum KeyState
{
	_Released = 0,
	_Pressed,
};


/// @brief Point
struct Point
{
	int32_t x;
	int32_t y;

	Point()
		:x(0),
		y(0)
	{}
};


/// @brief IndevData
struct IndevData
{
	Point    point;
	uint32_t key;
	uint32_t btnid;
	int16_t  encdiff;
	KeyState state;
	bool     isReady;

	IndevData()
		:key(0),
		btnid(0),
		encdiff(0),
		state(_Released),
		isReady(false)
	{}
};


/// @brief Indev
class Indev
{
public:
	//Methods
	virtual void Setup() = 0;
	virtual void Exit() = 0;

	//Data Methods
	virtual IndevData* Read() = 0;
};

#endif //!__VG_INDEV_H__
