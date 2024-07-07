//###########################################################################
// ElfLoader.h
// Declarations of the functions that manage elf loader
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __ELF_LOADER_H__
#define __ELF_LOADER_H__

#include "ElfDefines.h"


/// @brief ElfLoader
class ElfLoader : public ElfDefines
{
private:
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
private:
	//Members
	ELF   elf;
	char* filename;

	//Linker members
	bool isIgnoreUnresolvedSymbols;

	//Methods
	bool LoadElf();
	bool PreParser();
	bool SetMapAddr();
	bool LoadProgram();
	bool PostParser();
	bool SharedObjs();
	bool RelEntries();
	void RelSymCall(uint32_t relAddr, uint32_t symAddr, uint8_t type, uint32_t size);
#if defined(ARCH_ARM)
	void RelJumpCall(uint32_t relAddr, uint32_t symAddr, uint8_t type);
#endif
public:
	//Methods
	ElfLoader(const char* filename = NULL);
	~ElfLoader();
	bool Load(const char* filename);
	bool FillBssZero();
	bool InitArray();
	bool Execute(const char* symbol = NULL, int argc = 0, char* argv[] = NULL);
	bool FiniArray();
	bool Exit();

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

	//Linker methods
	void IgnoreUnresolvedSymbols(bool enable = true);
};

#endif //!__ELF_LOADER_H__
