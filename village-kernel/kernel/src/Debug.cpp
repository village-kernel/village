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


/// @brief Constructor
ConcreteDebug::ConcreteDebug()
	:isReady(false),
	debugLevel(_Lv2),
	txBufPos(0)
{
}


/// @brief Destructor
ConcreteDebug::~ConcreteDebug()
{
}


/// @brief Setup
void ConcreteDebug::Setup()
{
	//Get transceiver driver and initialize
	transceiver.Open("serial0", FileMode::_Write);

	//Set ready flag
	isReady = true;

	//Output debug info
	Info("Debug setup done!");
}


/// @brief Exit
void ConcreteDebug::Exit()
{
	//Close transceiver
	transceiver.Close();

	//Clear ready flag
	isReady = false;
}


/// @brief Write
/// @param data 
void ConcreteDebug::Write(const char* data)
{
	//Calculate the string length
	int size = strlen((const char*)data);

	//When the device is not ready and the buffer is full, 
	//the previous part of the data is discarded.
	if (!isReady && ((buf_size - txBufPos) < size))
	{
		//Calculate how much data needs to be discarded
		int delta = size - (buf_size - txBufPos);

		//Discard specified amount of data
		for (int i = 0; i < buf_size - delta; i++)
		{
			txBuffer[i] = txBuffer[i + delta];
		}

		//Update txBufPos
		txBufPos -= delta;
	}

	//Copy msg data into txBuffer
	for (int i = 0; i < size; i++)
	{
		//The txBuffer is full, block here until the data is sent
		if (txBufPos >= buf_size) Sending();

		//Copy data
		txBuffer[txBufPos++] = data[i];
	}

	//Sending msg
	Sending();
}


/// @brief Sent data when txbuffer not empty
/// @brief Reset txBufPos when sent data successfully
void ConcreteDebug::Sending()
{
	if (isReady && txBufPos)
	{
		while (txBufPos != transceiver.Write(txBuffer, txBufPos)) {}
		txBufPos = 0;
	}
}


/// @brief Debug log
/// @param format 
/// @param  
void ConcreteDebug::Log(const char* format, ...)
{
	mutex.Lock();
	va_list arg;
	va_start(arg, format);
	vsnprintf(data, buf_size, format, arg);
	va_end(arg);
	Write("Log: ");
	Write(data);
	Write("\r\n");
	mutex.Unlock();
}


/// @brief Debug info
/// @param format 
/// @param  
void ConcreteDebug::Info(const char* format, ...)
{
	mutex.Lock();
	va_list arg;
	va_start(arg, format);
	vsnprintf(data, buf_size, format, arg);
	va_end(arg);
	Write("\033[36m[Info] ");
	Write(data);
	Write("\r\n\033[39m");
	mutex.Unlock();
}


/// @brief Debug error
/// @param format 
/// @param  
void ConcreteDebug::Error(const char* format, ...)
{
	mutex.Lock();
	va_list arg;
	va_start(arg, format);
	vsnprintf(data, buf_size, format, arg);
	va_end(arg);
	Write("\033[31m[Error] ");
	Write(data);
	Write("\r\n\033[39m");
	mutex.Unlock();
}


/// @brief Debug warn
/// @param format 
/// @param  
void ConcreteDebug::Warn(const char* format, ...)
{
	mutex.Lock();
	va_list arg;
	va_start(arg, format);
	vsnprintf(data, buf_size, format, arg);
	va_end(arg);
	Write("\033[33m[Warning] ");
	Write(data);
	Write("\r\n\033[39m");
	mutex.Unlock();
}


/// @brief Debug output
/// @param format 
/// @param  
void ConcreteDebug::Output(int level, const char* format, ...)
{
	if (level >= debugLevel)
	{
		mutex.Lock();
		va_list arg;
		va_start(arg, format);
		vsnprintf(data, buf_size, format, arg);
		va_end(arg);
		Write("\033[36m[Debug] ");
		Write(data);
		Write("\r\n\033[39m");
		mutex.Unlock();
	}
}


/// @brief Debug set debug level
/// @param level 
void ConcreteDebug::SetDebugLevel(int level)
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
