//###########################################################################
// PS2Mouse.cpp
// Definitions of the functions that manage mouse
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Driver.h"
#include "Kernel.h"
#include "Hardware.h"
#include "PS2Controller.h"


/// @brief PS2Mouse
class PS2Mouse : public Driver
{
private:
	//Packet union
	union Packet
	{
		uint8_t byte[4];
		struct
		{
			//Byte 0
			uint8_t leftBtn:1;
			uint8_t rightBtn:1;
			uint8_t middleBtn:1;
			uint8_t always1:1;
			uint8_t xSignBit:1;
			uint8_t ySignBit:1;
			uint8_t xOverflow:1;
			uint8_t yOverflow:1;
			//Byte 1
			uint8_t x;
			//Byte 2
			uint8_t y;
			//Byte 3
			uint8_t z;
		} __attribute__((packed));
	};

	//Members
	uint8_t ack;
	uint8_t config;
	uint8_t mouseid;
	uint8_t count;
	Packet  packet;
	//Status members
	bool isLeftBtnPressed;
	bool isRightBtnPressed;
	bool isMiddleBtnPressed;
	//Controller members
	PS2Controller ps2;
	//Work
	InputEvent* inputevent;
	Interrupt*  interrupt;
	WorkQueue*  workQueue;
	WorkQueue::Work* work;
private:
	/// @brief Mouse write data
	/// @param data 
	/// @return ack
	uint8_t MouseWriteData(uint8_t data)
	{
		ps2.WriteCmd(PS2_CMD_WR_CTL_SEC_INPUT_BUFF);
		ps2.WriteData(data);
		return ps2.ReadData();
	}


	/// @brief Mouse read data
	/// @return data
	uint8_t MouseReadData()
	{
		return ps2.ReadData();
	}


	/// @brief Configuure mouse
	/// @return result
	bool ConfigureMouse()
	{
		//Disable irq
		kernel->system.DisableIRQ();

		//Read config
		ps2.WriteCmd(PS2_CMD_READ_BYTE_0);
		config = ps2.ReadData();
		
		//Set irq12 and ps2 clk enable flag
		config |=  (PS2_CTL_SECOND_PORT_INT);
		config &= ~(PS2_CTL_SECOND_PORT_CLK);

		//Enable irq12
		ps2.WriteCmd(PS2_CMD_WRITE_NEXT_BYTE_0);
		ps2.WriteData(config);

		//Enable second ps2 port
		ps2.WriteCmd(PS2_CMD_ENA_SEC_PS2_PORT);

		//Restore to defaults
		MouseWriteData(PS2_MOUSE_CMD_SET_DEFAULTS);

		//Init/Detection Command Sequences
		MouseWriteData(PS2_MOUSE_CMD_SET_SAMPLE_RATE);
		MouseWriteData(200);

		MouseWriteData(PS2_MOUSE_CMD_SET_SAMPLE_RATE);
		MouseWriteData(100);

		MouseWriteData(PS2_MOUSE_CMD_SET_SAMPLE_RATE);
		MouseWriteData(80);

		MouseWriteData(PS2_MOUSE_CMD_GET_DEVICE_ID);
		mouseid = MouseReadData();

		//Enable 4th and 5th mouse buttons
		if (mouseid == 3)
		{
			MouseWriteData(PS2_MOUSE_CMD_SET_SAMPLE_RATE);
			MouseWriteData(200);

			MouseWriteData(PS2_MOUSE_CMD_SET_SAMPLE_RATE);
			MouseWriteData(200);

			MouseWriteData(PS2_MOUSE_CMD_SET_SAMPLE_RATE);
			MouseWriteData(80);

			MouseWriteData(PS2_MOUSE_CMD_GET_DEVICE_ID);
			mouseid = MouseReadData();
		}

		//Set sample rate
		MouseWriteData(PS2_MOUSE_CMD_SET_SAMPLE_RATE);
		MouseWriteData(200);

		//Set resolution
		MouseWriteData(PS2_MOUSE_CMD_SET_RESOLUTION);
		MouseWriteData(3);

		//Set scaling 1:1
		MouseWriteData(PS2_MOUSE_CMD_SCALING_1_1);

		//Enable mouse
		ack = MouseWriteData(PS2_MOUSE_CMD_ENA_DATA_REPORTING);

		//Enable irq
		kernel->system.EnableIRQ();

		return (0xfa == ack);
	}


	/// @brief Mouse input handler
	void InputHandler()
	{
		if (PortByteIn(PS2_READ_STATUS) & PS2_STATUS_OUTPUT_BUFFER)
		{
			packet.byte[count] = PortByteIn(PS2_READ_DATA);

			if (++count >= mouseid)
			{
				count = 0;
				workQueue->Sched(work);
			}
		}
	}


	/// @brief Mouse report handler
	void  ReportHandler()
	{
		//Report left button
		if (packet.leftBtn && !isLeftBtnPressed)
		{
			isLeftBtnPressed = true;
			inputevent->ReportKey(0xf1, 1);
		}
		else if (!packet.leftBtn && isLeftBtnPressed)
		{
			isLeftBtnPressed = false;
			inputevent->ReportKey(0xf1, 0);
		}

		//Report right button
		if (packet.rightBtn && !isRightBtnPressed)
		{
			isRightBtnPressed = true;
			inputevent->ReportKey(0xf2, 1);
		}
		else if (!packet.rightBtn && isRightBtnPressed)
		{
			isRightBtnPressed = false;
			inputevent->ReportKey(0xf2, 0);
		}

		//Report middle button
		if (packet.middleBtn && !isMiddleBtnPressed)
		{
			isMiddleBtnPressed = true;
			inputevent->ReportKey(0xf3, 1);
		}
		else if (!packet.middleBtn && isMiddleBtnPressed)
		{
			isMiddleBtnPressed = false;
			inputevent->ReportKey(0xf3, 0);
		}

		//Report axis x, y, z movement value
		int axisX = (int16_t)packet.x - (packet.xSignBit ? 0x100 : 0);
		int axisY = (int16_t)packet.y - (packet.ySignBit ? 0x100 : 0);
		int axisZ = (int8_t)packet.z;
		inputevent->ReportLoc(axisX, axisY, axisZ);
	}
public:
	/// @brief Constructor
	PS2Mouse()
		:ack(0),
		config(0),
		mouseid(0),
		isLeftBtnPressed(false),
		isRightBtnPressed(false),
		isMiddleBtnPressed(false),
		inputevent(NULL),
		interrupt(NULL),
		workQueue(NULL),
		work(NULL)
	{
	}


	/// @brief Deconstructor
	~PS2Mouse()
	{
	}


	/// @brief Mouse open
	bool Open()
	{
		//Get the inputevent pointer
		inputevent = &kernel->inputevent;

		//Get the interrupt pointer
		interrupt = &kernel->interrupt;

		//Get the work queue pointer
		workQueue = &kernel->workqueue;

		//Create work
		work = workQueue->Create((Method)&PS2Mouse::ReportHandler, this);

		//Set interrupt service
		interrupt->SetISR(IRQ_Mouse_Controller, (Method)&PS2Mouse::InputHandler, this);

		//Config
		ConfigureMouse();

		return true;
	}


	/// @brief Mouse close
	void Close()
	{
		interrupt->RemoveISR(IRQ_Mouse_Controller, (Method)(&PS2Mouse::InputHandler), this);
		workQueue->Delete(work);
	}
};


//Register driver
REGISTER_DRIVER(new PS2Mouse(), DriverID::_character, ps2mouse);
