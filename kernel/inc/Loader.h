//###########################################################################
// Loader.h
// Declarations of the functions that manage loader
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __LOADER_H__
#define __LOADER_H__

#include "Module.h"
#include "FileStream.h"


///Loader
class Loader : public Module
{
private:
	//Enumerations
	enum Result
	{
		_OK     = 0,
		_ERR    = 1,
	};

	//Structures
	struct ELFHeader
	{
		uint8_t  ident[16];
		uint16_t type;
		uint16_t machine;
		uint32_t version;
		uint32_t entry;
		uint32_t programHeaderOffset;
		uint32_t sectionHeaderOffset;
		uint32_t flags;
		uint16_t elfHeaderSize;
		uint16_t programHeaderSize;
		uint16_t programHeaderNum;
		uint16_t sectionHeaderSize;
		uint16_t sectionHeaderNum;
		uint16_t sectionHeaderStringTableIndex;
	};

	struct SectionHeader
	{
		uint32_t nameOffset;
		uint32_t type;
		uint32_t flags;
		uint32_t addr;
		uint32_t offset;
		uint32_t size;
		uint32_t link;
		uint32_t info;
		uint32_t addrAlign;
		uint32_t entireSize;
	};

	struct SymbolTableEntry
	{
		uint32_t name;
		uint32_t value;
		uint32_t size;
		uint8_t  info;
		uint8_t  other;
		uint16_t index;
	};

	struct RelocationEntry
	{
		uint32_t offset;
		uint32_t info;
	};

	struct ProgramHeader
	{
		uint32_t type;
		uint32_t offset;
		uint32_t vaddr;
		uint32_t paddr;
		uint32_t fileSize;
		uint32_t memSize;
		uint32_t flags;
		uint32_t align;
	};

	struct DynamicHeader
	{
		int32_t tag;
		union dynUnion
		{
			uint32_t val;
			uint32_t ptr;
		};
	};


	struct ELF32
	{
		ELFHeader       elfHeader;
		SectionHeader*  sectionHeaders;
	};
	
	//Static constants
	static const int32_t elf_header_size = sizeof(ELFHeader);
	static const int32_t sec_header_size = sizeof(SectionHeader);

	//Members
	FileStream file;
	ELF32      elf32;

	//Methods
	void LoadElf32(const char* path);
	int ReadELFHeader();
	int ReadSectionHeaders();
	int ReadSymbolTableEntries();
	int ReadRelocationEntries();
public:
	//Methods
	void Initialize();
	void LoadModule();
	void LoadDevice();
	void LoadLibrary();
};

#endif //!__LOADER_H__
