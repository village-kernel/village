//###########################################################################
// CmdMkdir.cpp
// Definitions of the functions that manage command mkdir
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "CmdMkdir.h"
#include "Console.h"
#include "DirStream.h"


/// @brief Cmd mkdir initialize
void CmdMkdir::Initialize()
{

}


/// @brief Create directory
/// @param dirname 
void CmdMkdir::CreateDir(const char* dirname)
{
	DirStream dir;
	dir.Open(dirname, FileMode::_CreateNew);
	dir.Close();
}


/// @brief Cmd mkdir execute
/// @param argc 
/// @param argv 
void CmdMkdir::Execute(int argc, char* argv[])
{
	if (argc < 1)
	{
		console.Output("Usage: mkdir [dirname]");
		return;
	}
	CreateDir(argv[1]);
}


///Register cmd
REGISTER_CMD(new CmdMkdir(), mkdir);
