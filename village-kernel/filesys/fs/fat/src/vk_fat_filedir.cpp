//###########################################################################
// vk_fat_filedir.cpp
// Definitions of the functions that manage fat file dir
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_fat_filedir.h"
#include "vk_fat_folder.h"


/// @brief Constructor
/// @param diskio 
FatFile::FatFile(FatDiskio& diskio)
    :diskio(diskio),
    fatInfo(diskio.GetInfo()),
    object(NULL),
    filemode(0),
    fileSize(0),
    fstClust(0),
    sectorSize(0),
    clustSize(0),
    buflen(0),
    buffer(NULL)
{
}


/// @brief Open
/// @param fatObj 
void FatFile::Open(FatObject* fatObj, int mode)
{
    object   = fatObj;
    filemode = mode;
    fileSize = fatObj->GetFileSize();

    if (fileSize)
    {
        fstClust   = fatObj->GetFirstCluster();
        sectorSize = (fileSize + (fatInfo.bytesPerSec - 1)) / fatInfo.bytesPerSec;
        clustSize  = (sectorSize + (fatInfo.secPerClust - 1)) / fatInfo.secPerClust;
        buflen     =  clustSize * fatInfo.secPerClust * fatInfo.bytesPerSec;
        buffer     = (char*)new char[buflen]();
        clustSize  = diskio.ReadCluster(buffer, fstClust, clustSize);
    }
}


/// @brief Write
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int FatFile::Write(char* data, int size, int offset)
{
    int buffOffset = 0;

    if (filemode & FileMode::_OpenAppend)
        buffOffset = this->fileSize;
    else if (filemode & FileMode::_Write)
        buffOffset = 0;

    fileSize = buffOffset + size;

    if (fileSize > buflen)
    {
        sectorSize = (fileSize + (fatInfo.bytesPerSec - 1)) / fatInfo.bytesPerSec;
        clustSize  = (sectorSize + (fatInfo.secPerClust - 1)) / fatInfo.secPerClust;
        int   newBuflen = (clustSize * fatInfo.secPerClust * fatInfo.bytesPerSec);
        char* newBuffer = (char*)new char[newBuflen]();

        if (buffOffset) memcpy((void*)newBuffer, (const void*)buffer, buflen);
        delete[] buffer;
        buflen = newBuflen;
        buffer = newBuffer;
    }

    memcpy((void*)(buffer + buffOffset), (const void*)(data + offset), size);

    filemode = FileMode::_OpenAppend;

    return size;
}


/// @brief Read
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int FatFile::Read(char* data, int size, int offset)
{
    if (fileSize)
    {
        if (fileSize < size) size = fileSize;

        memcpy((void*)(data + offset), (const void*)buffer, size);
        
        return size;
    }
    return 0;
}


/// @brief Size
/// @return 
int FatFile::Size()
{
    return fileSize;
}


/// @brief Flush
void FatFile::Flush()
{
    if (clustSize == diskio.WriteCluster(buffer, fstClust, clustSize))
    {
        object->SetFileSize(fileSize);
        FatFolder(diskio).Update(object);
    }
}


/// @brief Close
void FatFile::Close()
{
    delete[] buffer;
}


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
