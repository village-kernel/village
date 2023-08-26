//###########################################################################
// CmdTouch.cpp
// Definitions of the functions that manage command touch
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Cmd.h"
#include "Console.h"
#include "FileStream.h"


/// @brief CmdTouch
class CmdTouch : public Cmd
{
private:
	/// @brief Create file
	/// @param filename 
	void CreateFile(const char* filename)
	{
		FileStream file;
		file.Open(filename, FileMode::_CreateNew);
		file.Close();
	}
public:
	/// @brief Cmd touch initialize
	void Initialize()
	{

	}


	/// @brief Cmd touch execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		if (argc < 1)
		{
			console.Output("Usage: touch [filename]");
			return;
		}
		CreateFile(argv[1]);
	}
};


///Register cmd
REGISTER_CMD(new CmdTouch(), touch);
