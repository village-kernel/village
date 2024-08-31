//###########################################################################
// FatEntries.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatEntries.h"


/// @brief Constructor
/// @param fatDisk 
/// @param object 
FatEntries::FatEntries(FatDiskio& fatDisk, FatObject* object)
	:fatDisk(fatDisk),
	volInfo(fatDisk.GetInfo()),
	index(0),
	clust(0),
	sector(0),
	unients(NULL),
	self(object),
	objIdx(0)
{
	Prepare();
}


/// @brief Destructor
FatEntries::~FatEntries()
{
	Release();
}


/// @brief Prepare
void FatEntries::Prepare()
{
	unients = (FatUnionEntry*)new char[volInfo.bytesPerSec]();

	if (NULL != self && FileType::_Diretory != self->GetObjectType()) return;

	for (ReadBegin(); !IsReadEnd(); ReadNext())
	{
		if (unients[index].IsValid())
		{
			uint8_t size = unients[index].GetStoreSize();
			FatUnionEntry* ufe = new FatUnionEntry[size]();
			FatObject* object = new FatObject(ufe);
			object->SetEntryLocInfo(index, clust, sector);

			if (Pop(ufe, size) == size)
			{
				object->Setup(ufe);
				objects.Add(object);
			}
			else delete object;
		}
	}
}


/// @brief Release
void FatEntries::Release()
{
	delete[] unients;

	for (objects.Begin(); !objects.IsEnd(); objects.Next())
	{
		delete objects.Item();
	}

	objects.Release();
}


/// @brief Calc first sector
/// @param clust 
/// @param sector 
void FatEntries::CalcFirstSector()
{
	if (NULL == self || self->GetFirstCluster() < 2)
	{
		if (FatDiskio::_FAT16 == volInfo.fatType)
		{
			clust  = 0;
			sector = volInfo.firstRootSector;
		}
		else if (FatDiskio::_FAT32 == volInfo.fatType)
		{
			clust  = volInfo.rootClust;
			sector = fatDisk.ClusterToSector(clust);
		}
	}
	else
	{
		clust  = self->GetFirstCluster();
		sector = fatDisk.ClusterToSector(clust);
	}
}


/// @brief Calc next sector
/// @param clust 
/// @param sector 
void FatEntries::CalcNextSector()
{
	//FAT16 root dir
	if (clust < 2)
	{
		uint32_t dirEndedSec = volInfo.firstRootSector + volInfo.countOfRootSecs;
		sector  = (++sector < dirEndedSec) ? sector : 0;
	}
	//FatDisk data dir
	else
	{ 
		if ((++sector - fatDisk.ClusterToSector(clust)) >= volInfo.secPerClust)
		{
			clust = fatDisk.GetNextCluster(clust);
			sector = (0 != clust) ? fatDisk.ClusterToSector(clust) : 0;
		}
	}
}


/// @brief Read union entries
void FatEntries::ReadUnionEntries()
{
	fatDisk.ReadSector((char*)unients, sector);
}


/// @brief Write union entries
void FatEntries::WriteUnionEntries()
{
	fatDisk.WriteSector((char*)unients, sector);
}


/// @brief Iterator begin
bool FatEntries::ReadBegin()
{
	index  = 0;
	clust  = 0;
	sector = 0;

	CalcFirstSector();
	ReadUnionEntries();

	return true;
}


/// @brief Iterator next
bool FatEntries::ReadNext()
{
	if (++index >= volInfo.entriesPerSec)
	{
		CalcNextSector();
		if (0 != sector)
		{
			ReadUnionEntries();
			index = 0;
		}
		else return false;
	}
	return true;
}


/// @brief Iterator next
bool FatEntries::WriteNext()
{
	if (++index >= volInfo.entriesPerSec)
	{
		WriteUnionEntries();

		CalcNextSector();
		if (0 != sector)
		{
			ReadUnionEntries();
			index = 0;
		}
		else return false;
	}
	return true;
}


/// @brief Iterator is ended
/// @return res
bool FatEntries::IsReadEnd()
{
	return 0 == sector;
}


/// @brief Find free space
/// @param size 
/// @return res
bool FatEntries::Find(uint32_t size)
{
	bool      isBackup  = true;
	uint32_t  bakIndex  = 0;
	uint32_t  bakClust  = 0;
	uint32_t  bakSector = 0;
	uint32_t  freeCount = 0;

	for (ReadBegin(); !IsReadEnd(); ReadNext())
	{
		if (!unients[index].IsValid())
		{
			if (true == isBackup)
			{
				isBackup  = false;
				bakIndex  = index;
				bakClust  = clust;
				bakSector = sector;
			}
			if (++freeCount >= size)
			{
				index  = bakIndex;
				clust  = bakClust;
				sector = bakSector;
				return true;
			}
		}
		else
		{
			isBackup  = true;
			freeCount = 0;
		}
	}

	return false;
}


/// @brief Pop entry
/// @param pop 
/// @param size 
/// @return size
uint32_t FatEntries::Pop(FatUnionEntry* pop, uint32_t size)
{
	for (uint32_t i = 0; i < size; i++)
	{
		pop[i] = unients[index];
	
		if ((i < size - 1) && !ReadNext()) return i;
	}
	return size;
}


/// @brief Push entry
/// @param push 
/// @param size 
/// @return size
uint32_t FatEntries::Push(FatUnionEntry* push, uint32_t size)
{
	ReadUnionEntries();

	for (uint32_t i = 0; i < size; i++)
	{
		unients[index] = push[i];

		if ((i < size - 1) && !WriteNext()) return i;
	}

	WriteUnionEntries();

	return size;
}


/// @brief Begin
void FatEntries::Begin()
{
	objIdx = 0;
}


/// @brief Next
void FatEntries::Next()
{
	if (objIdx < GetSize()) objIdx++;
}


/// @brief Is end
/// @return 
bool FatEntries::IsEnd()
{
	return objIdx >= GetSize();
}


/// @brief Get item
/// @return 
FatObject* FatEntries::Item()
{
	return objects.GetItem(objIdx);
}


/// @brief Get size
/// @return 
uint32_t FatEntries::GetSize()
{
	return objects.GetSize();
}


/// @brief Check dir name
/// @param object 
/// @return 
bool FatEntries::CheckDirName(FatObject* object)
{
	for (Begin(); !IsEnd(); Next())
	{
		if (0 == strncmp(Item()->GetShortName(), object->GetShortName(), 11)) return false;
	}
	return true;
}


/// @brief Create
/// @param name 
/// @param attr 
/// @return 
FatObject* FatEntries::Create(const char* name, int attr)
{
	FatObject* child = new FatObject();
	
	//Set short name, attr and clust
	child->SetupByName(name);
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

	//Get store size
	uint32_t size = child->GetStoreSize();

	//Put to disk
	if (Find(size))
	{
		child->SetEntryLocInfo(index, clust, sector);
		
		if (Push(child->GetUnionEntry(), size) == size)
		{
			if (FileType::_Diretory == child->GetObjectType())
			{
				FatObject objs[2];
				objs[0].SetupDot(child);
				objs[1].SetupDotDot(self);
				FatEntries(fatDisk, child).Write(objs, 2);
			}
			return child;
		}
	}

	return NULL;
}


/// @brief Write
/// @param objs 
/// @param size 
/// @return 
uint32_t FatEntries::Write(FatObject* objs, uint32_t size)
{
	for (uint32_t i = 0; i < size; i++)
	{
		uint32_t storeSize = objs[i].GetStoreSize();

		if (Find(storeSize) && Push(objs[i].GetUnionEntry(), storeSize) == storeSize)
		{
			objects.Add(&objs[i]);
		}
		else return i;
	}
	return size;
}


/// @brief Read
/// @param objs 
/// @param size 
/// @return 
uint32_t FatEntries::Read(FatObject* objs, uint32_t size)
{
	for (uint32_t i = 0; i < size; i++)
	{
		if (i < GetSize())
		{
			objs[i] = *objects.GetItem(i);
		}
		else return i;
	}
	return size;
}


/// @brief Remove
void FatEntries::Remove()
{
	self->SetEntryFree();
	self->GetEntryLocInfo(index, clust, sector);
	Push(self->GetUnionEntry(), self->GetStoreSize());
}


/// @brief Update
void FatEntries::Update()
{
	self->GetEntryLocInfo(index, clust, sector);
	Push(self->GetUnionEntry(), self->GetStoreSize());
}
