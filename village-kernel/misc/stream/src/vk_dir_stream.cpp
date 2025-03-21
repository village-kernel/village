//###########################################################################
// vk_dir_stream.cpp
// Definitions of the functions that manage file
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_dir_stream.h"
#include "vk_kernel.h"


/// @brief Constructor
DirStream::DirStream(const char* name, int mode)
    :fd(-1),
    volume(NULL)
{
    if (NULL != name) Open(name, mode);
}


/// @brief Destructor
DirStream::~DirStream()
{
}


/// @brief DirStream is exist
/// @param name 
/// @return 
bool DirStream::IsExist(const char* name)
{
    volume = kernel->filesys.GetVolume(name);

    if (NULL != volume)
    {
        return volume->IsExist(name, FileType::_Diretory);
    }
    
    return false;
}


/// @brief DirStream open
/// @param name 
/// @param mode 
/// @return 
bool DirStream::Open(const char* name, int mode)
{
    volume = kernel->filesys.GetVolume(name);

    if (NULL != volume)
    {
        fd = volume->OpenDir(name, mode);
    }
    
    return (fd != -1);
}


/// @brief DirStream read
/// @param dirs 
/// @param size 
/// @param offset 
/// @return 
int DirStream::Read(FileDir* dirs, int size, int offset)
{
    if (NULL != volume)
    {
        return volume->ReadDir(fd, dirs, size, offset);
    }
    return 0;
}


/// @brief DirStream size
/// @return 
int DirStream::Size()
{
    if (NULL != volume)
    {
        return volume->SizeDir(fd);
    }
    return 0;
}


/// @brief DirStream close
void DirStream::Close()
{
    if (NULL != volume)
    {
        volume->CloseDir(fd);
    }
}
