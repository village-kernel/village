//###########################################################################
// vg_relay_cmd.cpp
// Definitions of the functions that manage relay command
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_relay_cmd.h"


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
