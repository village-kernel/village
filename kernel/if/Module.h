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
private:
	//Members
	int pid;    //Process thread id
public:
	//Constructor
	Module(): pid(-1) {}

	//Deconstructor
	virtual ~Module() {}

	//Methods
	virtual void Initialize()       {}
	virtual void UpdateParams()     {}
	virtual void Execute()          {}
	virtual void FailSafe(int arg)  {}
	virtual void Exit()             {}
	virtual void SetPid(int pid)    { this->pid = pid; }
	virtual int  GetPid()           { return this->pid; }
};

#endif // !__MODULE_INTERFACE_H__
