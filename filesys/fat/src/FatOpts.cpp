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
	DirEntry* entry = fatData.Open(name, mode);
	if (NULL != entry)
	{
		return files.Add(entry);
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
	DirEntry* entry = files.GetItem(fd);
	if (NULL != entry)
	{
		return fatData.Write(data, size, entry);
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
	DirEntry* entry = files.GetItem(fd);
	if (NULL != entry)
	{
		return fatData.Read(data, size, entry);
	}
	return -1;
}


/// @brief FAT size
/// @return 
int FatOpts::Size(int fd)
{
	DirEntry* entry = files.GetItem(fd);
	if (NULL != entry)
	{
		return fatData.Size(entry);
	}
	return 0;
}


/// @brief FAT close
/// @return 
void FatOpts::Close(int fd)
{
	DirEntry* entry = files.GetItem(fd);
	if (NULL != entry)
	{
		files.Remove(entry, fd);
	}
}


/// @brief Open directory
/// @param name
/// @param mode 
/// @return 
int FatOpts::OpenDir(const char* name, int mode)
{
	DirEntries* data = fatData.OpenDir(name, mode);
	if (NULL != data)
	{
		return dirs.Add(data);
	}
	return -1;
}


/// @brief Get file type
/// @param entry 
/// @return file type
FileType FatOpts::GetFileType(DirEntry* entry)
{
	if (entry->body.IsFile())
		return FileType::_File;
	else if (entry->body.IsDirectory())
		return FileType::_Diretory;
	else if (entry->body.IsVolume())
		return FileType::_Volume;
	else
		return FileType::_Unknown;
}


/// @brief Get file attr
/// @param entry 
/// @return file attr
FileAttr FatOpts::GetFileAttr(DirEntry* entry)
{
	return entry->body.IsHidden() ? FileAttr::_Hidden : FileAttr::_Visible;
}


/// @brief Read directory
/// @param fd 
/// @param data 
/// @return 
int FatOpts::ReadDir(int fd, FileDir* dirs, int size, int offset)
{
	DirEntries* data = this->dirs.GetItem(fd);
	
	if (NULL != data)
	{
		for (int i = 0; i < size; i++)
		{
			DirEntry* ent = fatData.ReadDir(data);
			if (NULL != ent)
			{
				char* path = new char[strlen(data->path) + strlen(ent->name) + 2]();
				sprintf(path, "%s/%s", data->path, ent->name);
				dirs[i].path = path;
				dirs[i].name = ent->name;
				dirs[i].type = GetFileType(ent);
				dirs[i].attr = GetFileAttr(ent);
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
	DirEntries* data = dirs.GetItem(fd);
	if (NULL != data)
	{
		return fatData.SizeDir(data);
	}
	return -1;
}


/// @brief Close dir
/// @param fd 
/// @return 
void FatOpts::CloseDir(int fd)
{
	DirEntries* data = dirs.GetItem(fd);
	if (NULL != data)
	{
		dirs.Remove(data, fd);
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
