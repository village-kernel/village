//###########################################################################
// KeyBoard.cpp
// Definitions of the functions that manage key board
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Input.h"
#include "Kernel.h"
#include "Hardware.h"
#include "WorkQueue.h"


/// @brief KeyBoard
class KeyBoard : public Driver
{
private:
	//Members
	uint8_t keycode;
	Input* input;
	WorkQueue* workQueue;
	WorkQueue::Work* work;
private:
	/// @brief Interrupt handler
	void InputHandler()
	{
		if (PortByteIn(PS2_READ_STATUS) & PS2_STATUS_OUTPUT_BUFFER)
		{
			keycode = PortByteIn(PS2_READ_DATA);
			workQueue->Schedule(work);
		}
	}


	/// @brief Report handler
	void ReportHandler()
	{
		//Report keycode and status
		if (keycode >= 0 && keycode <= 0x39)
			input->ReportEvent(keycode, 1);
		else if (keycode >= 0x39 && keycode <= 0x39 + 0x80)
			input->ReportEvent(keycode - 0x80, 0);

		//Notify
		input->Notify();
	}
public:
	/// @brief Constructor
	KeyBoard()
		:keycode(0),
		input(NULL),
		workQueue(NULL),
		work(NULL)
	{
	}


	/// @brief Destructor
	~KeyBoard()
	{
	}


	/// @brief KeyBoard Initialize
	void Initialize()
	{
		//Get the input module
		input = (Input*)Kernel::modular.GetModuleByName("input");
		if (NULL == input)
		{
			Kernel::debug.Error("input feature not support");
			return;
		}

		//Get the work queue module
		workQueue = (WorkQueue*)Kernel::modular.GetModuleByName("workQueue");
		if (NULL == workQueue)
		{
			Kernel::debug.Error("work queue feature not support");
			return;
		}

		//Create work
		work = workQueue->Create((Method)&KeyBoard::ReportHandler, this);

		//Set interrupt
		Kernel::interrupt.SetISR(IRQ_Keyboard_Controller, (Method)(&KeyBoard::InputHandler), this);
	}


	/// @brief KeyBoard Exit
	void Exit()
	{
		Kernel::interrupt.RemoveISR(IRQ_Keyboard_Controller, (Method)(&KeyBoard::InputHandler), this);
		workQueue->Delete(work);
	}
};


//Register driver
REGISTER_DRIVER(new KeyBoard(), DriverID::_miscdev, ps2keyboard);
