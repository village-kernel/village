//###########################################################################
// vk_cmd_cat.cpp
// Definitions of the functions that manage command cat
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_cmd.h"
#include "vk_console.h"
#include "vk_kernel.h"
#include "vk_file_stream.h"


/// @brief CmdCat
class CmdCat : public Cmd
{
private:
	/// @brief Cat
	/// @param path 
	void Cat(const char* path)
	{
		FileStream file;

		if (file.Open(path, FileMode::_Read))
		{
			int   size = file.Size();
			char* load = new char[size]();

			if (load && (file.Read(load, size) == size))
			{
				console->Output(load, size);
				console->Print("\r\n");
			}

			file.Close();
			delete[] load;
		}
		else
		{
			console->Println("File %s not found", path);
		}
	}
public:
	/// @brief Cmd cat execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		if (argc < 1)
		{
			console->Println("Usage: cat <filename>");
			return;
		}

		const char* path = console->AbsolutePath(argv[1]);
		Cat(path);
		delete path;
	}


	/// @brief Cmd cat help
	void Help()
	{
		console->Println("cmd cat: concatenate and print files");
	}
};


///Register cmd
REGISTER_CMD(new CmdCat(), cat);
