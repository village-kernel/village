//###########################################################################
// vg_input_cmd.h
// Declarations of the functions that manage input command
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_INPUT_COMMAND_H__
#define __VG_INPUT_COMMAND_H__

#include "stdint.h"
#include "vk_class.h"

/// @brief ICommand
class ICommand
{
public:
	//Methods
	virtual void Execute(void* args) = 0;
};

#endif //!__VG_INPUT_COMMAND_H__
