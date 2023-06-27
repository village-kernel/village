//###########################################################################
// Debug.h
// Declarations of the debug
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "Driver.h"
#include "SyncLock.h"


/// @brief Debug
class Debug
{
public:
	//Debug level
	enum DebugLevel
	{
		_Lv0 = 0,
		_Lv1,
		_Lv2,
		_Lv3,
		_Lv4,
		_Lv5
	};
private:
	//Static constants
	static const uint16_t buf_size = 100;

	//Members
	Driver*   transceiver;
	Mutex     mutex;
	char      data[buf_size];
	uint8_t   debugLevel;

	//Methods
	Debug();
	~Debug();
	void Write(const char* data);
public:
	//Methods
	void Log(const char* format, ...);
	void Info(const char* format, ...);
	void Error(const char* format, ...);
	void Warn(const char* format, ...);
	void Output(int level, const char* format, ...);
	void SetDebugLevel(int level);
	
	//Singleton Instance
	static Debug& Instance();
};

///Declarations Debug reference
extern Debug& debug;

#endif //!__DEBUG_H__
