//###########################################################################
// vg_cmd_binding.cpp
// Definitions of the functions that manage command binding
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_cmd_binding.h"


/// @brief Constructor
/// @param user 
/// @param method 
RelayCommand::RelayCommand(Class* user, Method method)
{
	this->user = user;
	this->method = method;
}


/// @brief Execute
void RelayCommand::Execute(void* args)
{
	if (user) (user->*method)(args);
}
