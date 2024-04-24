//###########################################################################
// Input.h
// The overall framework of the keyboard
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __INPUT_H__
#define __INPUT_H__

#include "Keyboard.h"
#include "Mouse.h"

/// @brief Input
class Input
{
private:
	//Members
	Keyboard keyboard;
	Mouse    mouse;
public:
	//Methods
	Input();
	~Input();
	void Initialize(const char* keyboard, const char* mouse);
	void Execute();
};

#endif //!__INPUT_H__
