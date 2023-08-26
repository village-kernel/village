//###########################################################################
// CmdTouch.cpp
// Definitions of the functions that manage command touch
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "CmdTouch.h"
#include "Console.h"
#include "FileStream.h"


/// @brief Cmd touch initialize
void CmdTouch::Initialize()
{

}


/// @brief Create file
/// @param filename 
void CmdTouch::CreateFile(const char* filename)
{
	FileStream file;
	file.Open(filename, FileMode::_CreateNew);
	file.Close();
}


/// @brief Cmd touch execute
/// @param argc 
/// @param argv 
void CmdTouch::Execute(int argc, char* argv[])
{
	if (argc < 1)
	{
		console.Output("Usage: touch [filename]");
		return;
	}
	CreateFile(argv[1]);
}


///Register cmd
REGISTER_CMD(new CmdTouch(), touch);
