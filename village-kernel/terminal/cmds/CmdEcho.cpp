//###########################################################################
// CmdEcho.cpp
// Definitions of the functions that manage command echo
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Cmd.h"
#include "Console.h"
#include "Kernel.h"
#include "FileStream.h"


/// @brief CmdEcho
class CmdEcho : public Cmd
{
private:
	/// @brief echo
	/// @param path 
	void Echo(const char* data, const char* mode, const char* path)
	{
		if (NULL != path)
		{
			FileStream file;

			//Set mode
			int filemode = FileMode::_CreateNew;
			if (0 == strcmp(">", mode))
				filemode |= FileMode::_Write;
			else if (0 == strcmp(">>", mode))
				filemode |= FileMode::_OpenAppend;

			//Set path
			const char* filepath = console->AbsolutePath(path);

			//Write data
			if (file.Open(filepath, filemode))
			{
				int   size   = strlen(data) + 2;
				char* buffer = new char[size]();
				
				strcpy(buffer, data);
				strcat(buffer, "\r\n");

				file.Write((char*)buffer, size);
				file.Close();

				delete[] buffer;
			}

			delete path;
		}
		else
		{
			console->Println(data);
		}
	}
public:
	/// @brief Cmd echo execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		if (argc < 2)
		{
			console->Println("Usage: echo <string> [>]|[>>] [path]");
			return;
		}

		if (argc == 4)
		{
			Echo(argv[1], argv[2], argv[3]);
		}
		else
		{
			Echo(argv[1], NULL, NULL);
		}
	}


	/// @brief Cmd echo help
	void Help()
	{
		console->Println("cmd echo: write arguments to the standard output");
	}
};


///Register cmd
REGISTER_CMD(new CmdEcho(), echo);
