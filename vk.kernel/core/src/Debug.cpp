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
#include "Driver.h"
#include "Mutex.h"
#include "Kernel.h"


/// @brief ConcreteDebug
class ConcreteDebug : public Debug
{
private:
	//Static constants
	static const uint16_t buf_size = 100;

	//Members
	Driver*   transceiver;
	Mutex     mutex;
	char      data[buf_size];
	uint8_t   debugLevel;
private:
	/// @brief Write
	/// @param data 
	void Write(const char* data)
	{
		if (NULL != transceiver)
		{
			 while (0 == transceiver->Write((uint8_t*)data, strlen(data))) {}
		}
	}
public:
	/// @brief Constructor
	ConcreteDebug()
		:debugLevel(_Lv2)
	{
	}


	/// @brief Destructor
	~ConcreteDebug()
	{
	}


	/// @brief Initialize
	void Initialize()
	{
		//Get transceiver driver and initialize
		transceiver = kernel->device->GetDriver("serial0");
		if (NULL != transceiver) transceiver->Initialize();
	}


	/// @brief Debug log
	/// @param format 
	/// @param  
	void Log(const char* format, ...)
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


	/// @brief Debug info
	/// @param format 
	/// @param  
	void Info(const char* format, ...)
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


	/// @brief Debug error
	/// @param format 
	/// @param  
	void Error(const char* format, ...)
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


	/// @brief Debug warn
	/// @param format 
	/// @param  
	void Warn(const char* format, ...)
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


	/// @brief Debug output
	/// @param format 
	/// @param  
	void Output(int level, const char* format, ...)
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


	/// @brief Debug set debug level
	/// @param level 
	void SetDebugLevel(int level)
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
};


///Register module
REGISTER_MODULE(ConcreteDebug, ModuleID::_debug, debug);
