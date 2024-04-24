//###########################################################################
// Keyboard.h
// The overall framework of the keyboard
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include "DrvStream.h"

/// @brief Keyboard
class Keyboard
{
private:
	//Members
	DrvStream keyboarddrv;
public:
	//Methods
	Keyboard();
	~Keyboard();
	void Initialize(const char* keyboard);
	void Execute();
};

#endif //!__KEYBOARD_H__
