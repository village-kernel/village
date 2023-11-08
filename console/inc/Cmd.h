//###########################################################################
// Cmd.h
// Specifies the interface for all classes that contain command
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __CMD_INTERFACE_H__
#define __CMD_INTERFACE_H__

#include "stdint.h"
#include "stddef.h"

///Cmd
class Cmd
{
public:
	//Constructor
	Cmd() {}
	
	//Deconstructor
	virtual ~Cmd() {}

	//Methods
	virtual void Initialize() {}
	virtual void Execute(int argc, char* argv[]) = 0;
	virtual void Help() {}
};

#endif //!__CMD_INTERFACE_H__
