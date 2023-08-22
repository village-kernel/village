//###########################################################################
// CmdRemove.h
// Declarations of the functions that manage command remove
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __CMD_REMOVE_H__
#define __CMD_REMOVE_H__

#include "Cmd.h"

///CmdRemove
class CmdRemove : public Cmd
{
public:
	//Methods
	void Initialize();
	void Execute(int argc, char* argv[]);
};

#endif // !__CMD_REMOVE_H__
