//###########################################################################
// vk_fat_dir.cpp
// Definitions of the functions that manage fat dir
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_fat_dir.h"
#include "vk_fat_folder.h"


/// @brief Constructor
/// @param diskio 
FatDir::FatDir(FatDiskio& diskio)
    :diskio(diskio)
{
}

/// @brief Open
/// @param fatObj 
void FatDir::Open(FatObject* fatObj, int mode)
{
    FatFolder* folder = new FatFolder(diskio, fatObj);

    object  = fatObj;
    dirmode = mode;
    subSize = folder->Size();
    subObjs = new FatObject[subSize]();
    subSize = folder->Read(subObjs, subSize);
    
    folder->Close();
    delete folder;
}


/// @brief Read
/// @param dirs 
/// @param size 
/// @param offset 
/// @return 
int FatDir::Read(FileDir* dirs, int size, int offset)
{
    if (subSize < size) size = subSize;

    for (int i = 0; i < size; i++)
    {
        dirs[i].name = subObjs[i].GetObjectName();
        dirs[i].type = subObjs[i].GetObjectType();
        dirs[i].attr = subObjs[i].GetObjectAttr();
    }

    return size;
}

/// @brief Size
/// @return 
int FatDir::Size()
{
    return subSize;
}

/// @brief Close
void FatDir::Close()
{
    delete[] subObjs;
}
