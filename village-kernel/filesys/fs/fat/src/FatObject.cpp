//###########################################################################
// FatObject.cpp
// Definitions of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "FatObject.h"


/// @brief LongEntry constructor
FatLongEntry::FatLongEntry()
{
}


/// @brief LongEntry fill
void FatLongEntry::Fill()
{
	memset((void*)name1, 0xff, 10);
	memset((void*)name2, 0xff, 12);
	memset((void*)name3, 0xff, 4);
}


/// @brief ShortEntry constructor
FatShortEntry::FatShortEntry()
{
	memset((void*)this, 0, 32);
}


/// @brief UnionEntry constructor
FatUnionEntry::FatUnionEntry()
{
	memset((void*)this, 0, 32);
}


/// @brief UnionEntry is valid
/// @return 
bool FatUnionEntry::IsValid()
{
	if (lfe.ord != dir_free_flag && lfe.ord >= dir_valid_flag)
	{
		if ((sfe.attr & (_FAT_ATTR_DIRECTORY | _FAT_ATTR_VOLUME_ID)) == _FAT_ATTR_FILE)
			return true;
		else if ((sfe.attr & (_FAT_ATTR_DIRECTORY | _FAT_ATTR_VOLUME_ID)) == _FAT_ATTR_DIRECTORY)
			return true;
		else if ((sfe.attr & (_FAT_ATTR_DIRECTORY | _FAT_ATTR_VOLUME_ID)) == _FAT_ATTR_VOLUME_ID)
			return true;
		else if ((sfe.attr & _FAT_ATTR_LONG_NAME_MASK) == _FAT_ATTR_LONG_NAME)
			return true;
	}
	return false;
}


/// @brief UnionEntry get store size
/// @return 
uint8_t FatUnionEntry::GetStoreSize()
{
	if ((lfe.attr & _FAT_ATTR_LONG_NAME_MASK) == _FAT_ATTR_LONG_NAME)
		return (lfe.ord - dir_seq_flag + 1);
	else
		return 1;
}


/// @brief UnionEntry set store size
/// @param size 
void FatUnionEntry::SetStoreSize(uint8_t size)
{
	if (size > 1) lfe.ord = dir_seq_flag + size - 1;
}


/// @brief FatObject Constructor
FatObject::FatObject()
	:index(0),
	clust(0),
	sector(0),
	lfe(NULL),
	sfe(NULL),
	ufe(NULL)
{
}


/// @brief FatObject Constructor
FatObject::FatObject(FatUnionEntry* ufe)
	:index(0),
	clust(0),
	sector(0),
	lfe(NULL),
	sfe(NULL),
	ufe(ufe)
{
	if (NULL != ufe) Setup(ufe);
}


/// @brief FatObject Constructor
/// @param obj 
FatObject::FatObject(FatObject* obj)
	:index(0),
	clust(0),
	sector(0),
	lfe(NULL),
	sfe(NULL),
	ufe(NULL)
{
	if (NULL != obj) Clone(obj);
}


/// @brief Destructor
FatObject::~FatObject()
{
	delete[] this->ufe;
}


/// @brief FatObject clone
/// @param obj 
void FatObject::Clone(FatObject* obj)
{
	uint8_t        size = obj->GetStoreSize();
	FatUnionEntry* raw  = obj->GetUnionEntry();

	ufe = new FatUnionEntry[size];

	for (uint8_t i = 0; i < size; i++)
	{
		ufe[i] = raw[i];
	}

	Setup(ufe);

	obj->GetEntryLocInfo(index, clust, sector);
}


/// @brief FatObject setup
/// @param ufe 
void FatObject::Setup(FatUnionEntry* ufe)
{
	this->lfe = (FatLongEntry*)ufe;
	this->sfe = (FatShortEntry*)ufe;
	this->ufe = (FatUnionEntry*)ufe;

	if (ufe->IsValid() && IsLongName())
	{
		uint8_t n = lfe->ord - dir_seq_flag;
		lfe = (FatLongEntry*)ufe;
		sfe = (FatShortEntry*)ufe + n;
	}
}


/// @brief Setup by name
/// @param name 
void FatObject::SetupByName(const char* name)
{
	//Cal the size of entries
	uint8_t namelen = strlen(name);
	uint8_t dotpos = namelen;
	while ('.' != name[--dotpos] && dotpos);
	uint8_t extlen  = dotpos ? (namelen - dotpos - 1) : 0;
	uint8_t bodylen = dotpos ? dotpos : namelen;
	bool isNameLoss = (bodylen > 8 || extlen > 3);
	uint8_t mod = (namelen % (long_name_size - 1)) ? 1 : 0;

	//Alloc entires space
	uint8_t size = isNameLoss ? ((namelen / (long_name_size - 1)) + mod + 1) : 1;
	FatUnionEntry* ufe = new FatUnionEntry[size]();

	//Setup short name
	Setup(ufe);
	SetShortName(name);
	SetStoreSize(size);

	//Set long name
	if (isNameLoss)
	{
		sfe->NTRes |= _FAT_NS_LOSS;
		SetLongName(name);
	}
}


/// @brief Setup dot entry
/// @param obj 
void FatObject::SetupDot(FatObject* obj)
{
	Setup(new FatUnionEntry());
	SetRawName(".");
	SetFirstCluster(obj->GetFirstCluster());
	SetAttribute(_FAT_ATTR_DIRECTORY | _FAT_ATTR_HIDDEN);
}


/// @brief Setup dot dot entry
/// @param obj 
void FatObject::SetupDotDot(FatObject* obj)
{
	Setup(new FatUnionEntry());
	SetRawName("..");
	SetFirstCluster(obj->GetFirstCluster());
	SetAttribute(_FAT_ATTR_DIRECTORY | _FAT_ATTR_HIDDEN);
}


/// @brief FatObject set entry free flag
void FatObject::SetEntryFree()
{
	sfe->name[0] = dir_free_flag;

	if (true == IsLongName())
	{
		uint8_t n = lfe->ord - dir_seq_flag;

		for (uint8_t i = 0; i < n; i++)
		{
			lfe[i].ord = dir_free_flag;
		}
	}
}


/// @brief FatObject is long name
/// @return 
bool FatObject::IsLongName()
{
	return ((lfe->attr & _FAT_ATTR_LONG_NAME_MASK) == _FAT_ATTR_LONG_NAME);
}


/// @brief Get object name
/// @return 
char* FatObject::GetObjectName()
{
	return IsLongName() ? GetLongName() : GetShortName();
}


/// @brief Get object type
/// @return type
FileType FatObject::GetObjectType()
{
	if ((sfe->attr & (_FAT_ATTR_DIRECTORY | _FAT_ATTR_VOLUME_ID)) == _FAT_ATTR_FILE)
		return FileType::_File;
	else if ((sfe->attr & (_FAT_ATTR_DIRECTORY | _FAT_ATTR_VOLUME_ID)) == _FAT_ATTR_DIRECTORY)
		return FileType::_Diretory;
	else if ((sfe->attr & (_FAT_ATTR_DIRECTORY | _FAT_ATTR_VOLUME_ID)) == _FAT_ATTR_VOLUME_ID)
		return FileType::_Volume;
	else
		return FileType::_Unknown;
}


/// @brief Get object attr
/// @return attr
FileAttr FatObject::GetObjectAttr()
{
	if ((sfe->attr & _FAT_ATTR_HIDDEN) == _FAT_ATTR_HIDDEN)
		return FileAttr::_Hidden;
	else
		return FileAttr::_Visible;
}


/// @brief Set union entry
/// @param ufe 
void FatObject::SetUnionEntry(FatUnionEntry* ufe)
{
	Setup(ufe);
}


/// @brief Get union entry
/// @return 
FatUnionEntry* FatObject::GetUnionEntry()
{
	return ufe;
}


/// @brief Set store size
/// @param size 
void FatObject::SetStoreSize(uint8_t size)
{
	ufe->SetStoreSize(size);
}


/// @brief Get store size
/// @return 
uint8_t FatObject::GetStoreSize()
{
	return ufe->GetStoreSize();
}


/// @brief Set entry location info
/// @param index 
/// @param clust 
/// @param sector 
void FatObject::SetEntryLocInfo(uint32_t index, uint32_t clust, uint32_t sector)
{
	this->index  = index;
	this->clust  = clust;
	this->sector = sector;
}


/// @brief Get entry location info
/// @param index 
/// @param clust 
/// @param sector 
void FatObject::GetEntryLocInfo(uint32_t& index, uint32_t& clust, uint32_t& sector)
{
	index  = this->index;
	clust  = this->clust;
	sector = this->sector;
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


/// @brief FatObject set raw name
/// @param name 
void FatObject::SetRawName(const char* name)
{
	uint8_t namelen = strlen(name);

	//Check label length
	if (namelen > short_name_size) return;

	//Copy label name
	for (uint8_t i = 0; i < short_name_size; i++)
	{
		if (i < namelen)
		{
			if (name[i] >= 'a' && name[i] <= 'z')
				sfe->name[i] = name[i] - 0x20;
			else
				sfe->name[i] = name[i];
		}
		else sfe->name[i] = ' ';
	}
}


/// @brief FatObject get raw name
/// @return 
char* FatObject::GetRawName()
{
	uint8_t pos   = 0;
	char*   name = new char[short_name_size + 1]();

	//Copy label name
	for (uint8_t i = 0; i < short_name_size; i++)
	{
		name[pos++] = sfe->name[i];
	}
	
	//String EOC
	name[pos] = '\0';

	//Remove space
	while (pos--)
	{
		if (name[pos] == ' ')
		{
			name[pos] = '\0';
		}
		else break;
	}

	return name;
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
	if (isBodyLowedCase) sfe->NTRes |= _FAT_NS_BODY;
	if (isExtLowedCase)  sfe->NTRes |= _FAT_NS_EXT;
}


/// @brief FatObject get short name
/// @return 
char* FatObject::GetShortName()
{
	uint8_t pos = 0;
	char*   name = sfe->name;
	char*   sfn = new char[short_name_size + 2]();
	bool    isBodyLowedCase = (sfe->NTRes & _FAT_NS_BODY) == _FAT_NS_BODY;
	bool    isExtLowedCase  = (sfe->NTRes & _FAT_NS_EXT ) == _FAT_NS_EXT;
	
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
		lfe[n].attr = _FAT_ATTR_LONG_NAME;
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
