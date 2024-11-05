//###########################################################################
// vg_relay_cmd.h
// Declarations of the functions that manage relay command
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_RELAY_COMMAND_H__
#define __VG_RELAY_COMMAND_H__

#include "vg_input_cmd.h"


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
	void Execute(void* args);
};

#endif //!__VG_RELAY_COMMAND_H__
