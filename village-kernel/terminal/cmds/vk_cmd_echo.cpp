//###########################################################################
// vk_cmd_echo.cpp
// Definitions of the functions that manage command echo
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_cmd.h"
#include "vk_console.h"
#include "vk_kernel.h"
#include "vk_file_stream.h"


/// @brief CmdEcho
class CmdEcho : public Cmd
{
private:
	/// @brief echo
	/// @param path 
	void Echo(int size, char* data[], char* mode, char* path)
	{
		if (NULL != path)
		{
			//Set mode
			int filemode = FileMode::_CreateNew;

			if (0 == strcmp(">", mode))
			{
				filemode |= FileMode::_Write;
			}
			else if (0 == strcmp(">>", mode))
			{
				filemode |= FileMode::_OpenAppend;
			}
			else
			{
				console->Error("parse error near \'\n\'");
				return;
			}

			//Set path
			const char* filepath = console->AbsolutePath(path);

			//Write data
			FileStream file;

			if (file.Open(filepath, filemode))
			{
				if (file.Size() && (filemode & FileMode::_OpenAppend))
				{
					file.Write((char*)"\r\n", 3);
				}
				
				for (int i = 0; i < size; i++)
				{
					file.Write(data[i], strlen(data[i]));
					file.Write((char*)" ", 2);
				}
				
				file.Flush();
				file.Close();
			}

			delete filepath;
		}
		else
		{
			console->Println(data[0]);
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

		if (argc >= 4)
		{
			Echo(argc - 3, argv + 1, argv[argc - 2], argv[argc - 1]);
		}
		else
		{
			Echo(argc - 1, argv + 1, NULL, NULL);
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
