//###########################################################################
// Mouse.cpp
// Definitions of the functions that manage mouse
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Mouse.h"
#include "Kernel.h"
#include "Input.h"
#include "Hardware.h"


/// @brief Constructor
Mouse::Mouse()
	:x(0),
	y(0)
{
}


/// @brief Deconstructor
Mouse::~Mouse()
{
}


/// @brief Mouse initialize
void Mouse::Initialize()
{
	interrupt.SetISR(IRQ_Mouse_Controller, (Method)&Mouse::InputHandler, this);
	work = workQueue.Create((Method)&Mouse::ReportHandler, this);
}


/// @brief Mouse exit
void Mouse::Exit()
{

}


/// @brief Mouse input handler
void Mouse::InputHandler()
{
	/* The PIC leaves us the scancode in port 0x60 */
	flags.byte = PortByteIn(0x60);
	x = PortByteIn(0x60);
	y = PortByteIn(0x60);
	workQueue.Schedule(work);
}


/// @brief Mouse report handler
void  Mouse::ReportHandler()
{

}
