//###########################################################################
// vk_fat_filedir.h
// Declarations of the functions that manage fat file dir
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_FAT_FILE_DIR_H__
#define __VK_FAT_FILE_DIR_H__

#include "vk_fat_diskio.h"
#include "vk_fat_object.h"

/// @brief FatFile
class FatFile
{
private:
    //Members
    FatDiskio&       diskio;
    FatDiskio::Info& diskinf;

    //File Members
    FatObject* object;
    int        filemode;
    int        fileSize;
    uint32_t   fstClust;
    uint32_t   sectorSize;
    uint32_t   clustSize;
    int        buflen;
    char*      buffer;
public:
    //Methods
    FatFile(FatDiskio& diskio);
    void Open(FatObject* fatObj, int mode);
    int Write(char* data, int size, int offset);
    int Read(char* data, int size, int offset);
    int Size();
    void Flush();
    void Close();
};


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

#endif //!__VK_FAT_FILE_DIR_H__
