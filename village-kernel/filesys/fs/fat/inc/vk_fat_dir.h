//###########################################################################
// vk_fat_dir.h
// Declarations of the functions that manage fat dir
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_FAT_DIR_H__
#define __VK_FAT_DIR_H__

#include "vk_fat_diskio.h"
#include "vk_fat_object.h"

/// @brief FatDir
class FatDir
{
private:
    //Members
    FatDiskio& diskio;

    //Dirent Members
    FatObject* object;
    int        dirmode;
    int        subSize;
    FatObject* subObjs;
public:
    //Methods
    FatDir(FatDiskio& diskio);
    void Open(FatObject* fatObj, int mode);
    int Read(FileDir* dirs, int size, int offset);
    int Size();
    void Close();
};

#endif //!__VK_FAT_DIR_H__
