//###########################################################################
// FatObject.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatObject.h"


/// @brief Constructor
FatObject::FatObject(char* raw)
	:clust(0),
	sector(0),
	index(0),
	size(0),
	lfe(NULL),
	sfe(NULL),
	ufe(NULL)
{
	if (NULL != raw) Setup(raw);
}


/// @brief Destructor
FatObject::~FatObject()
{
	delete[] this->ufe;
}


/// @brief FatObject setup
/// @param raw 
void FatObject::Setup(char* raw)
{
	this->lfe = (LongEntry*)raw;
	this->sfe = (ShortEntry*)raw;
	this->ufe = (UnionEntry*)raw;

	if (ufe->IsValid() && ufe->IsLongName())
	{
		uint8_t n = raw[0] - dir_seq_flag;
		this->lfe = (LongEntry*)raw;
		this->sfe = (ShortEntry*)raw + n;
	}
}


/// @brief FatObject set entry free flag
void FatObject::SetEntryFree()
{
	sfe->name[0] = dir_free_flag;

	if (true == ufe->IsLongName())
	{
		uint8_t n = lfe->ord - dir_seq_flag;

		for (uint8_t i = 0; i < n; i++)
		{
			lfe[i].ord = dir_free_flag;
		}
	}
}


/// @brief ChkSum
/// @param name 
/// @return 
uint8_t FatObject::ChkSum(const char* name)
{
	uint8_t sum = 0;

	for (int16_t namelen = 11; namelen != 0; namelen--)
	{
		sum = ((sum & 1) ? 0x80 : 0) + (sum >> 1) + *name++;
	}

	return sum;
}


/// @brief FatObject generate number name
/// @param num 
void FatObject::GenNumName(int num)
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
	while (' ' == sfe->name[--pos] && pos);
	if (pos) pos = pos - (7 - i);

	uint8_t size = 8 - i;
	for (uint8_t j = 0; j < size; j++)
	{
		sfe->name[j + pos] = numstr[i++];
	}
}


/// @brief FatObject set short name
/// @param name 
void FatObject::SetShortName(const char* name)
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
void FatObject::SetLongName(const char* name)
{
	uint8_t pos = 0;
	uint8_t size = lfe[0].ord - dir_seq_flag;
	uint8_t n = size;
	uint8_t chksum = ChkSum(sfe->name);

	//Loop for sequence of long directory entries
	while (n--)
	{
		if (n) lfe[n].ord = size - n;
		lfe[n].attr = _ATTR_LONG_NAME;
		lfe[n].chksum = chksum;
		lfe[n].Fill();

		//Part 1 of long name 
		for (uint8_t i = 0; i < 5; i++)
		{
			if ('\0' != name[pos])
			{
				lfe[n].name1[i] = name[pos++];
			}
			else
			{
				lfe[n].name1[i] = 0;
				return;
			}
		}

		//Part 2 of long name 
		for (uint8_t i = 0; i < 6; i++)
		{
			if ('\0' != name[pos])
			{
				lfe[n].name2[i] = name[pos++];
			}
			else
			{
				lfe[n].name2[i] = 0;
				return;
			}
		}

		//Part 3 of long name 
		for (uint8_t i = 0; i < 2; i++)
		{
			if ('\0' != name[pos])
			{
				lfe[n].name3[i] = name[pos++];
			}
			else
			{
				lfe[n].name3[i] = 0;
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
		//Chksum
		if (lfe[n].chksum != chksum)
		{
			delete[] lfn;
			return NULL;
		}

		//Part 1 of long name 
		for (uint8_t i = 0; i < 5; i++)
		{
			if (0xffff != lfe[n].name1[i])
			{
				lfn[pos++] = (char)lfe[n].name1[i];
			}
			else break;
		}

		//Part 2 of long name 
		for (uint8_t i = 0; i < 6; i++)
		{
			if (0xffff != lfe[n].name2[i])
			{
				lfn[pos++] = (char)lfe[n].name2[i];
			}
			else return lfn;
		}

		//Part 3 of long name
		for (uint8_t i = 0; i < 2; i++)
		{
			if (0xffff != lfe[n].name3[i])
			{
				lfn[pos++] = (char)lfe[n].name3[i];
			}
			else return lfn;
		}
	}

	return lfn;
}


/// @brief FatObject set volume label
/// @param label 
void FatObject::SetVolumeLabel(const char* label)
{
	uint8_t namelen = strlen(label);

	//Check label length
	if (namelen > volume_label_size) return;

	//Copy label name
	for (uint8_t i = 0; i < volume_label_size; i++)
	{
		if (i < namelen)
		{
			if (label[i] >= 'a' && label[i] <= 'z')
				sfe->name[i] = label[i] - 0x20;
			else
				sfe->name[i] = label[i];
		}
		else sfe->name[i] = ' ';
	}
}


/// @brief FatObject get volume label
/// @return 
char* FatObject::GetVolumeLabel()
{
	uint8_t pos   = 0;
	char*   label = new char[volume_label_size + 1]();

	//Copy label name
	for (uint8_t i = 0; i < volume_label_size; i++)
	{
		label[pos++] = sfe->name[i];
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


/// @brief LongEntry fill
void FatObject::LongEntry::Fill()
{
	memset((void*)name1, 0xff, 10);
	memset((void*)name2, 0xff, 12);
	memset((void*)name3, 0xff, 4);
}


/// @brief ShortEntry constructor
FatObject::ShortEntry::ShortEntry()
{
	memset((void*)this, 0, 32);
}


/// @brief UnionEntry constructor
FatObject::UnionEntry::UnionEntry()
{
	memset((void*)this, 0, 32);
}


/// @brief UnionEntry is directory
/// @return 
bool FatObject::UnionEntry::IsDirectory()
{
	return ((sfe.attr & (_ATTR_DIRECTORY | _ATTR_VOLUME_ID)) == _ATTR_DIRECTORY); 
}


/// @brief UnionEntry is volume
/// @return 
bool FatObject::UnionEntry::IsVolume()
{
	return ((sfe.attr & (_ATTR_DIRECTORY | _ATTR_VOLUME_ID)) == _ATTR_VOLUME_ID);
}


/// @brief UnionEntry is file
/// @return 
bool FatObject::UnionEntry::IsFile()
{
	return ((sfe.attr & (_ATTR_DIRECTORY | _ATTR_VOLUME_ID)) == _ATTR_FILE);
}


/// @brief UnionEntry is hidden
/// @return 
bool FatObject::UnionEntry::IsHidden()
{
	return ((sfe.attr & _ATTR_HIDDEN) == _ATTR_HIDDEN);
}


/// @brief UnionEntry is long name
/// @return 
bool FatObject::UnionEntry::IsLongName()
{
	return ((lfe.attr & _ATTR_LONG_NAME_MASK) == _ATTR_LONG_NAME);
}


/// @brief UnionEntry is valid
/// @return 
bool FatObject::UnionEntry::IsValid()
{
	return ((lfe.ord > dir_seq_flag) && (lfe.ord != dir_free_flag));
}


/// @brief UnionEntry ord size
/// @return 
uint8_t FatObject::UnionEntry::OrdSize()
{
	return (lfe.ord - dir_seq_flag + 1);
}


/// @brief UnionEntry alloc size
/// @return 
uint8_t FatObject::UnionEntry::AllocSize()
{
	if ((lfe.attr & _ATTR_LONG_NAME_MASK) == _ATTR_LONG_NAME)
		return (lfe.ord - dir_seq_flag + 1);
	else
		return 1;
}
