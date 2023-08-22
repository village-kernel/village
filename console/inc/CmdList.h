//###########################################################################
// CmdList.h
// Declarations of the functions that manage command list
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __CMD_LIST_H__
#define __CMD_LIST_H__

#include "Cmd.h"

///CmdList
class CmdList : public Cmd
{
private:
	//Methods
	void ListDirectory(const char* name);
public:
	//Methods
	void Initialize();
	void Execute(int argc, char* argv[]);
};

#endif // !__CMD_LIST_H__
