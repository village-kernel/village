//###########################################################################
// FatObject.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatObject.h"


/// @brief Constructor
FatObject::FatObject(LongEntry* lfe, ShortEntry* sfe)
{
	this->lfe = lfe;
	this->sfe = sfe;
}


/// @brief Destructor
FatObject::~FatObject()
{
}


/// @brief ChkSum
/// @param name 
/// @return 
uint8_t FatObject::ChkSum(char* name)
{
	uint8_t sum = 0;

	for (int16_t namelen = 11; namelen != 0; namelen--)
	{
		sum = ((sum & 1) ? 0x80 : 0) + (sum >> 1) + *name++;
	}

	return sum;
}


/// @brief FatObject set short name
/// @param name 
void FatObject::SetShortName(char* name)
{
	uint8_t pos = 0;
	char*   sfn = sfe->name;
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
			sfn[i] = ch - 0x20;
		else
			sfn[i] = ch;

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
			sfn[i] = ch - 0x20;
		else
			sfn[i] = ch;

		if (isExtLowedCase && (ch >= 'A' && ch <= 'Z'))
			isExtLowedCase = false;
	}

	//Set NTRes
	if (isBodyLowedCase) sfe->NTRes |= _NS_BODY;
	if (isExtLowedCase)  sfe->NTRes |= _NS_EXT;
}


/// @brief FatObject get short name
/// @return 
char* FatObject::GetShortName()
{
	uint8_t pos = 0;
	char*   name = sfe->name;
	char*   sfn = new char[short_name_size + 2]();
	bool    isBodyLowedCase = (sfe->NTRes & _NS_BODY) == _NS_BODY;
	bool    isExtLowedCase  = (sfe->NTRes & _NS_EXT ) == _NS_EXT;
	
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


/// @brief FatObject set long name
/// @param name 
void FatObject::SetLongName(char* name)
{
	uint8_t pos = 0;
	uint8_t size = lfe[0].ord - dir_seq_flag;
	uint8_t n = size;
	uint8_t chksum = ChkSum(sfe->name);

	//Loop for sequence of long directory entries
	while (n--)
	{
		LongEntry* lfe = &lfe[n];

		if (n) lfe->ord = size - n;
		lfe->attr = _ATTR_LONG_NAME;
		lfe->chksum = chksum;
		lfe->Fill();

		//Part 1 of long name 
		for (uint8_t i = 0; i < 5; i++)
		{
			if ('\0' != name[pos])
			{
				lfe->name1[i] = name[pos++];
			}
			else
			{
				lfe->name1[i] = 0;
				return;
			}
		}

		//Part 2 of long name 
		for (uint8_t i = 0; i < 6; i++)
		{
			if ('\0' != name[pos])
			{
				lfe->name2[i] = name[pos++];
			}
			else
			{
				lfe->name2[i] = 0;
				return;
			}
		}

		//Part 3 of long name 
		for (uint8_t i = 0; i < 2; i++)
		{
			if ('\0' != name[pos])
			{
				lfe->name3[i] = name[pos++];
			}
			else
			{
				lfe->name3[i] = 0;
				return;
			}
		}
	}
}


/// @brief FatObject get long name
/// @return 
char* FatObject::GetLongName()
{
	uint8_t pos = 0;
	uint8_t n = lfe[0].ord - dir_seq_flag;
	uint8_t chksum = ChkSum(sfe->name);
	char*   lfn = new char[long_name_size * n + 1]();
	
	//Loop for sequence of long directory entries
	while (n--)
	{
		LongEntry* lfe = &lfe[n];

		//Chksum
		if (lfe[n].chksum != chksum)
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


/// @brief FatObject set attribute
/// @param attr 
void FatObject::SetAttribute(uint8_t attr)
{
	sfe->attr = attr;
}


/// @brief FatObject get attribute
/// @return 
uint8_t FatObject::GetAttribute()
{
	return sfe->attr;
}


/// @brief FatObject set nt res
/// @param NTRes 
void FatObject::SetNTRes(uint8_t NTRes)
{
	sfe->NTRes = NTRes;
}


/// @brief FatObject get nt res
/// @return 
uint8_t FatObject::GetNTRes()
{
	return sfe->NTRes;
}


/// @brief FatObject set create tenth
/// @param tenth 
void FatObject::SetCreateTenth(uint16_t tenth)
{
	sfe->crtTimeTenth = tenth;
}


/// @brief FatObject get create tenth
/// @return 
uint16_t FatObject::GetCreateTenth()
{
	return sfe->crtTimeTenth;
}


/// @brief FatObject set create time
/// @param time 
void FatObject::SetCreateTime(uint16_t time)
{
	sfe->crtTime = time;
}


/// @brief FatObject get create time
/// @return 
uint16_t FatObject::GetCreateTime()
{
	return  sfe->crtTime;
}


/// @brief FatObject set create date
/// @param date 
void FatObject::SetCreateDate(uint16_t date)
{
	sfe->crtDate = date;
}


/// @brief FatObject get create date
/// @return 
uint16_t FatObject::GetCreateDate()
{
	return sfe->crtDate;
}


/// @brief FatObject set last access date
/// @param date 
void FatObject::SetLastAccDate(uint16_t date)
{
	sfe->lstAccDate = date;
}


/// @brief FatObject get last access date
/// @return 
uint16_t FatObject::GetLastAccDate()
{
	return sfe->lstAccDate;
}


/// @brief FatObject set write time
/// @param time 
void FatObject::SetWriteTime(uint16_t time)
{
	sfe->wrtTime = time;
}


/// @brief FatObject get write time
/// @return 
uint16_t FatObject::GetWriteTime()
{
	return sfe->wrtTime;
}


/// @brief FatObject set write date
/// @param date 
void FatObject::SetWriteDate(uint16_t date)
{
	sfe->wrtDate = date;
}


/// @brief FatObject get write date
/// @return 
uint16_t FatObject::GetWriteDate()
{
	return sfe->wrtDate;
}


/// @brief FatObject set first cluster
/// @param clust 
void FatObject::SetFirstCluster(uint32_t clust)
{
	sfe->fstClustHI = (clust >> 16) & 0xffff;
	sfe->fstClustLO = (clust >> 0)  & 0xffff;
}


/// @brief FatObject get first cluster
/// @return 
uint32_t FatObject::GetFirstCluster()
{
	return (uint32_t)(sfe->fstClustHI << 16) | sfe->fstClustLO;
}


/// @brief FatObject set file size
/// @param Size 
void FatObject::SetFileSize(uint32_t size)
{
	sfe->fileSize = size;
}


/// @brief FatObject get file size
/// @return 
uint32_t FatObject::GetFileSize()
{
	return sfe->fileSize;
}
