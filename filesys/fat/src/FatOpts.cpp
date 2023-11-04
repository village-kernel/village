//###########################################################################
// FatOpts.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatOpts.h"
#include "Kernel.h"
#include "Debug.h"
#include "stdio.h"


/// @brief Constructor
FatOpts::FatOpts()
{
}


/// @brief Destructor
FatOpts::~FatOpts()
{
	Exit();
}


/// @brief Setup
/// @param dat 
/// @return result
int FatOpts::Setup(Driver* diskdrv, uint32_t fstSec)
{
	return fatData.Setup(diskdrv, fstSec);
}


/// @brief Exit
void FatOpts::Exit()
{
	files.Release();
	dirs.Release();
}


/// @brief FAT mount
/// @return 
int FatOpts::Mount(const char* path, const char* mount, int opt)
{
	return _OK;
}


/// @brief FAT unmount
/// @return 
int FatOpts::Unmount(const char* mount)
{
	return _OK;
}


/// @brief Set volume label
/// @param name 
/// @return 
int FatOpts::SetVolumeLabel(const char* name)
{
	return fatData.SetVolumeLabel(name);
}


/// @brief Get volume label
/// @return 
char* FatOpts::GetVolumeLabel()
{
	return fatData.GetVolumeLabel();
}


/// @brief FAT open
/// @param name 
/// @param mode 
/// @return 
int FatOpts::Open(const char* name, int mode)
{
	DirEntry* dirent = fatData.Open(name, mode);
	if (NULL != dirent)
	{
		return files.Add(dirent);
	}
	return -1;
}


/// @brief FAT write
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int FatOpts::Write(int fd, char* data, int size, int offset)
{
	DirEntry* dirent = files.GetItem(fd);
	if (NULL != dirent)
	{
		return fatData.Write(data, size, dirent);
	}
	return -1;
}


/// @brief FAT read
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int FatOpts::Read(int fd, char* data, int size, int offset)
{
	DirEntry* dirent = files.GetItem(fd);
	if (NULL != dirent)
	{
		return fatData.Read(data, size, dirent);
	}
	return -1;
}


/// @brief FAT size
/// @return 
int FatOpts::Size(int fd)
{
	DirEntry* dirent = files.GetItem(fd);
	if (NULL != dirent)
	{
		return fatData.Size(dirent);
	}
	return 0;
}


/// @brief FAT close
/// @return 
void FatOpts::Close(int fd)
{
	DirEntry* dirent = files.GetItem(fd);
	if (NULL != dirent)
	{
		files.Remove(dirent, fd);
	}
}


/// @brief Open directory
/// @param name
/// @param mode 
/// @return 
int FatOpts::OpenDir(const char* name, int mode)
{
	DirEntries* dirents = fatData.OpenDir(name, mode);
	if (NULL != dirents)
	{
		return dirs.Add(dirents);
	}
	return -1;
}


/// @brief Get file type
/// @param dirent 
/// @return file type
FileType FatOpts::GetFileType(DirEntry* dirent)
{
	if (dirent->body.IsFile())
		return FileType::_File;
	else if (dirent->body.IsDirectory())
		return FileType::_Diretory;
	else if (dirent->body.IsVolume())
		return FileType::_Volume;
	else
		return FileType::_Unknown;
}


/// @brief Get file attr
/// @param dirent 
/// @return file attr
FileAttr FatOpts::GetFileAttr(DirEntry* dirent)
{
	return dirent->body.IsHidden() ? FileAttr::_Hidden : FileAttr::_Visible;
}


/// @brief Read directory
/// @param fd 
/// @param dirs 
/// @param size 
/// @param offset 
/// @return 
int FatOpts::ReadDir(int fd, FileDir* dirs, int size, int offset)
{
	DirEntries* dirents = this->dirs.GetItem(fd);
	
	if (NULL != dirents)
	{
		for (int i = 0; i < size; i++)
		{
			DirEntry* dirent = fatData.ReadDir(dirents);
			if (NULL != dirent)
			{
				char* path = new char[strlen(dirents->path) + strlen(dirent->name) + 2]();
				sprintf(path, "%s/%s", dirents->path, dirent->name);
				dirs[i].path = path;
				dirs[i].name = dirent->name;
				dirs[i].type = GetFileType(dirent);
				dirs[i].attr = GetFileAttr(dirent);
			}
			else return i;
		}
	}
	else return 0;

	return size;
}


/// @brief Size dir
/// @param fd 
/// @return 
int FatOpts::SizeDir(int fd)
{
	DirEntries* dirents = dirs.GetItem(fd);
	if (NULL != dirents)
	{
		return fatData.SizeDir(dirents);
	}
	return -1;
}


/// @brief Close dir
/// @param fd 
/// @return 
void FatOpts::CloseDir(int fd)
{
	DirEntries* dirents = dirs.GetItem(fd);
	if (NULL != dirents)
	{
		dirs.Remove(dirents, fd);
	}
}


/// @brief FAT move
/// @param old 
/// @param now 
/// @return 
int FatOpts::Move(const char* from, const char* to)
{
	return fatData.Move(from, to);
}


/// @brief FAT copy
/// @param from 
/// @param to 
/// @return 
int FatOpts::Copy(const char* from, const char* to)
{
	return fatData.Copy(from, to);
}


/// @brief FAT remove
/// @return 
int FatOpts::Remove(const char* name)
{
	return fatData.Remove(name);
}


/// @brief FAT move dir
/// @param old 
/// @param now 
/// @return 
int FatOpts::MoveDir(const char* from, const char* to)
{
	return fatData.MoveDir(from, to);
}


/// @brief FAT copy dir
/// @param from 
/// @param to 
/// @return 
int FatOpts::CopyDir(const char* from, const char* to)
{
	return fatData.CopyDir(from, to);
}


/// @brief FAT remove dir
/// @return 
int FatOpts::RemoveDir(const char* name)
{
	return fatData.RemoveDir(name);
}
