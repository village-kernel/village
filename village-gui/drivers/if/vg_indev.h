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


/// @brief VgIndevType
enum VgIndevType
{
	_Button = 1,
	_Keyboard,
	_Encoder,
	_Mouse,
	_Touchpad,
};


/// @brief VgKeyState
enum VgKeyState
{
	_Released = 0,
	_Pressed,
};


/// @brief VgPoint
struct VgPoint
{
	int x;
	int y;

	VgPoint
	(
		int x = 0,
		int y = 0
	):
		x(0),
		y(0)
	{}
};


/// @brief VgInputData
struct VgInputData
{
	VgPoint    point;
	VgPoint    axis;
	uint32_t   key;
	uint32_t   btnid;
	int16_t    encdiff;
	VgKeyState state;

	VgInputData()
		:key(0),
		btnid(0),
		encdiff(0),
		state(_Released)
	{}

	void Reset()
	{
		point = VgPoint();
		axis = VgPoint();
		key = 0;
		btnid = 0;
		encdiff = 0;
		state = _Released;
	}
};


/// @brief VgDevices
struct VgDevices;


/// @brief VgWindow
class VgWindow;


/// @brief VgIndev
class VgIndev
{
protected:
	//Members
	VgIndevType type;
	bool        ready;
public:
	//Methods
	virtual void Setup(VgDevices* devices) = 0;
	virtual void Exit() = 0;

	//Type Methods
	virtual void SetType(VgIndevType type) { this->type = type; }
	virtual VgIndevType GetType()          { return this->type; }

	//Ready Methods
	virtual bool IsReady()    { return this->ready; }
	virtual void SetReady()   { this->ready = true; }
	virtual void ClearReady() { this->ready = false; }

	//Mouse Methods
	virtual VgWindow* Cursor() { return NULL; }

	//Data Methods
	virtual VgInputData Read() = 0;
};

#endif //!__VG_INDEV_H__
