//###########################################################################
// Module.h
// Specifies the interface for all classes that contain module logic
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __MODULE_INTERFACE_H__
#define __MODULE_INTERFACE_H__

#include "Defines.h"
#include "Class.h"


/// @brief Module
class Module : public Base, public Class
{
public:
	//Constructor
	Module() { }

	//Destructor
	virtual ~Module() { }

	//Methods
	virtual bool  Setup() = 0;
	virtual void  Exit()  = 0;
	virtual void  SetData(void* data) { }
	virtual void* GetData() { return NULL; }
};

#endif // !__MODULE_INTERFACE_H__
