//###########################################################################
// Stack.h
// Specifies the interface for all classes that contain stack logic
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __STACK_INTERFACE_H__
#define __STACK_INTERFACE_H__

#include "Defines.h"
#include "Class.h"
#include "ProtDefs.h"


/// @brief Stack
class Stack : public Base, public Class
{
public:
	//Constructor
	Stack() { }

	//Destructor
	virtual ~Stack() { }

	//Methods
	virtual void Setup() = 0;
	virtual void Exit()  = 0;
};

#endif // !__STACK_INTERFACE_H__