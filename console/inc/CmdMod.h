//###########################################################################
// CmdMod.h
// Declarations of the functions that manage command insmod and rmmod
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __CMD_MOD_H__
#define __CMD_MOD_H__

#include "Cmd.h"
#include "ModInstaller.h"


/// @brief CmdInsMod
class CmdInsMod : public Cmd
{
private:
	//Members
	ModInstaller installer;
public:
	//Methods
	void Initialize();
	void Execute(int argc, char* argv[]);
};


/// @brief CmdRmMod
class CmdRmMod : public Cmd
{
private:
	//Members
	ModInstaller installer;
public:
	//Methods
	void Initialize();
	void Execute(int argc, char* argv[]);
};

#endif // !__CMD_MOD_H__
