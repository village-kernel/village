//###########################################################################
// vk_fat_system.h
// Declarations of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_FAT_FILE_SYSTEM_H__
#define __VK_FAT_FILE_SYSTEM_H__

#include "vk_fat_diskio.h"
#include "vk_fat_object.h"
#include "vk_filesys.h"
#include "vk_list.h"


/// @brief FatVolume
class FatVolume : public FileVol
{
private:
    //FatDir
    struct FatDir
    {
        FatObject* object;
        int        mode;
        int        subSize;
        FatObject* subObjs;
    };

    //FatFile
    struct FatFile
    {
        FatObject* object;
        int        mode;
        int        size;
        uint32_t   fstClust;
        uint32_t   sectorSize;
        uint32_t   clustSize;
        int        buflen;
        char*      buffer;
    };

    //Members
    FatDiskio        diskio;
    VkList<FatDir*>  fatDirs;
    VkList<FatFile*> fatFiles;

    //Members
    uint32_t bytesPerSec;
    uint32_t secPerClust;

    //Directory Methods
    char* BaseName(const char* path);
    FatObject* SearchPath(const char* path, int reserve = 0);
    FatObject* CreatePath(const char* path, int attr);
public:
    //Methods
    FatVolume();
    ~FatVolume();

    //Methods
    bool Setup(DevStream* device, uint32_t startingLBA);
    void Exit();
public:
    //File Volume Methods
    bool  SetName(const char* name);
    char* GetName();
    
    //File methods
    int  Open(const char* name, int mode);
    int  Write(int fd, char* data, int size, int offset);
    int  Read(int fd, char* data, int size, int offset);
    int  Size(int fd);
    void Flush(int fd);
    void Close(int fd);

    //Dir methods
    int  OpenDir(const char* path, int mode);
    int  ReadDir(int fd, FileDir* dirs, int size, int offset);
    int  SizeDir(int fd);
    void CloseDir(int fd);

    //Opt methods
    FileType GetFileType(const char* name);
    bool IsExist(const char* name, FileType type);
    bool Remove(const char* name);
};


/// @brief FatSystem
class FatSystem : public FileSys
{
public:
    //Methods
    uint32_t GetSystemID();
    FileVol* CreateVolume();
};

#endif //!__VK_FAT_FILE_SYSTEM_H__
