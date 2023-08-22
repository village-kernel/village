//###########################################################################
// CmdCopy.h
// Declarations of the functions that manage command copy
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __CMD_COPY_H__
#define __CMD_COPY_H__

#include "Cmd.h"

///CmdCopy
class CmdCopy : public Cmd
{
public:
	//Methods
	void Initialize();
	void Execute(int argc, char* argv[]);
};

#endif // !__CMD_COPY_H__
