//###########################################################################
// Mouse.h
// The overall framework of the Mouse
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __MOUSE_H__
#define __MOUSE_H__

#include "DrvStream.h"

/// @brief Mouse
class Mouse
{
private:
	//Members
	DrvStream mousedrv;
public:
	//Methods
	Mouse();
	~Mouse();
	void Initialize(const char* mouse);
	void Execute();
};

#endif //!__MOUSE_H__
