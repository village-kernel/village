//###########################################################################
// InputService.h
// Declarations of the input service
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __INPUT_SERVICE_H__
#define __INPUT_SERVICE_H__

#include "Kernel.h"


/// @brief InputService
class InputService : public Class
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
	void InputKeyCallBack(InputEvent::InputKey* input);
	void InputAxisCallBack(InputEvent::InputAxis* input);
public:
	//Methods
	InputService();
	~InputService();
	void Setup();
	void Execute();
	void Exit();
};

#endif //!__INPUT_SERVICE_H__
