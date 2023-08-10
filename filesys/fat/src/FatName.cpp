//###########################################################################
// FatName.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatName.h"


/// @brief 
/// @param fat 
/// @param dbr 
/// @param startSector 
void FatName::Initialize(FATData* fat, FATDBR* dbr, uint32_t startSector)
{
	this->dbr = dbr;
	this->fat = fat;
	disk.Initialize(fat, dbr, startSector);
}


/// @brief 
/// @param name 
/// @return 
uint8_t FatName::ChkSum(char* name)
{
	uint8_t sum = 0;

	for (int16_t nameLen = 11; nameLen != 0; nameLen--)
	{
		sum = ((sum & 1) ? 0x80 : 0) + (sum >> 1) + *name++;
	}

	return sum;
}


/// @brief Get short name
/// @param dirName 
/// @param dir 
/// @return 
char* FatName::GetShortName(FATSDir* sdir)
{
	uint8_t pos = 0;
	char*   name = sdir->name;
	char*   dirName = new char[short_name_size]();
	bool    isBodyLowedCase = (sdir->NTRes & _NS_BODY) == _NS_BODY;
	bool    isExtLowedCase  = (sdir->NTRes & _NS_EXT ) == _NS_EXT;
	
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

	return dirName;
}


/// @brief 
/// @param dirName 
/// @param dir 
/// @return 
char* FatName::GetLongName(FATLDir* ldir, FATSDir* sdir)
{
	uint8_t pos = 0;
	uint8_t n = ldir->ord - 0x40;
	char* dirName = new char[long_name_size * n]();
	
	//Loop for sequence of long directory entries
	while (n--)
	{
		//Chksum
		if (ldir[n].chksum != ChkSum(sdir->name))
		{
			delete[] dirName;
			return NULL;
		}

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
			else return dirName;
		}

		//Part 3 of long name
		for (uint8_t i = 0; i < 4; i += 2)
		{
			if (0xff != ldir[n].name3[i])
			{
				dirName[pos++] = ldir[n].name3[i];
			}
			else return dirName;
		}
	}

	return dirName;
}


/// @brief 
/// @param entries 
/// @param idx 
/// @param clust 
/// @param sector 
/// @return 
char* FatName::GetDirName(DirData* data)
{
	DirEntry*& entries = data->entries;
	char*&     name    = data->name;
	uint32_t&  index   = data->index;
	uint32_t&  clust   = data->clust;
	uint32_t&  sector  = data->sector;

	if ((entries[index].ldir.attr & _ATTR_LONG_NAME_MASK) == _ATTR_LONG_NAME)
	{
		uint8_t n = entries[index].ldir.ord - dir_seq_flag;

		FATLDir* ldirs = new FATLDir[n]();

		for (uint8_t i = 0; i < n; i++)
		{
			ldirs[i] = entries[index++].ldir;

			if (index >= fat->entriesPerSec)
			{
				disk.CalcNextSector(clust, sector);
				if (0 != sector)
				{
					disk.ReadOneSector((char*)entries, sector);
					index = 0;
				}
				else
				{
					delete[] ldirs;
					delete data;
					return name = NULL;
				}
			}
		}

		name = GetLongName(ldirs, &entries[index].sdir);

		delete[] ldirs;
	}
	else
	{
		name = GetShortName(&entries[index].sdir);
	}

	return name;
}
