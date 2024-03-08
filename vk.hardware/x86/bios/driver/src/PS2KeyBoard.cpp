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
	Interrupt* interrupt;
	WorkQueue* workQueue;
	WorkQueue::Work* work;
private:
	/// @brief Interrupt handler
	void InputHandler()
	{
		if (PortByteIn(PS2_READ_STATUS) & PS2_STATUS_OUTPUT_BUFFER)
		{
			keycode = PortByteIn(PS2_READ_DATA);
			workQueue->Sched(work);
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
	}
public:
	/// @brief Constructor
	KeyBoard()
		:keycode(0),
		input(NULL),
		interrupt(NULL),
		workQueue(NULL),
		work(NULL)
	{
	}


	/// @brief Destructor
	~KeyBoard()
	{
	}


	/// @brief KeyBoard open
	int Open()
	{
		//Get the input module
		input = (Input*)kernel->modular->GetModule("input");
		if (NULL == input)
		{
			kernel->debug->Error("input feature not support");
			return _ERR;
		}

		//Get the interrupt module
		interrupt = (Interrupt*)kernel->modular->GetModule("interrupt");
		if (NULL == interrupt)
		{
			kernel->debug->Error("interrupt feature not support");
			return _ERR;
		}

		//Get the work queue module
		workQueue = (WorkQueue*)kernel->modular->GetModule("workQueue");
		if (NULL == workQueue)
		{
			kernel->debug->Error("work queue feature not support");
			return _ERR;
		}

		//Create work
		work = workQueue->Create((Method)&KeyBoard::ReportHandler, this);

		//Set interrupt
		interrupt->SetISR(IRQ_Keyboard_Controller, (Method)(&KeyBoard::InputHandler), this);

		return _OK;
	}


	/// @brief KeyBoard close
	void Close()
	{
		interrupt->RemoveISR(IRQ_Keyboard_Controller, (Method)(&KeyBoard::InputHandler), this);
		workQueue->Delete(work);
	}
};


//Register driver
REGISTER_DRIVER(KeyBoard, DriverID::_miscdev, ps2keyboard);
