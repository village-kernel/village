//###########################################################################
// Loader.h
// Declarations of the functions that manage loader
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __LOADER_H__
#define __LOADER_H__

#include "Module.h"


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

	enum ELFClass
	{
		_ELF_Class_None   = 0,
		_ELF_Class_32     = 1,
		_ELF_Class_64     = 2,
	};

	enum ELFType
	{
		_ELF_Type_None    = 0,
		_ELF_Type_Rel     = 1,
		_ELF_Type_Exec    = 2,
		_ELF_Type_Dyn     = 3,
		_ELF_Type_Core    = 4,
		_ELF_Type_LO_Proc = 5,
		_ELF_Type_HI_Proc = 6,
	};

	enum ELFMachine
	{
		_ELF_Machine_None  = 0,
		_ELF_Machine_ARM   = 40,
	};

	enum ELFVersion
	{
		_ELF_Ver_None    = 0,
		_ELF_Ver_Current = 1,
	};

	enum RelocationCode
	{
		_R_ARM_NONE       = 0,
		_R_ARM_ABS32      = 2,
		_R_ARM_THM_CALL   = 10,
		_R_ARM_THM_JUMP24 = 30,
		_R_ARM_TARGET1    = 38,
		_R_ARM_THM_JUMP11 = 102,
	};

	enum SectionHeadrType
	{
		_SHT_NULL          = 0x00,
		_SHT_PROGBITS      = 0x01,
		_SHT_SYMTAB        = 0x02,
		_SHT_STRTAB        = 0x03,
		_SHT_RELA          = 0x04,
		_SHT_HASH          = 0x05,
		_SHT_DYNAMIC       = 0x06,
		_SHT_NOTE          = 0x07,
		_SHT_NOBITS        = 0x08,
		_SHT_REL           = 0x09,
		_SHT_SHLIB         = 0x0a,
		_SHT_DYNSYM        = 0x0b,
		_SHT_INIT_ARRAY    = 0x0e,
		_SHT_FINI_ARRAY    = 0x0f,
		_SHT_PREINIT_ARRAY = 0x10,
		_SHT_GROUP         = 0x11,
		_SHT_SYMTAB_SHNDX  = 0x12,
		_SHT_NUM           = 0x13,
		_SHT_LOOS          = 0x60000000,
	};

	enum SymbolType
	{
		_STT_NOTYPE     = 0,
		_STT_OBJECT     = 1,
		_STT_FUNC       = 2,
		_STT_SECTION    = 3,
		_STT_FILE       = 4,
		_STT_LOPROC     = 13,
		_STT_HIPROC     = 15,
	};

	enum SymbolBind
	{
		_STB_LOCAL    = 0,
		_STB_GLOBAL   = 1,
		_STB_WEAK     = 2,
		_STB_LOPROC   = 13,
		_STB_HIPROC   = 15,
	};

	//Symbol Structures
	struct SymbolEntry
	{
		uint32_t     name;
		uint32_t     value;
		uint32_t     size;
		uint8_t      type : 4;
		uint8_t      bind : 4;
		uint8_t      other;
		uint16_t     index;
	};

	struct Symbol
	{
		uint8_t*     name;
		SymbolEntry* entry;
		Symbol*      next;
	};

	struct SymbolTable
	{
		Symbol*      symbols;
		uint8_t*     sectionName;
		uint32_t     sectionIndex;
		SymbolTable* next;
	};

	struct RelocationEntry
	{
		uint32_t offset;
		uint32_t type:8;
		uint32_t symbol:8;
		uint32_t reversed:16;
	};

	struct Relocation
	{
		uint8_t*         name;
		RelocationEntry* entry;
		Relocation*      next;
	};

	struct RelocationTable
	{
		Relocation*      relocations;
		uint8_t*         sectionName;
		uint32_t         sectionIndex;
		RelocationTable* next;
	};

	//Elf header Structures
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

	//Porgram structures
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

	//Dynamic structures
	struct DynamicHeader
	{
		int32_t tag;
		union
		{
			uint32_t val;
			uint32_t ptr;
		};
	};

	//Section structures
	struct SectionHeader
	{
		uint32_t name;
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

	struct Section
	{
		SectionHeader* header;
		uint8_t*       name;
		union
		{
			uint8_t*         data;
			SymbolEntry*     symEntries;
			RelocationEntry* relEntries;
		};
		Section*       next;
	};

	//ELF structure
	struct ELF
	{
		uint8_t*         map;
		ELFHeader*       header;
		Section*         sections;
		SymbolTable*     symTabs;
		RelocationTable* relTabs;
	};
	
	//Members
	ELF elf;

	//Methods
	int LoadElf(const char* path);
	int ParserElfHeader();
	int ParserElfSection();
	int ParserSymbolEntries();
	int ParserRelocationEntries();
	int RelocationEntries();
	int RelocationSymbolCall(uint32_t relAddr, uint32_t symAddr, int type);
	int RelocationJumpCall(uint32_t relAddr, uint32_t symAddr, int type);
	int ExecuteElf();
public:
	//Methods
	void Initialize();
	void LoadModule();
	void LoadDevice();
	void LoadLibrary();
};

#endif //!__LOADER_H__
