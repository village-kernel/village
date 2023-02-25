//###########################################################################
// CmdMsgMgr.cpp
//
// Decodes incoming bytes into messages and Encodes outgoing messages
//
// $Copyright: Copyright (C) village
//############################################################################
#include "CmdMsgMgr.h"
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
void CmdMsgMgr::Initialize(VirtualSerial* transceiver)
{
	this->transceiver = transceiver;
}


///CmdMsgMgr execute
bool CmdMsgMgr::Execute()
{
	//Sent data when txbuffer not empty
	//Reset txBufPos when sent data successfully
	if (txBufPos && transceiver->SendBytes(txBuffer, txBufPos)) txBufPos = 0;

	//Received data and decode
	transceiver->Execute();
	return DecodeRxBytes();
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


///CmdMsgMgr decode rx bytes
bool CmdMsgMgr::DecodeRxBytes()
{
	while (transceiver->HasBytes())
	{
		if (rxBufPos >= arg_buffer_size)
		{
			rxBufPos = 0;
			transceiver->ClearReceiveBuffer();
			return false;
		}

		uint8_t byte = transceiver->ReadByte();

		//Control code
		if (0x1b == byte) //Ascii ESC
		{
			byte = transceiver->ReadByte();

			if (0x5b == byte)
			{
				byte = transceiver->ReadByte();
				switch (byte)
				{
					case 0x41: //up
						break;
					case 0x42: //down
						break;
					case 0x43: //right
						break;
					case 0x44: //left
						break;
					default: break;
				}
			}
		}
		else if (byte == 127) //Ascii DEL
		{
			if (rxBufPos)
			{
				rxBufPos--;
				Write(&byte, 1);
			}
		}
		else
		{
			//Ascii 32(space) ~ 126(~)
			if ((byte >= ' ') && (byte <= '~'))
			{
				rxBuffer[rxBufPos++] = byte;

				Write(&byte, 1);
			}

			//Ascii '\r'
			if ('\r' == byte)
			{
				Write((uint8_t*)"\r\n", 2);

				if (rxBufPos <= 1)
				{
					rxBufPos = 0;
					return false; 
				}

				for (int8_t i = 0; i < rxBufPos ; i++)
				{
					if ((' ' == rxBuffer[i]) || ('\r' == rxBuffer[i])) break;

					cmdBuffer[i] = rxBuffer[i];
				}

				cmdBuffer[rxBufPos] = '\0'; 

				rxBufPos = 0;
				return true;
			}
		}
	}

	return false;
}
