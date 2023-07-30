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
	startSector(0)
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


/// @brief Get short name
/// @param dirName 
/// @param dir 
/// @return 
void FAT::GetShortName(char* dirName, FATSDir* dir)
{
	uint8_t pos = 0;
	char*   name = dir->name;
	bool    isBodyLowedCase = (dir->NTRes & _NS_BODY) == _NS_BODY;
	bool    isExtLowedCase  = (dir->NTRes & _NS_EXT ) == _NS_EXT;
	
	//8.3 name body
	for (uint8_t i = 0; i < 8; i++)
	{
		if (' ' !=  name[i])
		{
			if (isBodyLowedCase && (name[i] >= 'A' && name[i] <= 'Z'))
				dirName[pos++] = name[i] + 0x20;
			else
				dirName[pos++] = name[i];
		} 
		else break;
	}

	//8.3 name dot
	if (' ' != name[8]) dirName[pos++] = '.';

	//8.3 name ext
	for (uint8_t i = 8; i < 11; i++)
	{
		if (' ' != name[i])
		{
			if (isExtLowedCase && (name[i] >= 'A' && name[i] <= 'Z'))
				dirName[pos++] = name[i] + 0x20;
			else
				dirName[pos++] = name[i]; 
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
/// @param data 
/// @param SecSize 
/// @param sector 
void FAT::ReadDisk(char* data, uint32_t secSize, uint32_t sector)
{
	if (NULL != disk)
	{
		disk->Read((uint8_t*)data, secSize, sector + startSector);
	}	
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
int FAT::CheckFS()
{
	fat = new FATData();

	if (NULL != fat)
	{
		//Calc fat size
		if (0 != dbr->bpb.FATSz16)
			fat->FATSz = dbr->bpb.FATSz16;
		else
			fat->FATSz = dbr->fat32.FATSz32;
		
		//Calc total sectors
		if (0 != dbr->bpb.totSec16)
			fat->totSec = dbr->bpb.totSec16;
		else
			fat->totSec = dbr->bpb.totSec32;

		//Calc fat12/16 root dir sector
		fat->firstRootDirSecNum = dbr->bpb.rsvdSecCnt + (dbr->bpb.numFATs * fat->FATSz);
		fat->rootDirSectors = ((dbr->bpb.rootEntCnt * dir_entry_size) + (dbr->bpb.bytsPerSec - 1)) / dbr->bpb.bytsPerSec;
		
		//Calc fat data sector
		fat->firstDataSector = dbr->bpb.rsvdSecCnt + (dbr->bpb.numFATs * fat->FATSz) + fat->rootDirSectors;
		fat->dataSec = fat->totSec - (dbr->bpb.rsvdSecCnt + (dbr->bpb.numFATs * fat->FATSz) - fat->rootDirSectors);

		//Calc counts of clusters
		fat->countOfClusters = fat->dataSec / dbr->bpb.secPerClus;

		//Detected fat type
		if (fat->countOfClusters < 4085)
			fat->type = _FAT12;
		else if (fat->countOfClusters < 65525)
			fat->type = _FAT16;
		else
			fat->type = _FAT32;

		//fat32 root cluster
		fat->rootClus = (_FAT32 == fat->type) ? dbr->fat32.rootClus : 0;

		return _OK;
	}

	return _ERR;
}


/// @brief 
/// @param clusHI 
/// @param clusLO 
/// @return 
uint32_t FAT::MergeCluster(uint16_t clusHI, uint16_t clusLO)
{
	return (uint32_t)clusHI << 16 | clusLO;
}


/// @brief 
/// @param clusHI 
/// @param clusLO 
/// @return 
uint32_t FAT::CalcSecNumOfFstClus(uint32_t clus)
{
	return ((clus - 2) * dbr->bpb.secPerClus) + fat->firstDataSector;
}


/// @brief 
/// @param clusHI 
/// @param clusLO 
/// @return 
uint32_t FAT::CalcSecNumOfNextClus(uint32_t clus)
{
	bool isEOC = false;
	uint32_t fatOffset = 0;
	uint32_t fatClusEntryVal = 0;

	if (_FAT16 == fat->type)
		fatOffset = clus * 2;
	else if (_FAT32 == fat->type)
		fatOffset = clus * 4;

	uint32_t thisFATSecNum = dbr->bpb.rsvdSecCnt + (fatOffset / dbr->bpb.bytsPerSec);
	uint32_t thisFATEntOffset = fatOffset % dbr->bpb.bytsPerSec;

	char* secBuff = new char[dbr->bpb.bytsPerSec]();
	
	ReadDisk(secBuff, 1, thisFATSecNum);

	if (_FAT16 == fat->type)
	{
		fatClusEntryVal = *((uint16_t*)&secBuff[thisFATEntOffset]);
		if (fatClusEntryVal >= fat16_eoc_flag) isEOC = true;
	}
	else if (_FAT32 == fat->type)
	{
		fatClusEntryVal = (*((uint32_t*)&secBuff[thisFATEntOffset])) & 0x0fffffff;
		if (fatClusEntryVal >= fat32_eoc_flag) isEOC = true;
	}
	
	delete[] secBuff;

	return isEOC ? 0 : ((fatClusEntryVal - 2) * dbr->bpb.secPerClus) + fat->firstDataSector;
}


/// @brief 
/// @param clusHI 
/// @param clusLO 
/// @return 
uint32_t FAT::CalcSecNumOfFstClus(uint16_t clusHI, uint16_t clusLO)
{
	uint32_t cluster = (uint32_t)clusHI << 16 | clusLO;
	return ((cluster - 2) * dbr->bpb.secPerClus) + fat->firstDataSector;
}


/// @brief 
/// @param clusHI 
/// @param clusLO 
/// @return 
uint32_t FAT::CalcSecNumOfNextClus(uint16_t clusHI, uint16_t clusLO)
{
	uint32_t cluster = (uint32_t)clusHI << 16 | clusLO;
	return CalcSecNumOfNextClus(cluster);
}


/// @brief 
/// @return 
char* FAT::MoveWindow(uint32_t clus, uint32_t seek)
{
	uint32_t secNum = CalcSecNumOfFstClus(clus);

	char* secBuff = new char[dbr->bpb.bytsPerSec * dbr->bpb.secPerClus]();
	
	ReadDisk(secBuff, dbr->bpb.secPerClus, secNum);
}


/// @brief 
/// @param data 
/// @param dir 
int FAT::ReadFile(char* data, uint32_t size, FATSDir* dir)
{
	uint32_t secNum = CalcSecNumOfFstClus(dir->fstClusHI, dir->fstClusLO);
	uint16_t secSize = (dir->fileSize + (dbr->bpb.bytsPerSec - 1)) / dbr->bpb.bytsPerSec;
	
	char* file = (char*)new char[secSize * dbr->bpb.bytsPerSec]();

	ReadDisk(file, secSize, secNum);
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
/// @param sdir 
int FAT::CheckDir(FATSDir* sdir)
{
	if ((sdir->attr & (_ATTR_DIRECTORY | _ATTR_VOLUME_ID)) == 0x00)
	{
		//Found a file
	}
	else if ((sdir->attr & (_ATTR_DIRECTORY | _ATTR_VOLUME_ID)) == _ATTR_DIRECTORY)
	{
		//Found a directory
	}
	else if ((sdir->attr & (_ATTR_DIRECTORY | _ATTR_VOLUME_ID)) == _ATTR_VOLUME_ID)
	{
		//Found a volume label
	}
	else
	{
		//Found an invalid directory entry
	}
	return _ERR;
}


/// @brief 
/// @param dirSecNum 
/// @param dirSecSize 
FAT::FATSDir* FAT::ReadRootDir(uint32_t dirSecNum, uint32_t dirSecSize, const char* readDir)
{
	char* secBuff = new char[dbr->bpb.bytsPerSec]();
	char* dirName = new char[short_name_size]();

	for (uint32_t sec = 0; sec < dirSecSize; sec++)
	{
		ReadDisk(secBuff, 1, dirSecNum + sec);
		char* tmpBuff = secBuff;

		while (((uint32_t)tmpBuff - (uint32_t)secBuff) < dbr->bpb.bytsPerSec)
		{
			FATLDir* ldir = (FATLDir*)(tmpBuff);
			FATSDir* sdir;
			
			//Found an active long name sub-component.
			if (((ldir->attr & _ATTR_LONG_NAME_MASK) == _ATTR_LONG_NAME) && (ldir->ord != dir_free_flag))
			{
				uint8_t  n = ldir->ord - dir_seq_flag;
				uint32_t allocSize = (n + 1) * dir_entry_size;
				char* ldirName  = new char[n * long_name_size]();
				char* allocBuff = new char[allocSize]();
				ldir = (FATLDir*)(allocBuff);
				sdir = (FATSDir*)(allocBuff + (n * dir_entry_size));
				
				uint32_t remaining = dbr->bpb.bytsPerSec - ((uint32_t)tmpBuff - (uint32_t)secBuff);

				if (allocSize > remaining)
				{
					memcpy((void*)allocBuff, (const void*)tmpBuff, remaining);
					
					sec++; ReadDisk(secBuff, 1, dirSecNum + sec); tmpBuff = secBuff;
					
					uint32_t read = allocSize - remaining;
					if (read) memcpy((void*)(allocBuff + remaining), (const void*)tmpBuff, read);
					
					tmpBuff += read;
				}
				else
				{
					memcpy((void*)allocBuff, (const void*)tmpBuff, allocSize);
					tmpBuff += allocSize;
				}

				GetLongName(ldirName, ldir, sdir);
				
				if (0 == strcmp(ldirName, readDir))
				{
					FATSDir* dir = new FATSDir();
					*dir = *sdir;
					delete[] secBuff;
					delete[] ldirName;
					delete[] allocBuff;
					return dir;
				}

				delete[] allocBuff;
				delete[] dirName;
			}
			else
			{
				if ((ldir->ord != 0) && (ldir->ord != dir_free_flag))
				{
					sdir = (FATSDir*)(tmpBuff);

					GetShortName(dirName, sdir);

					if (0 == strcmp(dirName, readDir))
					{
						FATSDir* dir = new FATSDir();
						*dir = *sdir;
						delete[] secBuff;
						delete[] dirName;
						return dir;
					}
				}

				tmpBuff += dir_entry_size;
			}
		}
	}

	delete[] secBuff;
	delete[] dirName;
	return NULL;
}



/// @brief 
/// @param dirSecNum 
/// @param dirSecSize 
FAT::FATSDir* FAT::ReadDir(uint32_t clus, const char* readDir)
{
	char* secBuff = new char[dbr->bpb.bytsPerSec]();
	char* dirName = new char[short_name_size]();

	uint32_t dirSecNum = CalcSecNumOfFstClus(clus);
	uint32_t dirSecSize = dbr->bpb.secPerClus;

	for (uint32_t sec = 0; sec < dirSecSize; sec++)
	{
		ReadDisk(secBuff, 1, dirSecNum + sec);
		char* tmpBuff = secBuff;

		while (((uint32_t)tmpBuff - (uint32_t)secBuff) < dbr->bpb.bytsPerSec)
		{
			FATLDir* ldir = (FATLDir*)(tmpBuff);
			FATSDir* sdir;
			
			//Found an active long name sub-component.
			if (((ldir->attr & _ATTR_LONG_NAME_MASK) == _ATTR_LONG_NAME) && (ldir->ord != dir_free_flag))
			{
				uint8_t  n = ldir->ord - dir_seq_flag;
				uint32_t allocSize = (n + 1) * dir_entry_size;
				char* ldirName  = new char[n * long_name_size]();
				char* allocBuff = new char[allocSize]();
				ldir = (FATLDir*)(allocBuff);
				sdir = (FATSDir*)(allocBuff + (n * dir_entry_size));
				
				uint32_t remaining = dbr->bpb.bytsPerSec - ((uint32_t)tmpBuff - (uint32_t)secBuff);

				if (allocSize > remaining)
				{
					memcpy((void*)allocBuff, (const void*)tmpBuff, remaining);
					
					sec++; ReadDisk(secBuff, 1, dirSecNum + sec); tmpBuff = secBuff;
					
					uint32_t read = allocSize - remaining;
					if (read) memcpy((void*)(allocBuff + remaining), (const void*)tmpBuff, read);
					
					tmpBuff += read;
				}
				else
				{
					memcpy((void*)allocBuff, (const void*)tmpBuff, allocSize);
					tmpBuff += allocSize;
				}

				GetLongName(ldirName, ldir, sdir);
				
				if (0 == strcmp(ldirName, readDir))
				{
					FATSDir* dir = new FATSDir();
					*dir = *sdir;
					delete[] secBuff;
					delete[] ldirName;
					delete[] allocBuff;
					return dir;
				}

				delete[] allocBuff;
				delete[] dirName;
			}
			else
			{
				if ((ldir->ord != 0) && (ldir->ord != dir_free_flag))
				{
					sdir = (FATSDir*)(tmpBuff);

					GetShortName(dirName, sdir);

					if (0 == strcmp(dirName, readDir))
					{
						FATSDir* dir = new FATSDir();
						*dir = *sdir;
						delete[] secBuff;
						delete[] dirName;
						return dir;
					}
				}

				tmpBuff += dir_entry_size;
			}
		}
	}

	delete[] secBuff;
	delete[] dirName;
	return NULL;
}


/// @brief 
/// @param name 
/// @return 
FAT::FATSDir* FAT::SearchDir(const char* name)
{
	regex.Split(name, '/');
	char**  path = regex.ToArray();
	uint8_t deep = regex.Size();
	
	FATSDir* dir;

	for (uint8_t i = 0; i < deep; i++)
	{
		if (0 == i)
		{
			if (_FAT16 == fat->type)
				dir = ReadRootDir(fat->firstRootDirSecNum, fat->rootDirSectors, path[i]);
			else
				dir = ReadDir(fat->rootClus, path[i]);
		}
		else
		{
			uint32_t nextClus = MergeCluster(dir->fstClusHI, dir->fstClusLO);
			dir = ReadDir(nextClus, path[i]);
		}

		if (NULL == dir)
		{
			debug.Output(Debug::_Lv2, "%s file not found", name);
			return NULL;
		}
	}

	return dir;
}


/// @brief FAT mount
/// @return 
int FAT::Mount(const char* path, const char* mount, int opt, int fstSecNum)
{
	startSector = fstSecNum;

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
	FATSDir* dir = SearchDir(name);
	if (NULL != dir)
	{
		return files.Add(dir);
	}
	return -1;
}


/// @brief FAT write
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int FAT::Write(int fd, char* data, int size, int offset)
{
	return 0;
}


/// @brief FAT read
/// @param data 
/// @param size 
/// @param offset 
/// @return 
int FAT::Read(int fd, char* data, int size, int offset)
{
	FATSDir* dir = files.GetItem(fd);
	return ReadFile(data, size, dir);
}


/// @brief FAT seek
/// @param offset 
/// @return 
int FAT::Seek(int fd, int offset)
{
	return 0;
}


/// @brief FAT rename
/// @param old 
/// @param now 
/// @return 
int FAT::Rename(int fd, const char* old, const char* now)
{
	return 0;
}


/// @brief FAT copy
/// @param from 
/// @param to 
/// @return 
int FAT::Copy(int fd, const char* from, const char* to)
{
	return 0;
}


/// @brief FAT remove
/// @return 
int FAT::Remove(int fd)
{
	return 0;
}


/// @brief FAT size
/// @return 
int FAT::Size(int fd)
{
	FATSDir* dir = files.GetItem(fd);
	return FileSize(dir);
}


/// @brief FAT close
/// @return 
int FAT::Close(int fd)
{
	return 0;
}


///Register file system
REGISTER_FS(new FAT(), fat);
