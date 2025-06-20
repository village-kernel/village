//###########################################################################
// vk_fat_folder.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vk_fat_folder.h"


/// @brief Constructor
FatFolder::FatFolder(FatDiskio& diskio, FatObject* fatObj)
    :diskio(diskio),
    fatInfo(diskio.GetInfo()),
    buffer(NULL),
    parent(NULL)
{
    Open(fatObj);
}


/// @brief Destructor
FatFolder::~FatFolder()
{
    Close();
}


/// @brief Calc first sector
/// @param clust 
/// @param sector 
void FatFolder::CalcFirstSector()
{
    if (NULL != parent)
    {
        if (parent->GetFirstCluster() < 2)
        {
            if (FatDiskio::_FAT16 == fatInfo.fatType)
            {
                entidx.clust  = 0;
                entidx.sector = fatInfo.firstRootSector;
            }
            else if (FatDiskio::_FAT32 == fatInfo.fatType)
            {
                entidx.clust  = fatInfo.rootClust;
                entidx.sector = diskio.ClusterToSector(entidx.clust);
            }
        }
        else
        {
            entidx.clust  = parent->GetFirstCluster();
            entidx.sector = diskio.ClusterToSector(entidx.clust);
        }
    }
}


/// @brief Calc next sector
/// @param clust 
/// @param sector 
void FatFolder::CalcNextSector()
{
    //FAT16 root dir
    if (entidx.clust < 2)
    {
        uint32_t dirEndedSec = fatInfo.firstRootSector + fatInfo.countOfRootSecs;
        entidx.sector = (++entidx.sector < dirEndedSec) ? entidx.sector : 0;
    }
    //FAT data dir
    else
    { 
        if ((++entidx.sector - diskio.ClusterToSector(entidx.clust)) >= fatInfo.secPerClust)
        {
            entidx.clust = diskio.GetNextCluster(entidx.clust);
            entidx.sector = (0 != entidx.clust) ? diskio.ClusterToSector(entidx.clust) : 0;
        }
    }
}


/// @brief Read union entries
void FatFolder::ReadEntries()
{
    diskio.ReadSector((char*)buffer, entidx.sector);
}


/// @brief Write union entries
void FatFolder::WriteEntries()
{
    diskio.WriteSector((char*)buffer, entidx.sector);
}


/// @brief Iterator begin
bool FatFolder::ReadBegin()
{
    entidx = EntryIndex();

    CalcFirstSector();
    ReadEntries();

    return true;
}


/// @brief Iterator next
bool FatFolder::ReadNext()
{
    if (++entidx.index >= fatInfo.entriesPerSec)
    {
        CalcNextSector();
        if (0 != entidx.sector)
        {
            ReadEntries();
            entidx.index = 0;
        }
        else return false;
    }
    return true;
}


/// @brief Iterator next
bool FatFolder::WriteNext()
{
    if (++entidx.index >= fatInfo.entriesPerSec)
    {
        WriteEntries();

        CalcNextSector();
        if (0 != entidx.sector)
        {
            ReadEntries();
            entidx.index = 0;
        }
        else return false;
    }
    return true;
}


/// @brief Iterator is ended
/// @return res
bool FatFolder::IsReadEnd()
{
    return 0 == entidx.sector;
}


/// @brief Iterator item
/// @return 
FatEntry& FatFolder::Item()
{
    return buffer[entidx.index];
}


/// @brief Alloc space
/// @param size 
/// @return res
bool FatFolder::Alloc(uint32_t size)
{
    bool        isStart = true;
    uint32_t    freeCnt = 0;
    EntryIndex  backup;

    for (ReadBegin(); !IsReadEnd(); ReadNext())
    {
        if (!Item().IsValid())
        {
            if (true == isStart)
            {
                isStart = false;
                backup = entidx;
            }
            if (++freeCnt >= size)
            {
                entidx = backup;
                return true;
            }
        }
        else
        {
            isStart = true;
            freeCnt = 0;
        }
    }

    return false;
}


/// @brief Pop entry
/// @param pop 
/// @param size 
/// @return size
uint32_t FatFolder::Pop(FatEntry* pop, uint32_t size)
{
    for (uint32_t i = 0; i < size; i++)
    {
        pop[i] = buffer[entidx.index];
    
        if ((i < size - 1) && !ReadNext()) return i;
    }
    return size;
}


/// @brief Push entry
/// @param push 
/// @param size 
/// @return size
uint32_t FatFolder::Push(FatEntry* push, uint32_t size)
{
    ReadEntries();

    for (uint32_t i = 0; i < size; i++)
    {
        buffer[entidx.index] = push[i];

        if ((i < size - 1) && !WriteNext()) return i;
    }

    WriteEntries();

    return size;
}


/// @brief Check dir name
/// @param fatObj 
/// @return 
bool FatFolder::CheckDirName(FatObject* fatObj)
{
    for (fatObjs.Begin(); !fatObjs.IsEnd(); fatObjs.Next())
    {
        if (0 == strncmp(fatObjs.Item()->GetShortName(), fatObj->GetShortName(), 11)) return false;
    }
    return true;
}


/// @brief Open
/// @param fatObj 
void FatFolder::Open(FatObject* fatObj)
{
    this->parent = fatObj;

    buffer = (FatEntry*)new char[fatInfo.bytesPerSec]();

    if (NULL != parent)
    {
        if (FileType::_Diretory == parent->GetObjectType())
        {
            for (ReadBegin(); !IsReadEnd(); ReadNext())
            {
                if (Item().IsValid())
                {
                    uint8_t size = Item().GetStoreSize();
                    FatEntry* entries = new FatEntry[size]();
                    FatObject* fatObj = new FatObject(entries);
                    fatObj->SetEntryIndex(entidx);

                    if (Pop(entries, size) == size)
                    {
                        fatObj->Setup(entries);
                        fatObjs.Add(fatObj);
                    }
                    else delete fatObj;
                }
            }
        }
    }
}


/// @brief Search
/// @param name 
/// @return 
FatObject* FatFolder::Search(const char* name)
{
    for (fatObjs.Begin(); !fatObjs.IsEnd(); fatObjs.Next())
    {
        char* dirname = fatObjs.Item()->GetObjectName();

        if (0 == strcmp(dirname, name))
        {
            return fatObjs.Item();
        }
    }
    return NULL;
}


/// @brief Create
/// @param name 
/// @param attr 
/// @return 
FatObject* FatFolder::Create(const char* name, int attr)
{
    FatObject* child = new FatObject();
    
    //Set short name, attr and clust
    child->Setup(name);
    child->SetAttribute(attr);
    child->SetFirstCluster(diskio.AllocCluster());

    //Generate number name
    if (child->IsLongName())
    {
        for (uint8_t i = 1; i < 100; i++)
        {
            child->GenNumName(i);
            if (CheckDirName(child)) break;
        }
    }

    //Stored child object
    if (1 == Write(child, 1))
    {
        if (FatDefs::_AttrDirectory == attr)
        {
            FatObject objs[2];
            objs[0].SetupDot(child);
            objs[1].SetupDotDot(parent);
            FatFolder(diskio, child).Write(objs, 2);
        }
        return child;
    }

    return NULL;
}


/// @brief Write
/// @param objs 
/// @param size 
/// @return 
int FatFolder::Write(FatObject* objs, int size)
{
    for (int i = 0; i < size; i++)
    {
        uint32_t storeSize = objs[i].GetStoreSize();

        if (Alloc(storeSize))
        {
            objs[i].SetEntryIndex(entidx);

            if (storeSize == Push(objs[i].GetEntries(), storeSize))
            {
                fatObjs.Add(&objs[i]);
            }
        }
        else return i;
    }
    return size;
}


/// @brief Read
/// @param objs 
/// @param size 
/// @return 
int FatFolder::Read(FatObject* objs, int size)
{
    int objSize = fatObjs.GetSize();

    if (size > objSize) size = objSize;

    for (int i = 0; i < size; i++)
    {
        objs[i] = *fatObjs.GetItem(i);
    }
    
    return size;
}


/// @brief Remove
void FatFolder::Remove(FatObject* fatObj)
{
    if (NULL != fatObj)
    {
        fatObj->SetOjectFree();
        entidx = fatObj->GetEntryIndex();
        Push(fatObj->GetEntries(), fatObj->GetStoreSize());
    }
}


/// @brief Update
void FatFolder::Update(FatObject* fatObj)
{
    if (NULL != fatObj)
    {
        entidx = fatObj->GetEntryIndex();
        Push(fatObj->GetEntries(), fatObj->GetStoreSize());
    }
}


/// @brief Size
/// @return 
int FatFolder::Size()
{
    return fatObjs.GetSize();
}


/// @brief Close
void FatFolder::Close()
{
    if (NULL != buffer) delete[] buffer;

    for (fatObjs.Begin(); !fatObjs.IsEnd(); fatObjs.Next())
    {
        delete fatObjs.Item();
    }

    fatObjs.Release();
}
