//###########################################################################
// vg_cmd_binding.h
// Declarations of the functions that manage command binding
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_COMMAND_BINDING_H__
#define __VG_COMMAND_BINDING_H__

#include "vg_cmd_interface.h"


/// @brief RelayCommand
class RelayCommand : public ICommand
{
private:
	//Members
	Class* user;
	Method method;
public:
	//Methods
	RelayCommand(Class* user, Method method);
	void Execute(void* args = NULL);
};

#endif //!__VG_COMMAND_BINDING_H__
