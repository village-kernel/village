//###########################################################################
// Module.h
// Specifies the interface for all classes that contain module logic
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __MODULE_INTERFACE_H__
#define __MODULE_INTERFACE_H__

#include "Defines.h"
#include "Templates.h"

///Module
class Module : public Class
{
public:
	//Constructor
	Module() {}

	//Deconstructor
	virtual ~Module() {}

	//Methods
	virtual void Initialize()       {}
	virtual void UpdateParams()     {}
	virtual void Execute()          {}
	virtual void FailSafe(int arg)  {}
};

#endif // !__MODULE_INTERFACE_H__
