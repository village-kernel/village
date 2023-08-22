//###########################################################################
// CmdTouch.h
// Declarations of the functions that manage command touch
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __CMD_TOUCH_H__
#define __CMD_TOUCH_H__

#include "Cmd.h"

///CmdTouch
class CmdTouch : public Cmd
{
public:
	//Methods
	void Initialize();
	void Execute(int argc, char* argv[]);
};

#endif // !__CMD_TOUCH_H__
