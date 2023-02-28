//###########################################################################
// CmdMsgMgr.cpp
//
// Decodes incoming bytes into messages and Encodes outgoing messages
//
// $Copyright: Copyright (C) village
//############################################################################
#include "CmdMsgMgr.h"
#include "IOStream.h"
#include "string.h"


///Constructor
CmdMsgMgr::CmdMsgMgr()
	:txBufPos(0),
	rxBufPos(0)
{
	rxMsg.cmd = cmdBuffer;
	rxMsg.args = rxBuffer;
}


///CmdMsgMgr initialize
void CmdMsgMgr::Initialize()
{
	
}


///CmdMsgMgr execute
bool CmdMsgMgr::Execute()
{
	//Sent data when txbuffer not empty
	//Reset txBufPos when sent data successfully
	if (txBufPos && IOStream::Write(txBuffer, txBufPos)) txBufPos = 0;

	//Received data and decode
	IOStream::Execute();
	return HandleInputData();
}


///CmdMsgMgr write
void CmdMsgMgr::Write(uint8_t* msg, uint16_t size)
{
	size = (0 == size) ? strlen((const char*)msg) : size;

	for (int i = 0; i < size; i++)
	{
		txBuffer[txBufPos++] = msg[i];
	}
}


///CmdMsgMgr Handle input data
bool CmdMsgMgr::HandleInputData()
{
	uint8_t databuff[10] = { 0 };

	while (IOStream::Read(databuff, 10))
	{
		if (rxBufPos >= arg_buffer_size)
		{
			rxBufPos = 0;
			return false;
		}

		uint8_t byte = rxBuffer[rxBufPos++];

	}

	return false;
}
