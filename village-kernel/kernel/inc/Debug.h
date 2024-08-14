//###########################################################################
// Debug.h
// Declarations of the debug
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "Kernel.h"
#include "Mutex.h"
#include "DrvStream.h"


/// @brief ConcreteDebug
class ConcreteDebug : public Debug
{
private:
	/// @brief Static constants
	static const uint16_t buf_size = 256;

	/// @brief Members
	DrvStream transceiver;
	Mutex     mutex;
	bool      isReady;
	uint8_t   debugLevel;
	uint16_t  txBufPos;
	char      data[buf_size] = { 0 };
	char      txBuffer[buf_size] = { 0 };

	/// @brief Methods
	void Write(const char* data);
	void Sending();
public:
	/// @brief Methods
	ConcreteDebug();
	~ConcreteDebug();
	void Setup();
	void Exit();

	/// @brief Methods
	void Log(const char* format, ...);
	void Info(const char* format, ...);
	void Error(const char* format, ...);
	void Warn(const char* format, ...);
	void Output(int level, const char* format, ...);
	void SetDebugLevel(int level);
};

#endif //!__DEBUG_H__
