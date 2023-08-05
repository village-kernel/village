//###########################################################################
// FATName.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatDir.h"


/// @brief 
/// @param name 
/// @return 
uint8_t FatDir::ChkSum(char* name)
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
char* FatDir::GetShortName(FATSDir* sdir)
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
char* FatDir::GetLongName(FATLDir* ldir, FATSDir* sdir)
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
