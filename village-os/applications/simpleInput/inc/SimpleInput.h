//###########################################################################
// SimpleInput.h
// The overall framework of the simple input method
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __SIMPLE_INPUT_METHOD_H__
#define __SIMPLE_INPUT_METHOD_H__

#include "DrvStream.h"
#include "Kernel.h"


/// @brief SimpleInput
class SimpleInput : public Class
{
private:
	//Members
	DrvStream keyboarddrv;
	DrvStream mousedrv;

	//Members
	bool isCapsLock;
	bool isShiftPressed;

	//Methods
	void InputKeyHandler(InputEvent::InputKey* input);
	void InputAxisHandler(InputEvent::InputAxis* input);
public:
	//Methods
	SimpleInput();
	~SimpleInput();
	void Setup(const char* keyboard, const char* mouse);
	void Execute();
};

#endif //!__SIMPLE_INPUT_METHOD_H__
