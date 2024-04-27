//###########################################################################
// SimpleInput.cpp
// The overall framework of the simple input method
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "SimpleInput.h"
#include "EventCodes.h"


/// @brief keycode to text table
static const char code2text[0x38] = {
	/* 0x00 */ '\0', '\033', '1',  '2',  '3',    '4',  '5',    '6',
	/* 0x08 */ '7',  '8',    '9',  '0',  '-',    '=',  '\177', '\027',
	/* 0x10 */ 'q',  'w',    'e',  'r',  't',    'y',  'u',    'i',
	/* 0x18 */ 'o',  'p',    '[',  ']',  '\015', '\0', 'a',    's',
	/* 0x20 */ 'd',  'f',    'g',  'h',  'j',    'k',  'l',    ';',
	/* 0x28 */ '\'', '`',    '\0', '\\', 'z',    'x',  'c',    'v',
	/* 0x30 */ 'b',  'n',    'm',  ',',  '.',    '\0', '*',    '\0',
};


/// @brief Constructor
SimpleInput::SimpleInput()
	:isUpperCase(false)
{
} 


/// @brief Destructor
SimpleInput::~SimpleInput()
{
}


/// @brief Setup
void SimpleInput::Setup(const char* keyboard, const char* mouse)
{
	//Open keyboard and mouse
	keyboarddrv.Open(keyboard, FileMode::_Read);
	mousedrv.Open(mouse, FileMode::_Read);

	//Attach input event
	kernel->inputEvent.Attach(InputEvent::_InputKey, (Method)&SimpleInput::ReadInputKey, this);
	kernel->inputEvent.Attach(InputEvent::_InputAxis, (Method)&SimpleInput::ReadInputAxis, this);
}


/// @brief Update key
void SimpleInput::ReadInputKey(InputEvent::InputKey* input)
{
	if (input->status)
	{
		switch (input->code)
		{
			case EventCode::_KeyUp: kernel->inputEvent.PushText((char*)"\033[A", 3); break;
			case EventCode::_KeyDown: kernel->inputEvent.PushText((char*)"\033[B", 3); break;
			case EventCode::_KeyLeft: kernel->inputEvent.PushText((char*)"\033[D", 3); break;
			case EventCode::_KeyRight: kernel->inputEvent.PushText((char*)"\033[C", 3); break;
			case EventCode::_KeyCapsLock:
			case EventCode::_KeyLeftShift:
			case EventCode::_KeyRightShift: isUpperCase = !isUpperCase; break;
			default: break;
		}

		if (input->code > 0 && input->code <= 0x38)
		{
			text[0] = code2text[input->code];
			if (isUpperCase && text[0] >= 'a' && text[0] <= 'z') text[0] -= 0x20;
			kernel->inputEvent.PushText(text, 1);
		}
	}
	else
	{
		if ((EventCode::_KeyLeftShift == input->code) || 
			(EventCode::_KeyRightShift == input->code))
			isUpperCase = !isUpperCase;
	}
}


/// @brief Update location
void SimpleInput::ReadInputAxis(InputEvent::InputAxis* input)
{
	kernel->inputEvent.PushAxis(input->axisX, input->axisY, input->axisZ);
}


/// @brief Execute
void SimpleInput::Execute()
{
	while(1) {}
}


/// @brief main
int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		return -1;
	}
	else
	{
		SimpleInput input;
		input.Setup(argv[1], argv[2]);
		input.Execute();
		return 0;
	}
}
