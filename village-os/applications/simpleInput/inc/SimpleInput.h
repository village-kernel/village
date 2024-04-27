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
	bool isUpperCase;
	char text[20] = {0};

	//Methods
	void ReadInputKey(InputEvent::InputKey* input);
	void ReadInputAxis(InputEvent::InputAxis* input);
public:
	//Methods
	SimpleInput();
	~SimpleInput();
	void Setup(const char* keyboard, const char* mouse);
	void Execute();
};

#endif //!__SIMPLE_INPUT_METHOD_H__
