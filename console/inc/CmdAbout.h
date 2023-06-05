//###########################################################################
// CmdAbout.h
// Declarations of the functions that manage command about
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __CMD_ABOUT_H__
#define __CMD_ABOUT_H__

#include "Cmd.h"

///CmdAbout
class CmdAbout : public Cmd
{
public:
	//Methods
	void Initialize();
	void Execute(int argc, char* argv[]);
};

#endif // !__CMD_ABOUT_H__
