//###########################################################################
// CmdCd.h
// Declarations of the functions that manage command change directory
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __CMD_CD_H__
#define __CMD_CD_H__

#include "Cmd.h"

///CmdCd
class CmdCd : public Cmd
{
public:
	//Methods
	void Initialize();
	void Execute(int argc, char* argv[]);
};

#endif // !__CMD_CD_H__
