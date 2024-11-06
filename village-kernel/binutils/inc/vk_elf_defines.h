//###########################################################################
// vk_elf_defines.h
// Declarations of the functions that manage elf loader
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_ELF_DEFINES_H__
#define __VK_ELF_DEFINES_H__

#include "vk_defines.h"


/// @brief 
class ElfDefines
{
public:
	//Type define
	typedef void(*Function)();
	typedef void(*StartEntry)(void* kernel, int argc, char* argv[]);
	typedef void(*FuncEntry)(int argc, char* argv[]);

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
		_R_TYPE_COPY      = _R_386_COPY,
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
		_R_ARM_COPY       = 20,
		_R_TYPE_COPY      = _R_ARM_COPY,
		_R_ARM_GLOB_DAT   = 21,
		_R_ARM_JUMP_SLOT  = 22,
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
		_STB_LOCAL      = 0,
		_STB_GLOBAL     = 1,
		_STB_WEAK       = 2,
		_STB_LOPROC     = 13,
		_STB_HIPROC     = 15,
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
		_DT_SONAME      = 14,
		_DT_RPATH       = 15,
		_DT_SYMBOLIC    = 16,
		_DT_REL         = 17,
		_DT_RELSZ       = 18,
		_DT_RELENT      = 19,
		_DT_PLTREL      = 20,
		_DT_DEBUG       = 21,
		_DT_TEXTREL     = 22,
		_DT_JMPREL      = 23,
		_DT_ENCODING    = 32,
		_OLD_DT_LOOS    = 0x60000000,
		_DT_LOOS        = 0x6000000d,
		_DT_HIOS        = 0x6ffff000,
		_DT_VALRNGLO    = 0x6ffffd00,
		_DT_VALRNGHI    = 0x6ffffdff,
		_DT_ADDRRNGLO   = 0x6ffffe00,
		_DT_ADDRRNGHI   = 0x6ffffeff,
		_DT_VERSYM      = 0x6ffffff0,
		_DT_RELACOUNT   = 0x6ffffff9,
		_DT_RELCOUNT    = 0x6ffffffa,
		_DT_FLAGS_1     = 0x6ffffffb,
		_DT_VERDEF      = 0x6ffffffc,
		_DT_VERDEFNUM   = 0x6ffffffd,
		_DT_VERNEED     = 0x6ffffffe,
		_DT_VERNEEDNUM  = 0x6fffffff,
		_OLD_DT_HIOS    = 0x6fffffff,
		_DT_LOPROC      = 0x70000000,
		_DT_HIPROC      = 0x7fffffff,
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
};

#endif //!__VK_ELF_DEFINES_H__
