//###########################################################################
// SimpleInput.h
// The overall framework of the simple input method
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __SIMPLE_INPUT_METHOD_H__
#define __SIMPLE_INPUT_METHOD_H__

#include "Kernel.h"


/// @brief SimpleInput
class SimpleInput : public Class
{
private:
	//Members
	bool isCapsLock;
	bool isAltPressed;
	bool isCtrlPressed;
	bool isShiftPressed;

	//Methods
	void SpecialKeysPressed(int code);
	void SpecialKeysReleased(int code);
	void CharacterKeys(int code);
	void InputKeyHandler(InputEvent::InputKey* input);
	void InputAxisHandler(InputEvent::InputAxis* input);
public:
	//Methods
	SimpleInput();
	~SimpleInput();
	void Setup();
	void Execute();
};

#endif //!__SIMPLE_INPUT_METHOD_H__
