//###########################################################################
// InputService.cpp
// Definitions of the functions that manage input service
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "InputService.h"
#include "EventCodes.h"


/// @brief lower code table
static const char lowerCodes[0x3A] = {
	/* 0x00 */ '\0', '\033', '1',  '2',  '3',    '4',  '5',    '6',
	/* 0x08 */ '7',  '8',    '9',  '0',  '-',    '=',  '\177', '\027',
	/* 0x10 */ 'q',  'w',    'e',  'r',  't',    'y',  'u',    'i',
	/* 0x18 */ 'o',  'p',    '[',  ']',  '\015', '\0', 'a',    's',
	/* 0x20 */ 'd',  'f',    'g',  'h',  'j',    'k',  'l',    ';',
	/* 0x28 */ '\'', '`',    '\0', '\\', 'z',    'x',  'c',    'v',
	/* 0x30 */ 'b',  'n',    'm',  ',',  '.',    '/',  '\0',   '*',
	/* 0x38 */ '\0', ' ',
};


/// @brief upper codes table
static const char upperCodes[0x3A] = {
	/* 0x00 */ '\0', '\033', '!',  '@',  '#',    '$',  '%',    '^',
	/* 0x08 */ '&',  '*',    '(',  ')',  '_',    '+',  '\177', '\027',
	/* 0x10 */ 'Q',  'W',    'E',  'R',  'T',    'Y',  'U',    'I',
	/* 0x18 */ 'O',  'P',    '{',  '}',  '\015', '\0', 'A',    'S',
	/* 0x20 */ 'D',  'F',    'G',  'H',  'J',    'K',  'L',    ':',
	/* 0x28 */ '"',  '~',    '\0', '|',  'Z',    'X',  'C',    'V',
	/* 0x30 */ 'B',  'N',    'M',  '<',  '>',    '?',  '\0',   '*',
	/* 0x38 */ '\0', ' ',
};


/// @brief Constructor
InputService::InputService()
	:isCapsLock(false),
	isAltPressed(false),
	isCtrlPressed(false),
	isShiftPressed(false)
{
} 


/// @brief Destructor
InputService::~InputService()
{
}


/// @brief Setup
void InputService::Setup()
{
	//Attach input event
	kernel->inputEvent.Attach(InputEvent::_InputKey, (Method)&InputService::InputKeyCallBack, this);
	kernel->inputEvent.Attach(InputEvent::_InputAxis, (Method)&InputService::InputAxisCallBack, this);
}


/// @brief Exit
void InputService::Exit()
{
	//Detach input event
	kernel->inputEvent.Detach(InputEvent::_InputKey, (Method)&InputService::InputKeyCallBack, this);
	kernel->inputEvent.Detach(InputEvent::_InputAxis, (Method)&InputService::InputAxisCallBack, this);
}


/// @brief SpecialKeysPressed
/// @param code 
void InputService::SpecialKeysPressed(int code)
{
	switch (code)
	{
		case EventCode::_KeyUp:
			kernel->inputEvent.PushString((char*)"\033[A", 3);
			break;
		case EventCode::_KeyDown:
			kernel->inputEvent.PushString((char*)"\033[B", 3);
			break;
		case EventCode::_KeyRight:
			kernel->inputEvent.PushString((char*)"\033[C", 3);
			break;
		case EventCode::_KeyLeft:
			kernel->inputEvent.PushString((char*)"\033[D", 3);
			break;
		case EventCode::_KeyCapsLock:
			isCapsLock = !isCapsLock;
			break;
		case EventCode::_KeyLeftAlt:
		case EventCode::_KeyRightAlt:
			isAltPressed = true;
			break;
		case EventCode::_KeyLeftCtrl:
		case EventCode::_KeyRightCtrl:
			isCtrlPressed = true;
			break;
		case EventCode::_KeyLeftShift:
		case EventCode::_KeyRightShift:
			isShiftPressed = true;
			break;
		default:
			break;
	}
}


/// @brief SpecialKeysReleased
/// @param code 
void InputService::SpecialKeysReleased(int code)
{
	switch (code)
	{
		case EventCode::_KeyLeftAlt:
		case EventCode::_KeyRightAlt:
			isAltPressed = false;
			break;
		case EventCode::_KeyLeftCtrl:
		case EventCode::_KeyRightCtrl:
			isCtrlPressed = false;
			break;
		case EventCode::_KeyLeftShift:
		case EventCode::_KeyRightShift:
			isShiftPressed = false;
			break;
		default:
			break;
	}
}


/// @brief CharacterKeys
/// @param code 
void InputService::CharacterKeys(int code)
{
	if ((code > EventCode::_KeyReserved) && 
		(code <= EventCode:: _KeySpace))
	{
		char chr = lowerCodes[code];

		if (chr >= 'a' && chr <= 'z')
		{
			if (isCapsLock ^ isShiftPressed) chr = upperCodes[code];
		}
		else
		{
			if (isShiftPressed) chr = upperCodes[code];
		}

		kernel->inputEvent.PushChar(chr);
	}
}


/// @brief Input key handler
void InputService::InputKeyCallBack(InputEvent::InputKey* input)
{
	if (KeyStatus::_KeyPressed == input->status)
	{
		//Special keys pressed
		SpecialKeysPressed(input->code);

		//Character keys
		CharacterKeys(input->code);
	}
	else
	{
		//Special keys released
		SpecialKeysReleased(input->code);
	}
}


/// @brief Input axis handler
void InputService::InputAxisCallBack(InputEvent::InputAxis* input)
{
	kernel->inputEvent.PushAxis(input->axisX, input->axisY, input->axisZ);
}


/// @brief Execute
void InputService::Execute()
{
	kernel->thread.ChangeState(Thread::_Blocked);

	while(1) {}
}


/// @brief main
int main(int argc, char* argv[])
{
	InputService input;
	input.Setup();
	input.Execute();
	input.Exit();
	return 0;
}
