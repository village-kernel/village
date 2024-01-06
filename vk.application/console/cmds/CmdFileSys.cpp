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


/// @brief CmdList
class CmdList : public Cmd
{
private:
	/// @brief List directory
	/// @param name 
	void ListDirectory(const char* name)
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
					//if ((FileAttr::_Visible == dirs[i].attr) &&
					//	(0 != strcmp(dirs[i].name, ".")) &&
					//	(0 != strcmp(dirs[i].name, "..")))
					{
						if (FileType::_Diretory == dirs[i].type)
							console.OutputRAW("\033[36m%s  \033[39m", dirs[i].name);
						else if (FileType::_File == dirs[i].type)
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
		if (_ERR == file.Open(filename, FileMode::_CreateNew))
		{
			console.Error("Create file %s failed.", filename);
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
		CreateFile(argv[1]);
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
		if (_ERR == dir.Open(dirname, FileMode::_CreateNew))
		{
			console.Error("Create directory %s failed.", dirname);
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
		CreateDir(argv[1]);
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
		Move(argv[1], argv[2]);
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
		Copy(argv[1], argv[2]);
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
		Remove(argv[1]);
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
