//###########################################################################
// Console.h
// Declarations of the functions that manage console
//
// $Copyright: Copyright (C) jingwei
//###########################################################################
#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include "Kernel.h"

///Console
class Console
{
private:
	
public:
	//Methods
	Console();
	static void Initialize();
	static void Write(uint8_t* data, uint16_t size, uint16_t offset);
	static void Read(uint8_t* data, uint16_t size, uint16_t offset);
};

#endif // !__CONSOLE_H__
