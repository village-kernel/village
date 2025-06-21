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
    diskinf(diskio.GetInfo()),
    buffer(NULL),
    myself(NULL)
{
    Open(fatObj);
}


/// @brief Destructor
FatFolder::~FatFolder()
{
    Close();
}


/// @brief Iterator begin
bool FatFolder::ReadBegin()
{
    uint32_t fstClust = (NULL != myself) ? myself->GetFirstCluster() : 0;

    entidx = diskio.GetFristIndex(fstClust);

    diskio.ReadSector((char*)buffer, entidx.sector);

    return true;
}


/// @brief Iterator next
bool FatFolder::ReadNext()
{
    if (++entidx.index >= diskinf.entriesPerSec)
    {
        entidx = diskio.GetNextIndex(entidx);
        if (0 != entidx.sector)
        {
            diskio.ReadSector((char*)buffer, entidx.sector);
            entidx.index = 0;
        }
        else return false;
    }
    return true;
}


/// @brief Iterator next
bool FatFolder::WriteNext()
{
    if (++entidx.index >= diskinf.entriesPerSec)
    {
        diskio.WriteSector((char*)buffer, entidx.sector);

        entidx = diskio.GetNextIndex(entidx);
        if (0 != entidx.sector)
        {
            diskio.ReadSector((char*)buffer, entidx.sector);
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
    bool             isStart = true;
    uint32_t         freeCnt = 0;
    FatDiskio::Index backup;

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
/// @param entries 
/// @param size 
/// @return size
uint32_t FatFolder::Pop(FatEntry* entries, uint32_t size)
{
    for (uint32_t i = 0; i < size; i++)
    {
        entries[i] = buffer[entidx.index];
    
        if ((i < size - 1) && !ReadNext()) return i;
    }
    return size;
}


/// @brief Push entry
/// @param entries 
/// @param size 
/// @return size
uint32_t FatFolder::Push(FatEntry* entries, uint32_t size)
{
    diskio.ReadSector((char*)buffer, entidx.sector);

    for (uint32_t i = 0; i < size; i++)
    {
        buffer[entidx.index] = entries[i];

        if ((i < size - 1) && !WriteNext()) return i;
    }

    diskio.WriteSector((char*)buffer, entidx.sector);

    return size;
}


/// @brief Open
/// @param fatObj 
void FatFolder::Open(FatObject* selfObj)
{
    this->myself = selfObj;

    buffer = (FatEntry*)new char[diskinf.bytesPerSec]();

    if (NULL != myself)
    {
        if (FileType::_Diretory == myself->GetObjectType())
        {
            for (ReadBegin(); !IsReadEnd(); ReadNext())
            {
                if (Item().IsValid())
                {
                    uint8_t size = Item().GetStoreSize();
                    FatEntry* entries = new FatEntry[size]();
                    FatObject* fatObj = new FatObject(entries);
                    fatObj->SetIndex(entidx);

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


/// @brief Write
/// @param objs 
/// @param size 
/// @return 
int FatFolder::Write(FatObject* subObjs, int size)
{
    for (int i = 0; i < size; i++)
    {
        uint32_t storeSize = subObjs[i].GetStoreSize();

        if (Alloc(storeSize))
        {
            subObjs[i].SetIndex(entidx);

            if (storeSize == Push(subObjs[i].GetEntries(), storeSize))
            {
                fatObjs.Add(&subObjs[i]);
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
int FatFolder::Read(FatObject* subObjs, int size)
{
    int objSize = fatObjs.GetSize();

    if (size > objSize) size = objSize;

    for (int i = 0; i < size; i++)
    {
        subObjs[i] = *fatObjs.GetItem(i);
    }
    
    return size;
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


/// @brief Remove
void FatFolder::Remove(FatObject* selfObj)
{
    if (NULL != selfObj)
    {
        selfObj->SetOjectFree();
        entidx = selfObj->GetIndex();
        Push(selfObj->GetEntries(), selfObj->GetStoreSize());
    }
}


/// @brief Update
void FatFolder::Update(FatObject* selfObj)
{
    if (NULL != selfObj)
    {
        entidx = selfObj->GetIndex();
        Push(selfObj->GetEntries(), selfObj->GetStoreSize());
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


/// @brief Create
/// @param name 
/// @param attr 
/// @return 
FatObject* FatFolder::Create(const char* name, int attr)
{
    FatObject* newObj = new FatObject();
    
    //Set short name, attr and clust
    newObj->Setup(name);
    newObj->SetAttribute(attr);
    newObj->SetFirstCluster(diskio.AllocCluster());

    //Generate number name
    if (newObj->IsLongName())
    {
        for (uint8_t i = 1; i < 100; i++)
        {
            newObj->GenNumName(i);
            if (CheckDirName(newObj)) break;
        }
    }

    //Stored newObj object
    if (1 == Write(newObj, 1))
    {
        if (FatDefs::_AttrDirectory == attr)
        {
            FatObject objs[2];
            objs[0].SetupDot(newObj);
            objs[1].SetupDotDot(myself);
            FatFolder(diskio, newObj).Write(objs, 2);
        }
        return newObj;
    }

    return NULL;
}
