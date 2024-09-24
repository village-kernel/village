//###########################################################################
// FatObject.h
// Declarations of the functions that manage fat file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FAT_OBJECT_H__
#define __FAT_OBJECT_H__

#include "stdint.h"
#include "string.h"
#include "FileDefs.h"


/// @brief FatDefs
class FatDefs
{
public:
	/// @brief EntryAttr
	enum EntryAttr
	{
		_AttrFile           = 0x00,
		_AttrReadOnly       = 0x01,
		_AttrHidden         = 0x02,
		_AttrSystem         = 0x04,
		_AttrVolumeID       = 0x08,
		_AttrDirectory      = 0x10,
		_AttrArchive        = 0x20,
		_AttrLongName       = _AttrReadOnly | _AttrHidden | _AttrSystem | _AttrVolumeID,
		_AttrLongNameMask   = _AttrReadOnly | _AttrHidden | _AttrSystem | _AttrVolumeID | _AttrDirectory | _AttrArchive,
	};


	/// @brief NSFlag
	enum NSFlag
	{
		_NsNoe          = 0x00,
		_NsLoss         = 0x01,   /* Out of 8.3 format */
		_NsLfn          = 0x02,   /* Force to create LFN entry */
		_NsLast         = 0x04,   /* Last segment */
		_NsBody         = 0x08,   /* Lower case flag (body) */
		_NsExt          = 0x10,   /* Lower case flag (ext) */
		_NsDot          = 0x20,   /* Dot entry */
		_NsNolfn        = 0x40,   /* Do not find LFN */
		_NsNoname       = 0x80,   /* Not followed */
	};
};


/// @brief FatEntryLoc
struct FatEntryLoc
{
	//Members
	uint32_t index;
	uint32_t clust;
	uint32_t sector;

	//Methods
	FatEntryLoc();
};


/// @brief FatLongEntry
struct FatLongEntry
{
	//Members
	uint8_t  ord;
	uint16_t name1[5];
	uint8_t  attr;
	uint8_t  type;
	uint8_t  chksum;
	uint16_t name2[6];
	uint16_t fstClustLO;
	uint16_t name3[2];

	//Methods
	FatLongEntry();
	void Fill();
} __attribute__((packed));


/// @brief FatShortEntry
struct FatShortEntry
{
	//Members
	char     name[11];
	uint8_t  attr;
	uint8_t  NTRes;
	uint8_t  crtTimeTenth;
	uint16_t crtTime;
	uint16_t crtDate;
	uint16_t lstAccDate;
	uint16_t fstClustHI;
	uint16_t wrtTime;
	uint16_t wrtDate;
	uint16_t fstClustLO;
	uint32_t fileSize;

	//Methods
	FatShortEntry();
} __attribute__((packed));


/// @brief FatEntry
union FatEntry
{
	//static constants
	static const uint8_t dir_seq_flag = 0x40;
	static const uint8_t dir_free_flag = 0xe5;
	static const uint8_t dir_valid_flag = 0x20;

	//Members
	FatLongEntry  lfe;
	FatShortEntry sfe;
	
	//Methods
	FatEntry();
	bool    IsValid();
	void    SetStoreSize(uint8_t size);
	uint8_t GetStoreSize();
} __attribute__((packed));


/// @brief FatFolder
class FatFolder;


/// @brief FatObject
class FatObject
{
private:
	//Static constants
	static const uint8_t long_name_size  = 13;
	static const uint8_t short_name_size = 11;
	static const uint8_t dir_seq_flag = 0x40;
	static const uint8_t dir_free_flag = 0xe5;

	//Members
	int             mode;
	FatEntryLoc     entloc;
	FatFolder*      folder;

	//Members
	FatLongEntry*   lfe;
	FatShortEntry*  sfe;
	FatEntry*       ufe;

	//Methods
	uint8_t ChkSum(const char* name);
public:
	//Methods
	FatObject();
	FatObject(const char* name);
	FatObject(FatObject* fatObj);
	FatObject(FatEntry* ufe);
	~FatObject();

	void Setup(const char* name);
	void Setup(FatObject* fatObj);
	void Setup(FatEntry* ufe);

	void SetupDot(FatObject* fatObj);
	void SetupDotDot(FatObject* fatObj);

	void SetOjectFree();

	char* GetObjectName();
	FileType GetObjectType();
	FileAttr GetObjectAttr();

	FatEntry* GetEntries();
	void SetStoreSize(uint8_t size);
	uint8_t GetStoreSize();

	bool IsLongName();
	void GenNumName(int num);
	void SetRawName(const char* label);
	char* GetRawName();
	void SetShortName(const char* name);
	char* GetShortName();
	void SetLongName(const char* name);
	char* GetLongName();
	void SetAttribute(uint8_t attr);
	uint8_t GetAttribute();
	void SetNTRes(uint8_t NTRes);
	uint8_t GetNTRes();
	void SetCreateTenth(uint16_t tenth);
	uint16_t GetCreateTenth();
	void SetCreateTime(uint16_t time);
	uint16_t GetCreateTime();
	void SetCreateDate(uint16_t date);
	uint16_t GetCreateDate();
	void SetLastAccDate(uint16_t date);
	uint16_t GetLastAccDate();
	void SetWriteTime(uint16_t time);
	uint16_t GetWriteTime();
	void SetWriteDate(uint16_t date);
	uint16_t GetWriteDate();
	void SetFirstCluster(uint32_t clust);
	uint32_t GetFirstCluster();
	void SetFileSize(uint32_t size);
	uint32_t GetFileSize();
	void SetFatEntryLoc(FatEntryLoc loc);
	FatEntryLoc GetFatEntryLoc();
};

#endif //!__FAT_OBJECT_H__
