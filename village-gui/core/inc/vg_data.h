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
#include "vk_list.h"


/// @brief State
enum State
{
	_Released = 0,
	_Pressed,
};


/// @brief Point
struct Point
{
	int32_t x;
	int32_t y;
};


/// @brief IndevData
struct IndevData
{
	Point    point;
	uint32_t key;
	uint32_t btnid;
	int16_t  encdiff;
	State    state;
};


/// @brief DrawArea
struct DrawArea
{
	int x0;
	int y0;
	int x1;
	int y1;

	DrawArea
	(
		int x0 = 0,
		int y0 = 0,
		int x1 = 0,
		int y1 = 0
	):
		x0(x0),
		y0(y0),
		x1(x1),
		y1(y1)
	{}
};


/// @brief DrawData
struct DrawData
{
	DrawArea   area;
	uint8_t*   pixels;

	DrawData()
		:pixels(NULL)
	{}
};


/// @brief GraphicsData
struct GraphicsData
{
	int             ticks;
	IndevData       input;
	List<DrawData*> draws;

	GraphicsData()
		:ticks(0)
	{}
};

#endif //!__VG_DATA_H__
