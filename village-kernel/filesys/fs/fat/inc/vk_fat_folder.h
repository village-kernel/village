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
    FatDiskio&        fatDisk;
    FatDiskio::Info&  fatInfo;

    //Dirent Members
    FatEntryLoc       entloc;
    FatEntry*         buffer;
    FatObject*        parent;

    //FatObject Members
    VkList<FatObject*> fatObjs;

    //Disk Methods
    void CalcFirstSector();
    void CalcNextSector();
    void ReadEntries();
    void WriteEntries();

    //Iterator Methods
    bool ReadBegin();
    bool ReadNext();
    bool WriteNext();
    bool IsReadEnd();
    FatEntry& Item();
    
    //IO Methods
    bool Find(uint32_t size);
    uint32_t Pop(FatEntry* pop, uint32_t size);
    uint32_t Push(FatEntry* push, uint32_t size);

    //Methods
    bool CheckDirName(FatObject* fatObj);
public:
    //Methods
    FatFolder(FatDiskio& fatDisk, FatObject* fatObj = NULL);
    ~FatFolder();

    void Open(FatObject* fatObj);
    FatObject* Search(const char* name);
    FatObject* Create(const char* name, int attr);
    int  Write(FatObject* fatObjs, int size);
    int  Read(FatObject* fatObjs, int size);
    void Remove(FatObject* fatObj);
    void Update(FatObject* fatObj);
    int  Size();
    void Close();
};

#endif //!__VK_FAT_FOLDER_H__
