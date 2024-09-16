//###########################################################################
// FatFolder.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatFolder.h"


/// @brief Constructor
FatFolder::FatFolder(FatDiskio& fatDisk, FatObject* fatObj)
	:fatDisk(fatDisk),
	fatInfo(fatDisk.GetInfo()),
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
				entloc.clust  = 0;
				entloc.sector = fatInfo.firstRootSector;
			}
			else if (FatDiskio::_FAT32 == fatInfo.fatType)
			{
				entloc.clust  = fatInfo.rootClust;
				entloc.sector = fatDisk.ClusterToSector(entloc.clust);
			}
		}
		else
		{
			entloc.clust  = parent->GetFirstCluster();
			entloc.sector = fatDisk.ClusterToSector(entloc.clust);
		}
	}
}


/// @brief Calc next sector
/// @param clust 
/// @param sector 
void FatFolder::CalcNextSector()
{
	//FAT16 root dir
	if (entloc.clust < 2)
	{
		uint32_t dirEndedSec = fatInfo.firstRootSector + fatInfo.countOfRootSecs;
		entloc.sector = (++entloc.sector < dirEndedSec) ? entloc.sector : 0;
	}
	//FAT data dir
	else
	{ 
		if ((++entloc.sector - fatDisk.ClusterToSector(entloc.clust)) >= fatInfo.secPerClust)
		{
			entloc.clust = fatDisk.GetNextCluster(entloc.clust);
			entloc.sector = (0 != entloc.clust) ? fatDisk.ClusterToSector(entloc.clust) : 0;
		}
	}
}


/// @brief Read union entries
void FatFolder::ReadEntries()
{
	fatDisk.ReadSector((char*)buffer, entloc.sector);
}


/// @brief Write union entries
void FatFolder::WriteEntries()
{
	fatDisk.WriteSector((char*)buffer, entloc.sector);
}


/// @brief Iterator begin
bool FatFolder::ReadBegin()
{
	entloc = FatEntryLoc();

	CalcFirstSector();
	ReadEntries();

	return true;
}


/// @brief Iterator next
bool FatFolder::ReadNext()
{
	if (++entloc.index >= fatInfo.entriesPerSec)
	{
		CalcNextSector();
		if (0 != entloc.sector)
		{
			ReadEntries();
			entloc.index = 0;
		}
		else return false;
	}
	return true;
}


/// @brief Iterator next
bool FatFolder::WriteNext()
{
	if (++entloc.index >= fatInfo.entriesPerSec)
	{
		WriteEntries();

		CalcNextSector();
		if (0 != entloc.sector)
		{
			ReadEntries();
			entloc.index = 0;
		}
		else return false;
	}
	return true;
}


/// @brief Iterator is ended
/// @return res
bool FatFolder::IsReadEnd()
{
	return 0 == entloc.sector;
}


/// @brief Find free space
/// @param size 
/// @return res
bool FatFolder::Find(uint32_t size)
{
	bool        isStart = true;
	uint32_t    freeCnt = 0;
	FatEntryLoc backup;

	for (ReadBegin(); !IsReadEnd(); ReadNext())
	{
		if (!buffer[entloc.index].IsValid())
		{
			if (true == isStart)
			{
				isStart = false;
				backup = entloc;
			}
			if (++freeCnt >= size)
			{
				entloc = backup;
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
		pop[i] = buffer[entloc.index];
	
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
		buffer[entloc.index] = push[i];

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


/// @brief 
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
				if (buffer[entloc.index].IsValid())
				{
					uint8_t size = buffer[entloc.index].GetStoreSize();
					FatEntry* entries = new FatEntry[size]();
					FatObject* fatObj = new FatObject(entries);
					fatObj->SetFatEntryLoc(entloc);

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
	child->SetFirstCluster(fatDisk.AllocCluster());

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
			FatFolder(fatDisk, child).Write(objs, 2);
		}
		return child;
	}

	return NULL;
}


/// @brief Write
/// @param objs 
/// @param size 
/// @return 
uint32_t FatFolder::Write(FatObject* objs, uint32_t size)
{
	for (uint32_t i = 0; i < size; i++)
	{
		uint32_t storeSize = objs[i].GetStoreSize();

		if (Find(storeSize))
		{
			objs[i].SetFatEntryLoc(entloc);

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
uint32_t FatFolder::Read(FatObject* objs, uint32_t size)
{
	uint32_t fatSize = fatObjs.GetSize();

	size = (fatSize > size) ? fatSize : size;

	for (uint32_t i = 0; i < size; i++)
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
		entloc = fatObj->GetFatEntryLoc();
		Push(fatObj->GetEntries(), fatObj->GetStoreSize());
	}
}


/// @brief Update
void FatFolder::Update(FatObject* fatObj)
{
	if (NULL != fatObj)
	{
		entloc = fatObj->GetFatEntryLoc();
		Push(fatObj->GetEntries(), fatObj->GetStoreSize());
	}
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


/// @brief GetLists
/// @return 
List<FatObject*> FatFolder::GetLists()
{
	return fatObjs;
}
