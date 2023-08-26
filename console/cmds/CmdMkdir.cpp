//###########################################################################
// CmdMkdir.cpp
// Definitions of the functions that manage command mkdir
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Cmd.h"
#include "Console.h"
#include "DirStream.h"


/// @brief CmdMkdir
class CmdMkdir : public Cmd
{
private:
	/// @brief Create directory
	/// @param dirname 
	void CreateDir(const char* dirname)
	{
		DirStream dir;
		dir.Open(dirname, FileMode::_CreateNew);
		dir.Close();
	}
public:
	/// @brief Cmd mkdir initialize
	void Initialize()
	{

	}


	/// @brief Cmd mkdir execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		if (argc < 1)
		{
			console.Output("Usage: mkdir [dirname]");
			return;
		}
		CreateDir(argv[1]);
	}
};


///Register cmd
REGISTER_CMD(new CmdMkdir(), mkdir);
