//###########################################################################
// FatName.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatName.h"
#include "string.h"


/// @brief ChkSum
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
char* FatName::GetShortName(FATEnt* entry)
{
	uint8_t pos = 0;
	char*   name = entry->sdir.name;
	char*   dirName = new char[short_name_size + 2]();
	bool    isBodyLowedCase = (entry->sdir.NTRes & _NS_BODY) == _NS_BODY;
	bool    isExtLowedCase  = (entry->sdir.NTRes & _NS_EXT ) == _NS_EXT;
	
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


/// @brief Set short name
/// @param sdir 
/// @param name 
int FatName::SetShortName(FATEnt* entry, const char* name)
{
	uint8_t pos = 0;
	char*   dirName = entry->sdir.name;
	bool    isBodyLowedCase = true;
	bool    isExtLowedCase  = true;

	//8.3 dot pos
	uint8_t namelen = strlen(name);
	uint8_t dotpos = namelen;
	while ('.' != name[--dotpos] && dotpos);
	uint8_t bodylen = dotpos ? dotpos : namelen;
	
	//8.3 name body
	for (uint8_t i = 0; i < 8; i++)
	{
		char ch = ' ';
		if (pos < bodylen) do { ch = name[pos++]; } while ('.' == ch);

		if (ch >= 'a' && ch <= 'z')
			dirName[i] = ch - 0x20;
		else
			dirName[i] = ch;

		if (isBodyLowedCase && (ch >= 'A' && ch <= 'Z'))
			isBodyLowedCase = false;
	}

	//8.3 name dot
	pos = bodylen;

	//8.3 name ext
	for (uint8_t i = 8; i < 11; i++)
	{
		char ch = ' ';
		if (pos < namelen) do { ch = name[pos++]; } while ('.' == ch);

		if (ch >= 'a' && ch <= 'z')
			dirName[i] = ch - 0x20;
		else
			dirName[i] = ch;

		if (isExtLowedCase && (ch >= 'A' && ch <= 'Z'))
			isExtLowedCase = false;
	}

	//Set NTRes
	if (isBodyLowedCase) entry->sdir.NTRes |= _NS_BODY;
	if (isExtLowedCase)  entry->sdir.NTRes |= _NS_EXT;

	return _OK;
}


/// @brief Generate number name
/// @param name 
/// @param num 
/// @return 
void FatName::GenNumName(FATEnt* entry, int num)
{
	char numstr[8];
	
	uint8_t i = 7;
	do
	{
		char ch = (num % 10) + '0';
		numstr[i--] = ch;
		num /= 10;
	}
	while(num);
	numstr[i] = '~';

	uint8_t pos = 8;
	while (' ' == entry->sdir.name[--pos] && pos);
	if (pos) pos = pos - (7 - i);

	uint8_t size = 8 - i;
	for (uint8_t j = 0; j < size; j++)
	{
		entry->sdir.name[j + pos] = numstr[i++];
	}
}


/// @brief Get long name
/// @param dirName 
/// @param dir 
/// @return 
char* FatName::GetLongName(FATEnt* entires)
{
	uint8_t pos = 0;
	uint8_t n = entires[0].ldir.ord - dir_seq_flag;
	uint8_t chksum = ChkSum(entires[n].sdir.name);
	char* dirName = new char[long_name_size * n + 1]();
	
	//Loop for sequence of long directory entries
	while (n--)
	{
		FATLDir* ldir = &entires[n].ldir;

		//Chksum
		if (entires[n].ldir.chksum != chksum)
		{
			delete[] dirName;
			return NULL;
		}

		//Part 1 of long name 
		for (uint8_t i = 0; i < 5; i++)
		{
			if (0xffff != ldir->name1[i])
			{
				dirName[pos++] = (char)ldir->name1[i];
			}
			else break;
		}

		//Part 2 of long name 
		for (uint8_t i = 0; i < 6; i++)
		{
			if (0xffff != ldir->name2[i])
			{
				dirName[pos++] = (char)ldir->name2[i];
			}
			else return dirName;
		}

		//Part 3 of long name
		for (uint8_t i = 0; i < 2; i++)
		{
			if (0xffff != ldir->name3[i])
			{
				dirName[pos++] = (char)ldir->name3[i];
			}
			else return dirName;
		}
	}

	return dirName;
}


/// @brief Set long name
/// @param ldir 
/// @param sdir 
/// @param name 
int FatName::SetLongName(FATEnt* entires, const char* name)
{
	uint8_t pos = 0;
	uint8_t size = entires[0].ldir.ord - dir_seq_flag;
	uint8_t n = size;
	uint8_t chksum = ChkSum(entires[n].sdir.name);

	//Loop for sequence of long directory entries
	while (n--)
	{
		FATLDir* ldir = &entires[n].ldir;

		if (n) ldir->ord = size - n;
		ldir->attr = _ATTR_LONG_NAME;
		ldir->chksum = chksum;
		ldir->Fill();

		//Part 1 of long name 
		for (uint8_t i = 0; i < 5; i++)
		{
			if ('\0' != name[pos])
			{
				ldir->name1[i] = name[pos++];
			}
			else
			{
				ldir->name1[i] = 0;
				return _OK;
			}
		}

		//Part 2 of long name 
		for (uint8_t i = 0; i < 6; i++)
		{
			if ('\0' != name[pos])
			{
				ldir->name2[i] = name[pos++];
			}
			else
			{
				ldir->name2[i] = 0;
				return _OK;
			}
		}

		//Part 3 of long name 
		for (uint8_t i = 0; i < 2; i++)
		{
			if ('\0' != name[pos])
			{
				ldir->name3[i] = name[pos++];
			}
			else
			{
				ldir->name3[i] = 0;
				return _OK;
			}
		}
	}

	return _OK;
}


/// @brief Get volume label name
/// @param sdir 
/// @return 
char* FatName::GetVolumeLabel(FATEnt* entry)
{
	uint8_t pos   = 0;
	char*   label = new char[volume_label_size + 1]();

	//Copy label name
	for (uint8_t i = 0; i < volume_label_size; i++)
	{
		label[pos++] = entry->sdir.name[i];
	}
	
	//String EOC
	label[pos] = '\0';

	//Remove space
	while (pos--)
	{
		if (label[pos] == ' ')
		{
			label[pos] = '\0';
		}
		else break;
	}

	return label;
}


/// @brief Set volume label
/// @param sdir 
/// @param name 
int FatName::SetVolumeLabel(FATEnt* entry, const char* name)
{
	uint8_t namelen = strlen(name);

	//Check label length
	if (namelen > volume_label_size) return _ERR;

	//Copy label name
	for (uint8_t i = 0; i < volume_label_size; i++)
	{
		if (i < namelen)
		{
			if (name[i] >= 'a' && name[i] <= 'z')
				entry->sdir.name[i] = name[i] - 0x20;
			else
				entry->sdir.name[i] = name[i];
		}
		else entry->sdir.name[i] = ' ';
	}

	return _OK;
}
