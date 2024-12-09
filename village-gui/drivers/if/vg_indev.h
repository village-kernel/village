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


/// @brief IndevType
enum IndevType
{
	_Button = 1,
	_Keyboard,
	_Encoder,
	_Mouse,
	_Touchpad,
};


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

	IndevData()
		:key(0),
		btnid(0),
		encdiff(0),
		state(_Released)
	{}

	void Reset()
	{
		point = Point();
		key = 0;
		btnid = 0;
		encdiff = 0;
		state = _Released;
	}
};


/// @brief GraphicsDevices
struct GraphicsDevices;


/// @brief Wedget
class Wedget;


/// @brief Indev
class Indev
{
protected:
	//Members
	IndevType type;
	bool      ready;
public:
	//Methods
	virtual void Setup(GraphicsDevices* devices) = 0;
	virtual void Exit() = 0;

	//Type Methods
	virtual void SetType(IndevType type) { this->type = type; }
	virtual IndevType GetType()          { return this->type; }

	//Ready Methods
	virtual bool IsReady()    { return this->ready; }
	virtual void SetReady()   { this->ready = true; }
	virtual void ClearReady() { this->ready = false; }

	//Mouse Methods
	virtual Wedget* Cursor() { return NULL; }

	//Data Methods
	virtual IndevData Read() = 0;
};

#endif //!__VG_INDEV_H__
