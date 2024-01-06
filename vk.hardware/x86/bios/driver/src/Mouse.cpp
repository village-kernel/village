//###########################################################################
// Mouse.cpp
// Definitions of the functions that manage mouse
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Input.h"
#include "Driver.h"
#include "Kernel.h"
#include "Hardware.h"
#include "WorkQueue.h"


/// @brief Mouse
class Mouse : public Driver
{
private:
	//Structures
	union Flags
	{
		struct
		{
			uint8_t yOverflow:1;
			uint8_t xOverflow:1;
			uint8_t ySignBit:1;
			uint8_t xSignBit:1;
			uint8_t always1:1;
			uint8_t middleBtn:1;
			uint8_t RightBtn:1;
			uint8_t LeftBtn:1;
		} __attribute__((packed)) bits;
		uint8_t byte;
	};

	//Members
	Flags flags;
	uint8_t x;
	uint8_t y;
	WorkQueue::Work* work;
private:
	/// @brief Mouse input handler
	void InputHandler()
	{
		/* The PIC leaves us the scancode in port 0x60 */
		flags.byte = PortByteIn(0x60);
		x = PortByteIn(0x60);
		y = PortByteIn(0x60);
		workQueue.Schedule(work);
	}


	/// @brief Mouse report handler
	void  ReportHandler()
	{

	}
public:
	/// @brief Constructor
	Mouse()
		:x(0),
		y(0)
	{
	}


	/// @brief Deconstructor
	~Mouse()
	{
	}


	/// @brief Mouse initialize
	void Initialize()
	{
		interrupt.SetISR(IRQ_Mouse_Controller, (Method)&Mouse::InputHandler, this);
		work = workQueue.Create((Method)&Mouse::ReportHandler, this);
	}


	/// @brief Mouse exit
	void Exit()
	{

	}
};


//Register driver
REGISTER_DRIVER(new Mouse(), DriverID::_miscdev, mouse);
