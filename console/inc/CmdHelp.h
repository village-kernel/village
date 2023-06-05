//###########################################################################
// CmdHelp.h
// Declarations of the functions that manage command help
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __CMD_HELP_H__
#define __CMD_HELP_H__

#include "Cmd.h"

///CmdHelp
class CmdHelp : public Cmd
{
public:
	//Methods
	void Initialize();
	void Execute(int argc, char* argv[]);
};

#endif // !__CMD_HELP_H__
