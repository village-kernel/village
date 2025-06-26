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
    return diskio.Setup(device, startingLBA);
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
        *fatObj = *found;
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

    if (NULL == fatObj || FileType::_Diretory != fatObj->GetObjectType()) return NULL;
    
    return FatFolder(diskio, fatObj).Create(BaseName(path), attr);
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
            fatObj.SetShortName(name);

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
            name = fatObj.GetShortName();
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
        FatFile* file = new FatFile(diskio);

        file->Open(fatObj, mode);
  
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
        return file->Write(data, size, offset);
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

    if (NULL != file)
    {
        return file->Read(data, size, offset);
    }

    return 0;
}


/// @brief Size
/// @param fd 
/// @return 
int FatVolume::Size(int fd)
{
    FatFile* file = fatFiles.GetItem(fd);

    return (NULL != file) ? file->Size() : 0;
}


/// @brief Flush
/// @param fd 
void FatVolume::Flush(int fd)
{
    FatFile* file = fatFiles.GetItem(fd);
    
    if (NULL != file) file->Flush();
}


/// @brief Close
/// @param fd 
void FatVolume::Close(int fd)
{
    FatFile* file = fatFiles.GetItem(fd);
    
    if (NULL != file)
    {
        file->Close();
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
        FatDir* dir = new FatDir(diskio);
        
        dir->Open(fatObj, mode);

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
        return dir->Read(dirs, size, offset);
    }

    return 0;
}


/// @brief SizeDir
/// @param fd 
/// @return 
int FatVolume::SizeDir(int fd)
{
    FatDir* dir = fatDirs.GetItem(fd);
    
    return (NULL != dir) ? dir->Size() : 0;
}


/// @brief CloseDir
/// @param fd 
void FatVolume::CloseDir(int fd)
{
    FatDir* dir = fatDirs.GetItem(fd);
    
    if (NULL != dir)
    {
        dir->Close();
        fatDirs.Remove(dir, fd);
        delete dir;
    }
}


/// @brief IsExist
/// @param name 
/// @param type
/// @return 
bool FatVolume::IsExist(const char* name, FileType type)
{
    FileType res = FileType::_Unknown;

    FatObject* fatObj = SearchPath(name);

    if (NULL != fatObj) 
    {
        res = fatObj->GetObjectType();
        delete fatObj;
    }

    return (res == type);
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
