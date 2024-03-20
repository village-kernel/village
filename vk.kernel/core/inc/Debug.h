//###########################################################################
// Debug.h
// Declarations of the debug
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "Component.h"


/// @brief Debug
class Debug : public Component
{
public:
	//Debug level
	enum Level
	{
		_Lv0 = 0,
		_Lv1,
		_Lv2,
		_Lv3,
		_Lv4,
		_Lv5
	};
public:
	//Methods
	virtual void Log(const char* format, ...) = 0;
	virtual void Info(const char* format, ...) = 0;
	virtual void Error(const char* format, ...) = 0;
	virtual void Warn(const char* format, ...) = 0;
	virtual void Output(int level, const char* format, ...) = 0;
	virtual void SetDebugLevel(int level) = 0;
};

#endif //!__DEBUG_H__
