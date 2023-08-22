//###########################################################################
// CmdList.cpp
// Definitions of the functions that manage command list
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "CmdList.h"
#include "Console.h"
#include "DirStream.h"


///Cmd list initialize
void CmdList::Initialize()
{

}


/// @brief List directory
/// @param name 
void CmdList::ListDirectory(const char* name)
{
	DirStream dir;

	if (_OK == dir.Open(name, FileMode::_Read))
	{
		int size = dir.Size();

		FileDir* dirs = new FileDir[size]();

		if (dir.Read(dirs, size) == size)
		{
			for (int i = 0; i < size; i++)
			{
				if ((FileAttr::_Visible == dirs[i].attr) &&
					(0 != strcmp(dirs[i].name, ".")) &&
					(0 != strcmp(dirs[i].name, "..")))
				{
					console.OutputRAW("%s  ", dirs[i].name);
				}
			}
			if (size) console.OutputRAW("\r\n");
		}

		delete[] dirs;

		dir.Close();
	}
	else
	{
		console.Error("%s is not a valid path, please confirm whether the path is correct", name);
	}
}


///Cmd about execute
void CmdList::Execute(int argc, char* argv[])
{
	if (argc < 1)
	{
		console.Output("Usage: ls <path>");
		return;
	}
	ListDirectory(argv[1]);
}


///Register cmd
REGISTER_CMD(new CmdList(), ls);
