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
#include "PS2Controller.cpp"

/// @brief Mouse
class Mouse : public Driver
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
				workQueue.Schedule(work);
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
			input.ReportEvent(0xf1, 1);
		}
		else if (!packet.leftBtn && isLeftBtnPressed)
		{
			isLeftBtnPressed = false;
			input.ReportEvent(0xf1, 0);
		}

		//Report right button
		if (packet.rightBtn && !isRightBtnPressed)
		{
			isRightBtnPressed = true;
			input.ReportEvent(0xf2, 1);
		}
		else if (!packet.rightBtn && isRightBtnPressed)
		{
			isRightBtnPressed = false;
			input.ReportEvent(0xf2, 0);
		}

		//Report middle button
		if (packet.middleBtn && !isMiddleBtnPressed)
		{
			isMiddleBtnPressed = true;
			input.ReportEvent(0xf3, 1);
		}
		else if (!packet.middleBtn && isMiddleBtnPressed)
		{
			isMiddleBtnPressed = false;
			input.ReportEvent(0xf3, 0);
		}

		//Report axis x, y, z movement value
		int axisX = (int16_t)packet.x - (packet.xSignBit ? 0x100 : 0);
		int axisY = (int16_t)packet.y - (packet.ySignBit ? 0x100 : 0);
		int axisZ = (int8_t)packet.z;
		input.ReportMovement(axisX, axisY, axisZ);
	}
public:
	/// @brief Constructor
	Mouse()
		:ack(0),
		config(0),
		mouseid(0),
		isLeftBtnPressed(false),
		isRightBtnPressed(false),
		isMiddleBtnPressed(false)
	{
	}


	/// @brief Deconstructor
	~Mouse()
	{
	}


	/// @brief Mouse initialize
	void Initialize()
	{
		//Set interrupt service
		interrupt.SetISR(IRQ_Mouse_Controller, (Method)&Mouse::InputHandler, this);
		work = workQueue.Create((Method)&Mouse::ReportHandler, this);

		//Config
		ConfigureMouse();
	}


	/// @brief Mouse exit
	void Exit()
	{
		interrupt.RemoveISR(IRQ_Mouse_Controller, (Method)(&Mouse::InputHandler), this);
		workQueue.Delete(work);
	}
};


//Register driver
REGISTER_DRIVER(new Mouse(), DriverID::_miscdev + 1, ps2mouse);
