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

	for (int16_t namelen = 11; namelen != 0; namelen--)
	{
		sum = ((sum & 1) ? 0x80 : 0) + (sum >> 1) + *name++;
	}

	return sum;
}


/// @brief Get short name
/// @param unient 
/// @return 
char* FatName::GetShortName(UnionEntry* unient)
{
	uint8_t pos = 0;
	char*   name = unient->sfe.name;
	char*   sfn = new char[short_name_size + 2]();
	bool    isBodyLowedCase = (unient->sfe.NTRes & _NS_BODY) == _NS_BODY;
	bool    isExtLowedCase  = (unient->sfe.NTRes & _NS_EXT ) == _NS_EXT;
	
	//8.3 name body
	for (uint8_t i = 0; i < 8; i++)
	{
		if (' ' !=  name[i])
		{
			if (isBodyLowedCase && (name[i] >= 'A' && name[i] <= 'Z'))
				sfn[pos++] = name[i] + 0x20;
			else
				sfn[pos++] = name[i];
		} 
		else break;
	}

	//8.3 name dot
	if (' ' != name[8]) sfn[pos++] = '.';

	//8.3 name ext
	for (uint8_t i = 8; i < 11; i++)
	{
		if (' ' != name[i])
		{
			if (isExtLowedCase && (name[i] >= 'A' && name[i] <= 'Z'))
				sfn[pos++] = name[i] + 0x20;
			else
				sfn[pos++] = name[i]; 
		}
		else break;
	}

	//String EOC
	sfn[pos] = '\0';

	return sfn;
}


/// @brief Set short name
/// @param sdir 
/// @param name 
int FatName::SetShortName(UnionEntry* unient, const char* sfn)
{
	uint8_t pos = 0;
	char*   name = unient->sfe.name;
	bool    isBodyLowedCase = true;
	bool    isExtLowedCase  = true;

	//8.3 dot pos
	uint8_t namelen = strlen(sfn);
	uint8_t dotpos = namelen;
	while ('.' != sfn[--dotpos] && dotpos);
	uint8_t bodylen = dotpos ? dotpos : namelen;
	
	//8.3 name body
	for (uint8_t i = 0; i < 8; i++)
	{
		char ch = ' ';
		if (pos < bodylen) do { ch = sfn[pos++]; } while ('.' == ch);

		if (ch >= 'a' && ch <= 'z')
			name[i] = ch - 0x20;
		else
			name[i] = ch;

		if (isBodyLowedCase && (ch >= 'A' && ch <= 'Z'))
			isBodyLowedCase = false;
	}

	//8.3 name dot
	pos = bodylen;

	//8.3 name ext
	for (uint8_t i = 8; i < 11; i++)
	{
		char ch = ' ';
		if (pos < namelen) do { ch = sfn[pos++]; } while ('.' == ch);

		if (ch >= 'a' && ch <= 'z')
			name[i] = ch - 0x20;
		else
			name[i] = ch;

		if (isExtLowedCase && (ch >= 'A' && ch <= 'Z'))
			isExtLowedCase = false;
	}

	//Set NTRes
	if (isBodyLowedCase) unient->sfe.NTRes |= _NS_BODY;
	if (isExtLowedCase)  unient->sfe.NTRes |= _NS_EXT;

	return _OK;
}


/// @brief Generate number name
/// @param name 
/// @param num 
/// @return 
void FatName::GenNumName(UnionEntry* unient, int num)
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
	while (' ' == unient->sfe.name[--pos] && pos);
	if (pos) pos = pos - (7 - i);

	uint8_t size = 8 - i;
	for (uint8_t j = 0; j < size; j++)
	{
		unient->sfe.name[j + pos] = numstr[i++];
	}
}


/// @brief Get long name
/// @param unients 
/// @return 
char* FatName::GetLongName(UnionEntry* unients)
{
	uint8_t pos = 0;
	uint8_t n = unients[0].lfe.ord - dir_seq_flag;
	uint8_t chksum = ChkSum(unients[n].sfe.name);
	char*   lfn = new char[long_name_size * n + 1]();
	
	//Loop for sequence of long directory entries
	while (n--)
	{
		LongEntry* lfe = &unients[n].lfe;

		//Chksum
		if (unients[n].lfe.chksum != chksum)
		{
			delete[] lfn;
			return NULL;
		}

		//Part 1 of long name 
		for (uint8_t i = 0; i < 5; i++)
		{
			if (0xffff != lfe->name1[i])
			{
				lfn[pos++] = (char)lfe->name1[i];
			}
			else break;
		}

		//Part 2 of long name 
		for (uint8_t i = 0; i < 6; i++)
		{
			if (0xffff != lfe->name2[i])
			{
				lfn[pos++] = (char)lfe->name2[i];
			}
			else return lfn;
		}

		//Part 3 of long name
		for (uint8_t i = 0; i < 2; i++)
		{
			if (0xffff != lfe->name3[i])
			{
				lfn[pos++] = (char)lfe->name3[i];
			}
			else return lfn;
		}
	}

	return lfn;
}


/// @brief Set long name
/// @param lfn 
/// @param sdir 
/// @param name 
int FatName::SetLongName(UnionEntry* unients, const char* lfn)
{
	uint8_t pos = 0;
	uint8_t size = unients[0].lfe.ord - dir_seq_flag;
	uint8_t n = size;
	uint8_t chksum = ChkSum(unients[n].sfe.name);

	//Loop for sequence of long directory entries
	while (n--)
	{
		LongEntry* lfe = &unients[n].lfe;

		if (n) lfe->ord = size - n;
		lfe->attr = _ATTR_LONG_NAME;
		lfe->chksum = chksum;
		lfe->Fill();

		//Part 1 of long name 
		for (uint8_t i = 0; i < 5; i++)
		{
			if ('\0' != lfn[pos])
			{
				lfe->name1[i] = lfn[pos++];
			}
			else
			{
				lfe->name1[i] = 0;
				return _OK;
			}
		}

		//Part 2 of long name 
		for (uint8_t i = 0; i < 6; i++)
		{
			if ('\0' != lfn[pos])
			{
				lfe->name2[i] = lfn[pos++];
			}
			else
			{
				lfe->name2[i] = 0;
				return _OK;
			}
		}

		//Part 3 of long name 
		for (uint8_t i = 0; i < 2; i++)
		{
			if ('\0' != lfn[pos])
			{
				lfe->name3[i] = lfn[pos++];
			}
			else
			{
				lfe->name3[i] = 0;
				return _OK;
			}
		}
	}

	return _OK;
}


/// @brief Get volume label name
/// @param sdir 
/// @return 
char* FatName::GetVolumeLabel(UnionEntry* unient)
{
	uint8_t pos   = 0;
	char*   label = new char[volume_label_size + 1]();

	//Copy label name
	for (uint8_t i = 0; i < volume_label_size; i++)
	{
		label[pos++] = unient->sfe.name[i];
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
int FatName::SetVolumeLabel(UnionEntry* unient, const char* lbn)
{
	uint8_t namelen = strlen(lbn);

	//Check label length
	if (namelen > volume_label_size) return _ERR;

	//Copy label name
	for (uint8_t i = 0; i < volume_label_size; i++)
	{
		if (i < namelen)
		{
			if (lbn[i] >= 'a' && lbn[i] <= 'z')
				unient->sfe.name[i] = lbn[i] - 0x20;
			else
				unient->sfe.name[i] = lbn[i];
		}
		else unient->sfe.name[i] = ' ';
	}

	return _OK;
}
