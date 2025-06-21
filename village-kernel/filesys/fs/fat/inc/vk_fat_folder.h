//###########################################################################
// vk_fat_folder.h
// Declarations of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_FAT_FOLDER_H__
#define __VK_FAT_FOLDER_H__

#include "vk_list.h"
#include "vk_fat_object.h"
#include "vk_fat_diskio.h"


/// @brief FatFolder
class FatFolder
{
private:
    //Members
    FatDiskio&        diskio;
    FatDiskio::Info&  diskinf;

    //Dirent Members
    FatDiskio::Index  entidx;
    FatEntry*         buffer;
    FatObject*        myself;

    //FatObject Members
    VkList<FatObject*> fatObjs;

    //Iterator Methods
    bool ReadBegin();
    bool ReadNext();
    bool WriteNext();
    bool IsReadEnd();
    FatEntry& Item();
    
    //IO Methods
    bool Alloc(uint32_t size);
    uint32_t Pop(FatEntry* entires, uint32_t size);
    uint32_t Push(FatEntry* entires, uint32_t size);

    //Methods
    bool CheckDirName(FatObject* fatObj);
public:
    //Methods
    FatFolder(FatDiskio& diskio, FatObject* fatObj = NULL);
    ~FatFolder();

    void Open(FatObject* selfObj);
    int  Write(FatObject* subObjs, int size);
    int  Read(FatObject* subObjs, int size);
    int  Size();
    void Close();

    void Remove(FatObject* selfObj);
    void Update(FatObject* selfObj);

    FatObject* Search(const char* name);
    FatObject* Create(const char* name, int attr);
};

#endif //!__VK_FAT_FOLDER_H__
