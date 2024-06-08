//###########################################################################
// CmdFileSys.cpp
// Definitions of the functions that manage command change directory
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Cmd.h"
#include "Console.h"
#include "DirStream.h"
#include "FileStream.h"
#include "FileSysOpt.h"
#include "string.h"


/// @brief AbsolutePath
/// @param path 
/// @return 
static char* AbsolutePath(char* path)
{
	char* res = NULL;

	if ('/' != path[0])
	{
		res = new char[strlen(console.GetPath()) + strlen(path) + 2]();
		strcat(res, console.GetPath());
		if ('/' != res[strlen(console.GetPath()) - 1]) strcat(res, "/");
		strcat(res, path);
	}
	else
	{
		res = new char[strlen(path) + 1]();
		strcat(res, path);
	}

	return res;
}


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
			char* dir = strrchr(path, '/');

			//Handle "." dir
			if (0 == strcmp(dir, "/."))
			{
				dir[0] = '\0';
			}
			//Handle ".." dir
			else if (0 == strcmp(dir, "/.."))
			{
				dir[0] = '\0';
				dir = strrchr(path, '/');
				dir[(0 == (dir - path)) ? 1 : 0] = '\0';
			}

			console.SetPath(path);
		}
		else
		{
			console.Error("%s is not a valid path, please confirm whether the path is correct", path);
		}
	}
public:
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

		char* path = AbsolutePath(argv[1]);
		ChangeDirectory(path);
		delete path;
	}
};


/// @brief CmdList
class CmdList : public Cmd
{
private:
	/// @brief List directory
	/// @param name 
	void ListDirectory(const char* name)
	{
		DirStream dir;

		if (dir.Open(name, FileMode::_Read))
		{
			int size = dir.Size();

			FileDir* dirs = new FileDir[size]();

			if (dir.Read(dirs, size) == size)
			{
				for (int i = 0; i < size; i++)
				{
					if (FileAttr::_Visible == dirs[i].attr)
					{
						if ((FileType::_Diretory == dirs[i].type) ||
							(FileType::_File     == dirs[i].type))
						{
							console.OutputRAW("%s  ", dirs[i].name);
						}
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
public:
	/// @brief Cmd about execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		if (argc < 1)
		{
			console.Output("Usage: ls [directory]");
			return;
		}
		ListDirectory((argc == 1) ? console.GetPath() : argv[1]);
	}
};


/// @brief CmdTouch
class CmdTouch : public Cmd
{
private:
	/// @brief Create file
	/// @param filename 
	void CreateFile(const char* filename)
	{
		FileStream file;

		if (!file.IsExist(filename))
		{
			if (!file.Open(filename, FileMode::_CreateNew))
			{
				console.Error("Create file %s failed.", filename);
			}
		}
		else
		{
			console.Error("The file %s already exists.", filename);
		}

		file.Close();
	}
public:
	/// @brief Cmd touch execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		if (argc < 1)
		{
			console.Output("Usage: touch <filename>");
			return;
		}

		char* path = AbsolutePath(argv[1]);
		CreateFile(path);
		delete path;
	}
};


/// @brief CmdMkdir
class CmdMkdir : public Cmd
{
private:
	/// @brief Create directory
	/// @param dirname 
	void CreateDir(const char* dirname)
	{
		DirStream dir;
		
		if (!dir.IsExist(dirname))
		{
			if (!dir.Open(dirname, FileMode::_CreateNew))
			{
				console.Error("Create directory %s failed.", dirname);
			}
		}
		else
		{
			console.Error("The directory %s already exists.", dirname);
		}

		dir.Close();
	}
public:
	/// @brief Cmd mkdir execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		if (argc < 1)
		{
			console.Output("Usage: mkdir <dirname>");
			return;
		}

		char* path = AbsolutePath(argv[1]);
		CreateDir(path);
		delete path;
	}
};


/// @brief CmdMove
class CmdMove : public Cmd
{
private:
	/// @brief Move
	/// @param name 
	void Move(const char* source, const char* target)
	{
		FileSysOpt fileSysOpt;
		fileSysOpt.Move(source, target);
	}
public:
	/// @brief Cmd move execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		if (argc < 3)
		{
			console.Output("Usage: mv <source> <target>");
			return;
		}

		char* path1 = AbsolutePath(argv[1]);
		char* path2 = AbsolutePath(argv[2]);
		Move(path1, path2);
		delete path1;
		delete path2;
	}
};


/// @brief CmdCopy
class CmdCopy : public Cmd
{
private:
	/// @brief Copy
	/// @param name 
	void Copy(const char* source, const char* target)
	{
		FileSysOpt fileSysOpt;
		fileSysOpt.Copy(source, target);
	}
public:
	/// @brief Cmd copy execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		if (argc < 2)
		{
			console.Output("Usage: cp <source> <target>");
			return;
		}

		char* path1 = AbsolutePath(argv[1]);
		char* path2 = AbsolutePath(argv[2]);
		Copy(path1, path2);
		delete path1;
		delete path2;
	}
};


/// @brief CmdRemove
class CmdRemove : public Cmd
{
private:
	/// @brief Remove
	/// @param name 
	void Remove(const char* name)
	{
		FileSysOpt fileSysOpt;
		fileSysOpt.Remove(name);
	}
public:
	/// @brief Cmd remove execute
	/// @param argc 
	/// @param argv 
	void Execute(int argc, char* argv[])
	{
		if (argc < 2)
		{
			console.Output("Usage: rm <file/directory>");
			return;
		}

		char* path = AbsolutePath(argv[1]);
		Remove(path);
		delete path;
	}
};


///Register cmd
REGISTER_CMD(new CmdCd(),       cd    );
REGISTER_CMD(new CmdList(),     ls    );
REGISTER_CMD(new CmdTouch(),    touch );
REGISTER_CMD(new CmdMkdir(),    mkdir );
REGISTER_CMD(new CmdMove(),     mv    );
REGISTER_CMD(new CmdCopy(),     cp    );
REGISTER_CMD(new CmdRemove(),   rm    );
