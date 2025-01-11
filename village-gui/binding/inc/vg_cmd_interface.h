//###########################################################################
// vg_cmd_interface.h
// Declarations of the functions that manage command interface
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_COMMAND_INTERFACE_H__
#define __VG_COMMAND_INTERFACE_H__

#include "stdint.h"
#include "vk_class.h"

/// @brief ICommand
class ICommand
{
public:
	//Destructor
	virtual ~ICommand() {}

	//Methods
	virtual void Execute(void* args = NULL) = 0;
};

#endif //!__VG_COMMAND_INTERFACE_H__
