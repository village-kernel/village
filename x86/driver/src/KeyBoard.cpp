//###########################################################################
// KeyBoard.cpp
// Definitions of the functions that manage key board
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "KeyBoard.h"
#include "Kernel.h"
#include "Input.h"
#include "Hardware.h"


/// @brief Constructor
KeyBoard::KeyBoard()
{
}


/// @brief Deconstructor
KeyBoard::~KeyBoard()
{
}


/// @brief KeyBoard Initialize
void KeyBoard::Initialize()
{
	interrupt.SetISR(IRQ_Keyboard_Controller, (Method)(&KeyBoard::InputHandler), this);
	work = workQueue.Create((Method)&KeyBoard::ReportHandler, this);
}


/// @brief KeyBoard Exit
void KeyBoard::Exit()
{
	interrupt.RemoveISR(IRQ_Keyboard_Controller, (Method)(&KeyBoard::InputHandler), this);
	workQueue.Delete(work);
}


/// @brief Interrupt handler
void KeyBoard::InputHandler()
{
	/* The PIC leaves us the scancode in port 0x60 */
	keycode = PortByteIn(0x60);
	workQueue.Schedule(work);
}


/// @brief Report handler
void KeyBoard::ReportHandler()
{
	if (keycode >= 0 && keycode <= 0x39)
		input.ReportKey(keycode, 1);
	else if (keycode >= 0x39 && keycode <= 0x39 + 0x80)
		input.ReportKey(keycode - 0x80, 0);
}


//Register driver
REGISTER_DRIVER(new KeyBoard(), DriverID::_miscdev, keyboard);
