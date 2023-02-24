//###########################################################################
// VirtualSerial.h
// Provides a simple interface to transmit and receive bytes.
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VIRTUAL_SERIAL_H__
#define __VIRTUAL_SERIAL_H__

#include "HalHeaders.h"

///VirtualSerial
class VirtualSerial
{
public:
	virtual void Initialize() {}
	virtual void Execute() {}
	virtual void ChangeBaudrate(uint32_t baudrate) = 0;
	virtual bool SendBytes(uint8_t* txData, uint16_t length, bool enaDma = true) = 0;
	virtual bool HasMessage() = 0;
	virtual bool HasBytes() = 0;
	virtual uint8_t ReadByte() = 0;
	virtual void ClearReceiveBuffer() = 0;
};

#endif // !__VIRTUAL_SERIAL_H__
