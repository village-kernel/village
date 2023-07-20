//###########################################################################
// FAT.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FileSystem.h"
#include "Kernel.h"
#include "FAT.h"
#include "Debug.h"


/// @brief Constructor
FAT::FAT()
	:disk(NULL),
	dbr(NULL),
	relativeSectors(0)
{
}


/// @brief Deconstructor
FAT::~FAT()
{
}


/// @brief 
/// @param fcbName 
/// @return 
uint8_t FAT::ChkSum(char* fcbName)
{
	uint8_t sum = 0;

	for (int16_t fcbNameLen = 11; fcbNameLen != 0; fcbNameLen--)
	{
		sum = ((sum & 1) ? 0x80 : 0) + (sum >> 1) + *fcbName++;
	}

	return sum;
}


/// @brief Read DBR
int FAT::ReadDBR()
{
	static const uint8_t dbr_sector = 0;

	dbr = new DBR();

	if (NULL != dbr)
	{
		ReadDisk((char*)dbr, 1, dbr_sector);
		
		if (magic == dbr->magic) return _OK;
	}

	return _ERR;
}


/// @brief 
/// @return 
int FAT::InitVolume()
{
	fat->countOfClusters = fat->dataSec / dbr->bpb.secPerClus;

	if (fat->countOfClusters < 4085)
		fat->type = _FAT12;
	else if (fat->countOfClusters < 65525)
		fat->type = _FAT16;
	else
		fat->type = _FAT32;

	if (_FAT16 == fat->type)
		fat->FATOffset = fat->countOfClusters * 2;
	else if (_FAT32 == fat->type)
		fat->FATOffset = fat->countOfClusters * 4;

	fat->FATSecNum = dbr->bpb.rsvdSecCnt + (fat->FATOffset / dbr->bpb.bytsPerSec);

	fat->FATEntOffset = (fat->FATOffset % dbr->bpb.bytsPerSec);

	char* secBuf = new char[512]();

	ReadDisk(secBuf, 1, fat->FATSecNum);

	if (_FAT16 == fat->type)
		fat->FAT16ClusEntryVal = *((uint32_t*)&secBuf[fat->FATEntOffset]);
	else if (_FAT32 == fat->type)
		fat->FAT32ClusEntryVal = (*((uint32_t*)&secBuf[fat->FATEntOffset])) & 0x0fffffff;
	
	delete[] secBuf;

	return _OK;
}


/// @brief 
/// @return 
int FAT::CheckFS()
{
	fat = new FATData();

	if (NULL != fat)
	{
		if (0 != dbr->bpb.FATSz16)
			fat->FATSz = dbr->bpb.FATSz16;
		else
			fat->FATSz = dbr->fat32.FATSz32;
		
		if (0 != dbr->bpb.totSec16)
			fat->totSec = dbr->bpb.totSec16;
		else
			fat->totSec = dbr->bpb.totSec32;

		fat->firstRootDirSecNum = dbr->bpb.rsvdSecCnt + (dbr->bpb.numFATs * fat->FATSz);
		fat->rootDirSectors = ((dbr->bpb.rootEntCnt * 32) + (dbr->bpb.bytsPerSec - 1)) / dbr->bpb.bytsPerSec;
		
		fat->firstDataSector = dbr->bpb.rsvdSecCnt + (dbr->bpb.numFATs * fat->FATSz) + fat->rootDirSectors;
		fat->dataSec = fat->totSec - (dbr->bpb.rsvdSecCnt + (dbr->bpb.numFATs * fat->FATSz) - fat->rootDirSectors);

		return _OK;
	}

	return _ERR;
}


/// @brief 
/// @param dirName 
/// @param flag 
/// @return 
void FAT::ShortNameLowedCase(char* name, int flag)
{
	//Name body (8 byte)
	if ((flag & _NS_BODY) == _NS_BODY)
	{
		for (uint8_t i = 0; i < 8; i++)
		{
			if (name[i] >= 'A' && name[i] <= 'Z') name[i] = name[i] + 0x20;
		}
	}

	//Name ext (3 byte)
	if ((flag & _NS_EXT) == _NS_EXT)
	{
		for (uint8_t i = 8; i < 11; i++)
		{
			if (name[i] >= 'A' && name[i] <= 'Z') name[i] = name[i] + 0x20;
		}
	}
}


/// @brief Get short name
/// @param dirName 
/// @param dir 
/// @return 
void FAT::GetShortName(char* dirName, FATSDir* dir)
{
	uint8_t pos = 0;

	//8.3 name upper case -> lowed case
	ShortNameLowedCase(dir->name, dir->NTRes);

	//8.3 name body
	for (uint8_t i = 0; i < 8; i++)
	{
		if (' ' !=  dir->name[i])
		{
			dirName[pos++] = dir->name[i];
		} 
		else break;
	}

	//8.3 name dot
	if (' ' != dir->name[8]) dirName[pos++] = '.';

	//8.3 name ext
	for (uint8_t i = 8; i < 11; i++)
	{
		if (' ' != dir->name[i])
		{
			dirName[pos++] = dir->name[i]; 
		}
		else break;
	}

	//String EOC
	dirName[pos] = '\0';
}


/// @brief 
/// @param dirName 
/// @param dir 
/// @return 
void FAT::GetLongName(char* dirName, FATLDir* ldir, FATSDir* sdir)
{
	uint8_t pos = 0;
	uint8_t n = ldir[0].ord - 0x40;
	
	//Loop for sequence of long directory entries
	while (n--)
	{
		//Chksum
		if (ldir[n].chksum != ChkSum(sdir->name)) return;

		//Part 1 of long name 
		for (uint8_t i = 0; i < 10; i += 2)
		{
			if (0xff != ldir[n].name1[i])
			{
				dirName[pos++] = ldir[n].name1[i];
			}
			else break;
		}

		//Part 2 of long name 
		for (uint8_t i = 0; i < 11; i += 2)
		{
			if (0xff != ldir[n].name2[i])
			{
				dirName[pos++] = ldir[n].name2[i];
			}
			else return;
		}

		//Part 3 of long name
		for (uint8_t i = 0; i < 4; i += 2)
		{
			if (0xff != ldir[n].name3[i])
			{
				dirName[pos++] = ldir[n].name3[i];
			}
			else return;
		}
	}
}


/// @brief 
/// @param clusHI 
/// @param clusLO 
/// @return 
uint32_t FAT::CalcFirstSerctorOfCluster(uint16_t clusHI, uint16_t clusLO)
{
	uint32_t cluster = (uint32_t)clusHI << 16 | clusLO;
	return ((cluster - 2) * dbr->bpb.secPerClus) + fat->firstDataSector;
}


/// @brief 
/// @param data 
/// @param SecSize 
/// @param sector 
void FAT::ReadDisk(char* data, uint32_t secSize, uint32_t sector)
{
	if (NULL != disk)
	{
		disk->Read((uint8_t*)data, secSize, sector + relativeSectors);
	}	
}


/// @brief 
/// @param data 
/// @param dir 
int FAT::ReadFile(char* data, uint32_t size, FATSDir* dir)
{
	uint32_t secOfClus = CalcFirstSerctorOfCluster(dir->fstClusHI, dir->fstClusLO);
	uint16_t secSize = (dir->fileSize + (dbr->bpb.bytsPerSec - 1)) / dbr->bpb.bytsPerSec;
	
	char* file = (char*)new char[secSize * dbr->bpb.bytsPerSec]();

	ReadDisk(file, secSize, secOfClus);
	memcpy((void*)data, (const void*)file, size);
	
	delete[] file;

	return size;
}


/// @brief 
/// @param dir 
/// @return 
uint32_t FAT::FileSize(FATSDir* dir)
{
	return dir->fileSize;
}


/// @brief 
/// @param ldir 
/// @param sdir 
void FAT::DealDir(FATSDir* sdir, char* dirName)
{
	if ((sdir->attr & (_ATTR_DIRECTORY | _ATTR_VOLUME_ID)) == 0x00)
	{
		debug.Output(Debug::_Lv2, "Found a file: %s", dirName);
	}
	else if ((sdir->attr & (_ATTR_DIRECTORY | _ATTR_VOLUME_ID)) == _ATTR_DIRECTORY)
	{
		debug.Output(Debug::_Lv2, "Found a directory: %s", dirName);
	}
	else if ((sdir->attr & (_ATTR_DIRECTORY | _ATTR_VOLUME_ID)) == _ATTR_VOLUME_ID)
	{
		debug.Output(Debug::_Lv2, "Found a volume label: %s", dirName);
	}
	else
	{
		debug.Output(Debug::_Lv2, "Found an invalid directory entry");
	}
}


/// @brief 
/// @param dirSecNum 
/// @param dirSecSize 
FAT::FATSDir* FAT::ReadDir(uint32_t dirSecNum, uint32_t dirSecSize, const char* readDir)
{
	char* secBuf  = new char[dbr->bpb.bytsPerSec]();
	char* dirName = new char[100]();

	FATSDir* res = NULL;
	bool isFound = false;

	for (uint32_t sec = 0; sec < dirSecSize; sec++)
	{
		ReadDisk(secBuf, 1, dirSecNum + sec);
		uint8_t* buff = (uint8_t*)(secBuf);

		while (((uint32_t)buff - (uint32_t)secBuf) < dbr->bpb.bytsPerSec)
		{
			FATLDir* ldir = (FATLDir*)(buff);
			FATSDir* sdir;
			
			//Found an active long name sub-component.
			if (((ldir->attr & _ATTR_LONG_NAME_MASK) == _ATTR_LONG_NAME) && (ldir->ord != 0xE5))
			{
				uint8_t  n = ldir->ord - 0x40;
				uint32_t allocSize = (n + 1) * 32;
				uint8_t* allocBuff = (uint8_t*)new char[allocSize]();
				ldir = (FATLDir*)allocBuff;
				sdir = (FATSDir*)(allocBuff + (n * 32));

				uint32_t remaining = dbr->bpb.bytsPerSec - ((uint32_t)buff - (uint32_t)secBuf);

				if (allocSize > remaining)
				{
					memcpy((void*)allocBuff, (const void*)buff, remaining);
					
					sec++; ReadDisk(secBuf, 1, dirSecNum + sec); buff = (uint8_t*)(secBuf);
					
					uint32_t read = allocSize - remaining;
					if (read) memcpy((void*)(allocBuff + remaining), (const void*)buff, read);
					
					buff += read;
				}
				else
				{
					memcpy((void*)allocBuff, (const void*)buff, allocSize);
					buff += allocSize;
				}

				GetLongName(dirName, ldir, sdir);
				
				if (0 == strcmp(dirName, readDir))
				{
					res = new FATSDir();
					memcpy((void*)res, (const void*)sdir, 32);
					isFound = true;
				}

				delete[] allocBuff;
			}
			else
			{
				if ((ldir->ord != 0) && (ldir->ord != 0xE5))
				{
					sdir = (FATSDir*)(buff);

					GetShortName(dirName, sdir);

					if (0 == strcmp(dirName, readDir))
					{
						res = new FATSDir();
						memcpy((void*)res, (const void*)sdir, 32);
						isFound = true;
					}
				}

				buff += 32;
			}

			if (isFound) break;
		}

		if (isFound) break;
	}

	delete[] secBuf;
	delete[] dirName;
	return res;
}


/// @brief 
/// @param name 
/// @return 
FAT::FATSDir* FAT::SearchDir(const char* name)
{
	regex.Split(name, '/');
	char**  dirs = regex.ToArray();
	uint8_t deep = regex.Size();
	
	uint32_t dirSecNum = fat->firstRootDirSecNum;
	uint32_t dirSecSize = fat->rootDirSectors;

	FATSDir* res = NULL;

	for (uint8_t i = 0; i < deep; i++)
	{
		res = ReadDir(dirSecNum, dirSecSize, dirs[i]);

		if (NULL != res)
		{
			dirSecNum = CalcFirstSerctorOfCluster(res->fstClusHI, res->fstClusLO);
			dirSecSize = 1;
		}
		else
		{
			debug.Output(Debug::_Lv2, "%s file not found", name);
			return NULL;
		}
	}

	return res;
}


/// @brief FAT mount
/// @return 
int FAT::Mount(const char* path, const char* mount, int opt, int fstSecNum)
{
	relativeSectors = fstSecNum;

	disk = device.GetDriver(DriverID::_storage + 1);
	
	if (NULL == disk)
	{
		debug.Error("Not disk driver found");
		return _ERR;
	}

	if (_ERR == ReadDBR())
	{
		debug.Error("Not DBR found");
		return _ERR;
	}

	if (_ERR == CheckFS())
	{
		debug.Error("Not filesystem found");
		return _ERR;
	}

	debug.Output(Debug::_Lv2, "%s -> %s mount successful", path, mount);
	return _OK;
}


/// @brief FAT unmount
/// @return 
int FAT::Unmount(const char* mount)
{
	return _OK;
}


/// @brief FAT open
/// @param name 
/// @param mode 
/// @return 
int FAT::Open(const char* name, int mode)
{
	dir = SearchDir(name);

	if (NULL == dir) return _ERR;

	return _OK;
}


/// @brief FAT write
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int FAT::Write(char* data, int size, int offset)
{
	return 0;
}


/// @brief FAT read
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int FAT::Read(char* data, int size, int offset)
{
	return ReadFile(data, size, dir);
}


/// @brief FAT seek
/// @param offset 
/// @return 
int FAT::Seek(int offset)
{
	return 0;
}


/// @brief FAT rename
/// @param old 
/// @param now 
/// @return 
int FAT::Rename(const char* old, const char* now)
{
	return 0;
}


/// @brief FAT copy
/// @param from 
/// @param to 
/// @return 
int FAT::Copy(const char* from, const char* to)
{
	return 0;
}


/// @brief FAT remove
/// @return 
int FAT::Remove()
{
	return 0;
}


/// @brief FAT size
/// @return 
int FAT::Size()
{
	return FileSize(dir);
}


/// @brief FAT close
/// @return 
int FAT::Close()
{
	return 0;
}


///Register file system
REGISTER_FS(new FAT(), fat);
