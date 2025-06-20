//###########################################################################
// vk_fat_system.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_fat_system.h"
#include "vk_fat_folder.h"
#include "vk_filesys.h"
#include "vk_regex.h"
#include "vk_kernel.h"


/// @brief Constructor
FatVolume::FatVolume()
    :bytesPerSec(0),
    secPerClust(0)
{
}


/// @brief Destructor
FatVolume::~FatVolume()
{
}


/// @brief FatVolume Setup
/// @param device 
/// @param startingLBA 
/// @return 
bool FatVolume::Setup(DevStream* device, uint32_t startingLBA)
{
    if (diskio.Setup(device, startingLBA))
    {
        bytesPerSec = diskio.GetInfo().bytesPerSec;
        secPerClust = diskio.GetInfo().secPerClust;
    }
    return (bytesPerSec && secPerClust) ? true : false;
}


/// @brief FatVolume Exit
void FatVolume::Exit()
{
    diskio.Exit();
}


/// @brief BaseName
/// @param path 
/// @return 
char* FatVolume::BaseName(const char* path)
{
    uint8_t pos = strlen(path);
    char ch = 0; do { ch = path[--pos]; } while ('/' != ch && pos);
    return (char*)path + pos + 1;
}


/// @brief Search path
/// @param path 
/// @param reserve 
/// @return 
FatObject* FatVolume::SearchPath(const char* path, int reserve)
{
    Regex regex;
    regex.Split(path, '/');
    char** names = regex.ToArray();
    int8_t deep  = regex.Size() - reserve;

    //Create an directory fat object
    FatObject* fatObj = new FatObject(new FatEntry());
    fatObj->SetAttribute(FatDefs::_AttrDirectory);

    //Search directory
    FatObject* found = fatObj;
    for (int8_t i = 0; i < deep; i++)
    {
        found = FatFolder(diskio, found).Search(names[i]);
        if (NULL == found) break;
    }

    //Update fatObj
    if (NULL != found) 
    {
        fatObj->Setup(found);
        return fatObj;
    }

    return NULL;
}


/// @brief Create path
/// @param path 
/// @param attr 
/// @return 
FatObject* FatVolume::CreatePath(const char* path, int attr)
{
    FatObject* fatObj = SearchPath(path, 1);

    if (NULL != fatObj)
    {
        if (FileType::_Diretory == fatObj->GetObjectType())
        {
            FatObject* resObj = FatFolder(diskio, fatObj).Create(BaseName(path), attr);

            if (NULL != resObj)
            {
                fatObj->Setup(resObj);
                return fatObj;
            }
        }
    }

    return NULL;
}


/// @brief Set volume name
/// @param name 
/// @return 
bool FatVolume::SetName(const char* name)
{
    FatFolder folder(diskio, SearchPath("/"));

    FatObject fatObj;

    if (1 == folder.Read(&fatObj, 1))
    {
        if (FileType::_Volume == fatObj.GetObjectType())
        {
            fatObj.SetRawName(name);

            folder.Update(&fatObj);
        }
    }

    return (0 == strcmp(GetName(), name));
}


/// @brief Get volume name
/// @return 
char* FatVolume::GetName()
{
    char* name = (char*)"NONAME";

    FatFolder folder(diskio, SearchPath("/"));

    FatObject fatObj;

    if (1 == folder.Read(&fatObj, 1))
    {
        if (FileType::_Volume == fatObj.GetObjectType())
        {
            name = fatObj.GetRawName();
        }
    }

    return name;
}


/// @brief Open
/// @param name 
/// @param mode 
/// @return 
int FatVolume::Open(const char* name, int mode)
{
    FatObject* fatObj = SearchPath(name);

    if ((NULL == fatObj) && (mode & FileMode::_CreateNew))
    {
        fatObj = CreatePath(name, FatDefs::_AttrFile);
    }

    if (NULL != fatObj)
    {
        FatFile* file = new FatFile();
        file->object  = fatObj;
        file->mode    = mode;
        file->size    = fatObj->GetFileSize();

        if (file->size)
        {
            file->fstClust   = fatObj->GetFirstCluster();
            file->sectorSize = (file->size + (bytesPerSec - 1)) / bytesPerSec;
            file->clustSize  = (file->sectorSize + (secPerClust - 1)) / secPerClust;
            file->buflen     =  file->clustSize * secPerClust * bytesPerSec;
            file->buffer     = (char*)new char[file->buflen]();
            file->clustSize  = diskio.ReadCluster(file->buffer, file->fstClust, file->clustSize);
        }

        return fatFiles.Add(file);
    }

    return -1;
}


/// @brief Write
/// @param fd 
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int FatVolume::Write(int fd, char* data, int size, int offset)
{
    FatFile* file = fatFiles.GetItem(fd);

    if (NULL != file)
    {
        int buffOffset = 0;

        if (file->mode & FileMode::_OpenAppend)
            buffOffset = file->size;
        else if (file->mode & FileMode::_Write)
            buffOffset = 0;

        file->size = buffOffset + size;

        if (file->size > file->buflen)
        {
            file->sectorSize = (file->size + (bytesPerSec - 1)) / bytesPerSec;
            file->clustSize  = (file->sectorSize + (secPerClust - 1)) / secPerClust;
            int    buflen    = (file->clustSize * secPerClust * bytesPerSec);
            char*  buffer    = (char*)new char[file->buflen]();

            if (buffOffset) memcpy((void*)buffer, (const void*)file->buffer, file->buflen);
            delete[] file->buffer;
            file->buflen = buflen;
            file->buffer  = buffer;
        }

        memcpy((void*)(file->buffer + buffOffset), (const void*)(data + offset), size);

        file->mode = FileMode::_OpenAppend;

        return size;
    }

    return 0;
}


/// @brief Read
/// @param fd 
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int FatVolume::Read(int fd, char* data, int size, int offset)
{
    FatFile* file = fatFiles.GetItem(fd);

    if ((NULL != file) && (file->size))
    {
        if (file->size < size) size = file->size;

        memcpy((void*)(data + offset), (const void*)file->buffer, size);
        
        return size;
    }

    return 0;
}


/// @brief Size
/// @param fd 
/// @return 
int FatVolume::Size(int fd)
{
    FatFile* file = fatFiles.GetItem(fd);

    return (NULL != file) ? file->size : 0;
}


/// @brief Flush
/// @param fd 
void FatVolume::Flush(int fd)
{
    FatFile* file = fatFiles.GetItem(fd);
    
    if (NULL != file)
    {
        if (file->clustSize == diskio.WriteCluster(file->buffer, file->fstClust, file->clustSize))
        {
            file->object->SetFileSize(file->size);
            FatFolder(diskio).Update(file->object);
        }
    }
}


/// @brief Close
/// @param fd 
void FatVolume::Close(int fd)
{
    FatFile* file = fatFiles.GetItem(fd);
    
    if (NULL != file)
    {
        delete[] file->buffer;
        fatFiles.Remove(file, fd);
        delete file;
    }
}


/// @brief OpenDir
/// @param name 
/// @param mode 
/// @return 
int FatVolume::OpenDir(const char* path, int mode)
{
    FatObject* fatObj = SearchPath(path);
    
    if ((NULL == fatObj) && (mode & FileMode::_CreateNew))
    {
        fatObj = CreatePath(path, FatDefs::_AttrDirectory);
    }

    if (NULL != fatObj)
    {
        FatFolder* folder = new FatFolder(diskio, fatObj);

        FatDir* dir  = new FatDir();
        dir->object  = fatObj;
        dir->mode    = mode;
        dir->subSize = folder->Size();
        dir->subObjs = new FatObject[dir->subSize]();
        dir->subSize = folder->Read(dir->subObjs, dir->subSize);
        
        folder->Close();
        delete folder;
        return fatDirs.Add(dir);
    }

    return -1;
}


/// @brief ReadDir
/// @param fd 
/// @param dirs 
/// @param size 
/// @param offset 
/// @return 
int FatVolume::ReadDir(int fd, FileDir* dirs, int size, int offset)
{
    FatDir* dir = fatDirs.GetItem(fd);
    
    if (NULL != dir)
    {
        if (dir->subSize < size) size = dir->subSize;

        for (int i = 0; i < size; i++)
        {
            dirs[i].name = dir->subObjs[i].GetObjectName();
            dirs[i].type = dir->subObjs[i].GetObjectType();
            dirs[i].attr = dir->subObjs[i].GetObjectAttr();
        }
    }

    return size;
}


/// @brief SizeDir
/// @param fd 
/// @return 
int FatVolume::SizeDir(int fd)
{
    FatDir* dir = fatDirs.GetItem(fd);
    
    return (NULL != dir) ? dir->subSize : 0;
}


/// @brief CloseDir
/// @param fd 
void FatVolume::CloseDir(int fd)
{
    FatDir* dir = fatDirs.GetItem(fd);
    
    if (NULL != dir)
    {
        delete[] dir->subObjs;
        fatDirs.Remove(dir, fd);
        delete dir;
    }
}


/// @brief Get file type
/// @param name 
/// @return 
FileType FatVolume::GetFileType(const char* name)
{
    FileType type = FileType::_Unknown;

    FatObject* fatObj = SearchPath(name);

    if (NULL != fatObj) 
    {
        type = fatObj->GetObjectType();
        delete fatObj;
    }

    return type;
}


/// @brief IsExist
/// @param name 
/// @param type
/// @return 
bool FatVolume::IsExist(const char* name, FileType type)
{
    return (type == GetFileType(name));
}


/// @brief Remove
/// @param name 
/// @return 
bool FatVolume::Remove(const char* name)
{
    FatObject* fatObj = SearchPath(name);

    if (NULL != fatObj)
    {
        if (FileType::_File     == fatObj->GetObjectType() ||
            FileType::_Diretory == fatObj->GetObjectType())
        {
            FatFolder(diskio).Remove(fatObj);
            delete fatObj;
            return true;
        }
    }

    return false;
}


/// @brief GetSystemID
/// @return system id
uint32_t FatSystem::GetSystemID()
{
    const static uint32_t systemID = 11;
    return systemID;
}


/// @brief CreateVolume
/// @return fat volume
FileVol* FatSystem::CreateVolume()
{
    return new FatVolume();
}


///Register file system
REGISTER_FS(new FatSystem(), fat);
