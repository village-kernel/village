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
	virtual ~Cmd() {};

	//Methods
	virtual void Initialize()                    = 0;
	virtual void Execute(int argc, char* argv[]) = 0;
};

#endif //!__CMD_INTERFACE_H__
