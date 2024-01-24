//###########################################################################
// Debug.cpp
// Definitions of the functions that manage debug
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "string.h"
#include "stdarg.h"
#include "stdio.h"
#include "Debug.h"
#include "Kernel.h"


/// @brief Debug constructor
Debug::Debug()
	:debugLevel(_Lv2)
{
}


/// @brief Debug deconstructor
Debug::~Debug()
{
}


/// @brief Write
/// @param data 
void Debug::Write(const char* data)
{
	//Get transceiver driver and initialize
	if (NULL == transceiver)
	{
		transceiver = Kernel::device.GetDriver("serial0");
		if (NULL != transceiver) transceiver->Initialize();
	}
	
	//Sent data
	if (NULL != transceiver) while (0 == transceiver->Write((uint8_t*)data, strlen(data))) {}
}


/// @brief Debug log
/// @param format 
/// @param  
void Debug::Log(const char* format, ...)
{
	mutex.Lock();
	va_list arg;
	va_start(arg, format);
	vsprintf(data, format, arg);
	va_end(arg);
	Write("Log: ");
	Write(data);
	Write("\r\n");
	mutex.Unlock();
}
EXPORT_SYMBOL(_ZN5Debug3LogEPKcz);


/// @brief Debug info
/// @param format 
/// @param  
void Debug::Info(const char* format, ...)
{
	mutex.Lock();
	va_list arg;
	va_start(arg, format);
	vsprintf(data, format, arg);
	va_end(arg);
	Write("\033[36mInfo: ");
	Write(data);
	Write("\r\n\033[39m");
	mutex.Unlock();
}
EXPORT_SYMBOL(_ZN5Debug4InfoEPKcz);


/// @brief Debug error
/// @param format 
/// @param  
void Debug::Error(const char* format, ...)
{
	mutex.Lock();
	va_list arg;
	va_start(arg, format);
	vsprintf(data, format, arg);
	va_end(arg);
	Write("\033[31mError: ");
	Write(data);
	Write("\r\n\033[39m");
	mutex.Unlock();
}
EXPORT_SYMBOL(_ZN5Debug5ErrorEPKcz);


/// @brief Debug warn
/// @param format 
/// @param  
void Debug::Warn(const char* format, ...)
{
	mutex.Lock();
	va_list arg;
	va_start(arg, format);
	vsprintf(data, format, arg);
	va_end(arg);
	Write("\033[33mWarning: ");
	Write(data);
	Write("\r\n\033[39m");
	mutex.Unlock();
}
EXPORT_SYMBOL(_ZN5Debug4WarnEPKcz);


/// @brief Debug output
/// @param format 
/// @param  
void Debug::Output(int level, const char* format, ...)
{
	if (level >= debugLevel)
	{
		mutex.Lock();
		va_list arg;
		va_start(arg, format);
		vsprintf(data, format, arg);
		va_end(arg);
		Write("\033[36mDebug: ");
		Write(data);
		Write("\r\n\033[39m");
		mutex.Unlock();
	}
}
EXPORT_SYMBOL(_ZN5Debug6OutputEiPKcz);


/// @brief Debug set debug level
/// @param level 
void Debug::SetDebugLevel(int level)
{
	if (level >= _Lv0 && level <= _Lv5)
	{
		debugLevel = level;
	}
	else
	{
		Error("The level %d out of debug level", level);
	}
}
EXPORT_SYMBOL(_ZN5Debug13SetDebugLevelEi);
