//###########################################################################
// CmdCd.cpp
// Definitions of the functions that manage command change directory
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Cmd.h"
#include "Console.h"
#include "DirStream.h"


/// @brief CmdCd
class CmdCd : public Cmd
{
private:
	/// @brief Change directory
	/// @param  
	void ChangeDirectory(const char* path)
	{
		if (DirStream().IsExist(path))
		{
			console.SetPath(path);
		}
		else
		{
			console.Error("%s is not a valid path, please confirm whether the path is correct", path);
		}
	}
public:
	/// @brief Cmd cd initialize
	void Initialize()
	{

	}


	/// @brief Cmd cd execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		if (argc < 1)
		{
			console.Output("Usage: cd <directory>");
			return;
		}
		ChangeDirectory(argv[1]);
	}
};


///Register cmd
REGISTER_CMD(new CmdCd(), cd);
