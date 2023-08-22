//###########################################################################
// CmdMkdir.h
// Declarations of the functions that manage command mkdir
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __CMD_MAKE_DIR_H__
#define __CMD_MAKE_DIR_H__

#include "Cmd.h"

///CmdMkdir
class CmdMkdir : public Cmd
{
public:
	//Methods
	void Initialize();
	void Execute(int argc, char* argv[]);
};

#endif // !__CMD_MAKE_DIR_H__
