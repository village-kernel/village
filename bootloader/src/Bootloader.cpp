//###########################################################################
// Bootloader.cpp
// Definitions of the functions that manage bootloader
//
// $Copyright: Copyright (C) LDO Systems
//###########################################################################
#include "Kernel.h"
#include "Bootloader.h"


/// @brief Constructor
Bootloader::Bootloader()
{
}


/// @brief Test print string
/// @param string 
void printString(const char* string)
{
	char* videoMemory = (char*)0xb8000;

	for (int i = 0; 0 != string[i]; i++)
	{
		*videoMemory = string[i];
		videoMemory = videoMemory + 2;
	}
}


/// @brief Bootloader initialize
void Bootloader::Initialize()
{
	printString("Hello C world!");
}


/// @brief Bootloader execute
void Bootloader::Execute()
{
	while (1)
	{
	}
}


//Register module
REGISTER_MODULE(new Bootloader(), (ModuleID::_application + 0 ), bl);
