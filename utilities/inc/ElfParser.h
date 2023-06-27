//###########################################################################
// ElfParser.h
// Declarations of the functions that manage elf parser
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __ELF_PARSER_H__
#define __ELF_PARSER_H__

#include "Defines.h"


///ElfParser
class ElfParser
{
private:
	//Type define
	typedef void(*Function)();
	typedef void(*Entry)(int argc, char* argv[]);

	//Enumerations
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
		_ELF_Machine_None     = 0x00,
		_ELF_Machine_X86      = 0x03,
		_ELF_Machine_ARM      = 0x28,
		_ELF_Machine_ARM_64   = 0xb7,
		_ELF_Machine_RISC_V   = 0xf3,
	};

	enum ELFVersion
	{
		_ELF_Ver_None    = 0,
		_ELF_Ver_Current = 1,
	};

#if defined(ARCH_X86)
	enum RelocationCode
	{
		_R_386_NONE       = 0,
		_R_386_32         = 1,
		_R_386_PC32       = 2,
		_R_386_GOT32      = 3,
		_R_386_PLT32      = 4,
		_R_386_COPY       = 5,
		_R_386_GLOB_DAT   = 6,
		_R_386_JMP_SLOT   = 7,
		_R_386_RELATIVE   = 8,
		_R_TYPE_RELATIVE  = _R_386_RELATIVE,
		_R_386_GOTOFF     = 9,
		_R_386_GOTPC      = 10,
		_R_386_32PLT      = 11,
		_R_386_16         = 20,
		_R_386_PC16       = 21,
		_R_386_8          = 22,
		_R_386_PC8        = 23,
		_R_386_SIZE32     = 38,
	};
#elif defined(ARCH_ARM)
	enum RelocationCode
	{
		_R_ARM_NONE       = 0,
		_R_ARM_ABS32      = 2,
		_R_ARM_THM_CALL   = 10,
		_R_ARM_RELATIVE   = 23,
		_R_TYPE_RELATIVE  = _R_ARM_RELATIVE,
		_R_ARM_THM_JUMP24 = 30,
		_R_ARM_TARGET1    = 38,
		_R_ARM_THM_JUMP11 = 102,
	};
#endif

	enum ProgramHeaderType
	{
		_PT_NULL          = 0x00,
		_PT_LOAD          = 0x01,
		_PT_DYNAMIC       = 0x02,
		_PT_INTERP        = 0x03,
		_PT_NOTE          = 0x04,
		_PT_SHLIB         = 0x05,
		_PT_PHDR          = 0x06,
		_PT_TLS           = 0x07,
		_PT_NUM           = 0x08,
		_PT_LOOS          = 0x60000000,
		_PT_GNU_EH_FRAME  = 0x6474e550,
		_PT_GNU_STACK     = 0x6474e551,
		_PT_GNU_RELRO     = 0x6474e552,
		_PT_LOSUNW        = 0x6ffffffa,
		_PT_SUNWBSS       = 0x6ffffffa,
		_PT_SUNWSTACK     = 0x6ffffffb,
		_PT_HISUNW        = 0x6fffffff,
		_PT_HIOS          = 0x6fffffff,
		_PT_LOPROC        = 0x70000000,
		_PT_HIPROC        = 0x7fffffff,
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

	enum DynamicType
	{
		_DT_NULL        = 0,
		_DT_NEEDED      = 1,
		_DT_PLTRELSZ    = 2,
		_DT_PLTGOT      = 3,
		_DT_HASH        = 4,
		_DT_STRTAB      = 5,
		_DT_SYMTAB      = 6,
		_DT_RELA        = 7,
		_DT_RELASZ      = 8,
		_DT_RELAENT     = 9,
		_DT_STRSZ       = 10,
		_DT_SYMENT      = 11,
		_DT_INIT        = 12,
		_DT_FINI        = 13,
	};

	//Structures
	struct SymbolEntry
	{
		uint32_t     name;
		uint32_t     value;
		uint32_t     size;
		uint8_t      type : 4;
		uint8_t      bind : 4;
		uint8_t      other;
		uint16_t     shndx;
	};

	struct RelocationEntry
	{
		uint32_t offset;
		uint8_t  type;
		uint8_t  symbol;
		uint16_t reversed;
	};

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
		union
		{
			uint32_t val;
			uint32_t ptr;
			uint32_t offset;
		};
	};

	union SectionData
	{
		uint32_t         addr;
		uint8_t*         data;
		uint8_t*         dynstr;
		uint8_t*         strtab;
		uint8_t*         shstrtab;
		Function*        funcs;
		SymbolEntry*     symtab;
		SymbolEntry*     dynsym;
		DynamicHeader*   dynamic;
		RelocationEntry* reltab;
		
		SectionData(uint32_t addr):
			addr(addr)
		{}
	};

	//ELF structure
	struct ELF
	{
		uint32_t         map;
		uint32_t         load;
		uint32_t         exec;
		
		ELFHeader*       header;
		SectionHeader*   sections;
		ProgramHeader*   programs;

		DynamicHeader*   dynamics;
		uint32_t         dynsecNum;
		SymbolEntry*     dynsym;
		uint32_t         dynsymNum;
		uint8_t*         dynstr;

		SymbolEntry*     symtab;
		uint32_t         symtabNum;
		uint8_t*         strtab;
		uint8_t*         shstrtab;
	};
	
	//Static constants members
	static const uint32_t base_map_address =0x400000;
	static uint32_t mapAddr;
	char* filename;

	//Members
	ELF elf;

	//Methods
	int LoadElf();
	int PreParser();
	int SegmentMapping();
	int PostParser();
	int SharedObjs();
	int RelEntries();
	int RelSymCall(uint32_t relAddr, uint32_t symAddr, int type);
#if defined(ARCH_ARM)
	int RelJumpCall(uint32_t relAddr, uint32_t symAddr, int type);
#endif
public:
	//Methods
	ElfParser(const char* filename = NULL);
	int Load(const char* filename);
	//int LoadLib(const char* filename);
	int InitArray();
	int Execute(const char* symbol = NULL, int argc = 0, char* argv[] = NULL);
	int FiniArray();
	int Exit();

	//Tool methods
	const char* GetFileName();
	const char* GetDynamicString(uint32_t index);
	const char* GetSectionName(uint32_t index);
	const char* GetSymbolName(uint32_t index);
	const char* GetDynSymName(uint32_t index);
	uint32_t GetSymbolAddr(uint32_t index);
	uint32_t GetDynSymAddr(uint32_t index);
	uint32_t GetSymbolAddrByName(const char* name);
	uint32_t GetDynSymAddrByName(const char* name);
	SectionData GetSectionData(uint32_t index);
	SectionData GetDynSectionData(uint32_t index);
};

#endif //!__ELF_PARSER_H__
