//###########################################################################
// vk_cmd.h
// Specifies the interface for all classes that contain command
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_CMD_INTERFACE_H__
#define __VK_CMD_INTERFACE_H__

#include "stdint.h"
#include "stddef.h"


/// @brief Console
class Console;


/// @brief Cmd
class Cmd
{
protected:
	//Members
	Console* console;
public:
	//Constructor
	Cmd() {}
	
	//Deconstructor
	virtual ~Cmd() {}
	
	/// @brief Setup
	virtual void Setup(Console* console) 
	{
		this->console = console;
	}

	/// @brief Exit
	virtual void Exit() {}

	//Methods
	virtual void Execute(int argc, char* argv[]) = 0;
	virtual void Help() = 0;
};

#endif //!__VK_CMD_INTERFACE_H__
