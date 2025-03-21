//###########################################################################
// vk_cmd_filesys.cpp
// Definitions of the functions that manage command change directory
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_cmd.h"
#include "vk_console.h"
#include "vk_dir_stream.h"
#include "vk_file_stream.h"
#include "vk_filesys_opt.h"
#include "string.h"


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

            console->SetPath(path);
        }
        else
        {
            console->Error("%s is not a valid path, please confirm whether the path is correct", path);
        }
    }
public:
    /// @brief Cmd cd execute
    /// @param argc 
    /// @param argv 
    void Execute(int argc, char* argv[])
    {
        if (argc < 2)
        {
            console->Println("Usage: cd <directory>");
            return;
        }

        const char* path = console->AbsolutePath(argv[1]);
        ChangeDirectory(path);
        delete path;
    }


    /// @brief Cmd cd help
    void Help()
    {
        console->Println("cmd cd: change directory");
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
                            console->Print("%s  ", dirs[i].name);
                        }
                    }
                }
                if (size) console->Print("\r\n");
            }

            delete[] dirs;

            dir.Close();
        }
        else
        {
            console->Error("%s is not a valid path, please confirm whether the path is correct", name);
        }
    }
public:
    /// @brief Cmd list execute
    /// @param argc 
    /// @param argv 
    void Execute(int argc, char* argv[])
    {
        if (argc < 1)
        {
            console->Println("Usage: ls [directory]");
            return;
        }

        if (argc == 1)
            ListDirectory(console->GetPath());
        else
            ListDirectory(console->AbsolutePath(argv[1]));
    }


    /// @brief Cmd list help
    void Help()
    {
        console->Println("cmd ls: list directory");
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
                console->Error("Create file %s failed.", filename);
            }
        }
        else
        {
            console->Error("The file %s already exists.", filename);
        }

        file.Close();
    }
public:
    /// @brief Cmd touch execute
    /// @param argc 
    /// @param argv 
    void Execute(int argc, char* argv[])
    {
        if (argc < 2)
        {
            console->Println("Usage: touch <filename>");
            return;
        }

        const char* path = console->AbsolutePath(argv[1]);
        CreateFile(path);
        delete path;
    }


    /// @brief Cmd touch help
    void Help()
    {
        console->Println("cmd touch: create file");
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
                console->Error("Create directory %s failed.", dirname);
            }
        }
        else
        {
            console->Error("The directory %s already exists.", dirname);
        }

        dir.Close();
    }
public:
    /// @brief Cmd mkdir execute
    /// @param argc 
    /// @param argv 
    void Execute(int argc, char* argv[])
    {
        if (argc < 2)
        {
            console->Println("Usage: mkdir <dirname>");
            return;
        }

        const char* path = console->AbsolutePath(argv[1]);
        CreateDir(path);
        delete path;
    }


    /// @brief Cmd mkdir help
    void Help()
    {
        console->Println("cmd mkdir: create directory");
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

        if (!fileSysOpt.Move(source, target))
        {
            console->Error("move %s to %s failed!", source, target);
        }
    }
public:
    /// @brief Cmd move execute
    /// @param argc 
    /// @param argv 
    void Execute(int argc, char* argv[])
    {
        if (argc < 3)
        {
            console->Println("Usage: mv <source> <target>");
            return;
        }

        const char* path1 = console->AbsolutePath(argv[1]);
        const char* path2 = console->AbsolutePath(argv[2]);
        Move(path1, path2);
        delete path1;
        delete path2;
    }


    /// @brief Cmd move help
    void Help()
    {
        console->Println("cmd mv: move file or directory");
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

        if (!fileSysOpt.Copy(source, target))
        {
            console->Error("copy %s to %s failed!", source, target);
        }
    }
public:
    /// @brief Cmd copy execute
    /// @param argc 
    /// @param argv 
    void Execute(int argc, char* argv[])
    {
        if (argc < 2)
        {
            console->Println("Usage: cp <source> <target>");
            return;
        }

        const char* path1 = console->AbsolutePath(argv[1]);
        const char* path2 = console->AbsolutePath(argv[2]);
        Copy(path1, path2);
        delete path1;
        delete path2;
    }


    /// @brief Cmd cp help
    void Help()
    {
        console->Println("cmd cp: copy file or directory");
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

        if (!fileSysOpt.Remove(name))
        {
            console->Error("Remove %s failed!", name);
        }
    }
public:
    /// @brief Cmd remove execute
    /// @param argc 
    /// @param argv 
    void Execute(int argc, char* argv[])
    {
        if (argc < 2)
        {
            console->Println("Usage: rm <file/directory>");
            return;
        }

        const char* path = console->AbsolutePath(argv[1]);
        Remove(path);
        delete path;
    }


    /// @brief Cmd remove help
    void Help()
    {
        console->Println("cmd rm: remove file or directory");
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
