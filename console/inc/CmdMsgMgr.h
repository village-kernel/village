//###########################################################################
// CmdMsgMgr.h
//
// Decodes incoming bytes into messages and Encodes outgoing messages
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __COMMAND_MSG_MGR_H__
#define __COMMAND_MSG_MGR_H__

#include "System.h"
#include "CmdDefines.h"
#include "VirtualSerial.h"

//CmdMsg struct
struct CmdMsg
{
	uint8_t* cmd;
	uint8_t* args;
};


///CmdMsg
class CmdMsgMgr
{
private:
	//Static constants
	static const uint16_t cmd_buffer_size = 20;
	static const uint16_t arg_buffer_size = 256;

	//Members
	CmdMsg rxMsg;
	VirtualSerial* transceiver;
	uint16_t txBufPos;
	uint16_t rxBufPos;
	uint8_t cmdBuffer[cmd_buffer_size] = { 0 };
	uint8_t txBuffer[arg_buffer_size] = { 0 };
	uint8_t rxBuffer[arg_buffer_size] = { 0 };

	//Methods
	bool DecodeRxBytes();
public:
	//Methods
	CmdMsgMgr();
	void Initialize(VirtualSerial* transceiver);
	bool Execute();
	void Write(uint8_t* txMsg, uint16_t size = 0);

	///Gets the decoded message
	inline CmdMsg Read() { return rxMsg; }
};

#endif //!__COMMAND_MSG_MGR_H__
