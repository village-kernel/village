//###########################################################################
// CmdRun.h
// Declarations of the functions that manage command Run
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __CMD_RUN_H__
#define __CMD_RUN_H__

#include "Cmd.h"
#include "Executor.h"


///CmdRun
class CmdRun : public Cmd
{
private:
	//Members
	Executor executor;
public:
	//Methods
	void Initialize();
	void Execute(int argc, char* argv[]);
};

#endif // !__CMD_RUN_H__
