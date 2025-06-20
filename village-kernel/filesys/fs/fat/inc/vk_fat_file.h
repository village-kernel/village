//###########################################################################
// vk_fat_file.h
// Declarations of the functions that manage fat file
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_FAT_FILE_H__
#define __VK_FAT_FILE_H__

#include "vk_fat_diskio.h"
#include "vk_fat_object.h"

/// @brief FatFile
class FatFile
{
private:
    //Members
    FatDiskio& diskio;
    FatDiskio::Info& fatInfo;

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

#endif //!__VK_FAT_FILE_H__
