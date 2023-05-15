//###########################################################################
// CmdMsgMgr.cpp
//
// Decodes incoming bytes into messages and Encodes outgoing messages
//
// $Copyright: Copyright (C) village
//############################################################################
#include "CmdMsgMgr.h"
#include "Device.h"
#include "string.h"


///Constructor
CmdMsgMgr::CmdMsgMgr()
	:txBufPos(0),
	rxBufPos(0),
	inputMode(_EDIT)
{
	rxMsg.cmd = cmdBuffer;
	rxMsg.args = rxBuffer;
}


///CmdMsgMgr initialize
void CmdMsgMgr::Initialize()
{
	transceiver = device.GetDriver(DriverID::_serial);
}


///CmdMsgMgr execute
bool CmdMsgMgr::Execute()
{
	if (NULL == transceiver) return false;

	//Sent data when txbuffer not empty
	//Reset txBufPos when sent data successfully
	if (txBufPos && transceiver->Write(txBuffer, txBufPos)) txBufPos = 0;

	//Received data and decode
	transceiver->Execute();
	return HandleInputData();
}


///CmdMsgMgr write
void CmdMsgMgr::Write(uint8_t* msg, uint16_t size)
{
	if (NULL == transceiver) return;

	size = (0 == size) ? strlen((const char*)msg) : size;

	for (int i = 0; i < size; i++)
	{
		txBuffer[txBufPos++] = msg[i];
	}
}


///CmdMsgMgr Handle input data
bool CmdMsgMgr::HandleInputData()
{
	if (NULL == transceiver) return false;

	const uint8_t br_buf_size = 20;
	uint8_t brBuff[br_buf_size] = { 0 };
	uint8_t brSize = 0;

	while ((brSize = transceiver->Read(brBuff, br_buf_size)) > 0)
	{
		for (uint8_t i = 0; i < brSize; i++)
		{
			uint8_t byte = brBuff[i++];

			if (rxBufPos >= arg_buffer_size)
			{
				rxBufPos = 0;
				return false;
			}

			switch (inputMode)
			{
				case _EDIT:
				{
					//ANSI ESC
					if ('\033' == byte)
					{
						inputMode = _ANSI;
					}

					//ASCII 32(space) ~ 126(~)
					else if (byte >= 0x20 && byte <= 0x7e)
					{
						txBuffer[txBufPos++] = byte;
						rxBuffer[rxBufPos++] = byte;
					}

					//ASCII DEL
					else if (0x7f == byte)
					{
						if (rxBufPos)
						{
							rxBufPos--;
							txBuffer[txBufPos++] = byte;
						}
					}

					//ASCII CR
					else if (0x0d == byte)
					{
						//String terminator
						rxBuffer[rxBufPos++] = '\0';

						//Enter and new line
						txBuffer[txBufPos++] = '\r';
						txBuffer[txBufPos++] = '\n';

						//Check rxBufPos
						if (rxBufPos <= 1)
						{
							rxBufPos = 0;
							return false; 
						}

						//Set command
						for (uint16_t i = 0; i <= rxBufPos ; i++)
						{
							if ((' '  == rxBuffer[i]) ||
								('\r' == rxBuffer[i]) ||
								(  i  == rxBufPos   ))
							{
								cmdBuffer[i] = '\0'; break;
							}

							cmdBuffer[i] = rxBuffer[i];
						}

						//Reset rxBufPos
						rxBufPos = 0;
						return true;
					}
				}
				break;

				case _ANSI:
				{
					switch (byte)
					{
						case 'N': //ESC N | 0x8e | SS2 – Single Shift Two
							break;
						case 'O': //ESC O | 0x8f | SS3 – Single Shift Three
							break;
						case 'P': //ESC P | 0x90 | DCS – Device Control String
							inputMode = _DCS;
							break;
						case '[': //ESC [ | 0x9b | CSI - Control Sequence Introducer
							inputMode = _CSI;
							break;
						case '\\'://ESC \ | 0x9c | ST – String Terminator
							break;
						case ']': //ESC ] | 0x9d | OSC – Operating System Command
							inputMode = _OSC;
							break;
						case 'X': //ESC X | 0x98 | SOS – Start of String
							break;
						case '^': //ESC ^ | 0x9e | PM – Privacy Message
							break;
						case '_': //ESC _ | 0x9f | APC – Application Program Command
							break;
						case 'c': //ESC c |      | RIS – Reset to Initial State
							break;
						default: break;
					}
				}
				break;

				case _DCS:
				{
					
				}
				break;

				case _CSI:
				{
					//Param byte
					if (byte >= 0x30 && byte <= 0x3f)
					{

					}

					//Middle byte
					if (byte >= 0x20 && byte <= 0x2f)
					{

					}

					//Final byte
					if (byte >= 0x40 && byte <= 0x7e)
					{
						switch (byte)
						{
							case 'A': //up
								break;
							case 'B': //down
								break;
							case 'C': //right
								break;
							case 'D': //left
								break;
							case 'm': //SGR
								break;
							default: break;
						}

						inputMode = _EDIT;
					}
				}
				break;

				case _OSC:
				{
					if ('\0' == byte) inputMode = _EDIT;
				}
				break;

				default: break;
			}
		}
	}

	return false;
}
