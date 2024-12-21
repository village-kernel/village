//###########################################################################
// vk_hex_loader.h
// Declarations of the functions that manage hex loader
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_HEX_LOADER_H__
#define __VK_HEX_LOADER_H__

#include "vk_elf_defines.h"
#include "vk_list.h"


/// @brief HexLoader
class HexLoader : public ElfDefines
{
private:
	//Record Type
	enum RecordType
	{
		_Data            = 00,
		_EndOfFile       = 01,
		_ExtSegAddr      = 02,
		_StartSegAddr    = 03,
		_ExtLinearAddr   = 04,
		_StartLinearAddr = 04,
	};

	//Hex record
	struct Record
	{
		uint8_t  length;
		uint16_t address;
		uint8_t  type;
		char*    data;

		Record()
			:length(0),
			address(0),
			type(0),
			data(NULL)
		{}
	};

	//ELF structure
	struct HEX
	{
		uint32_t text;
		uint32_t load;
		uint32_t base;
		uint32_t exec;

		uint32_t offset;
		uint32_t dynamic;
		uint32_t entry;
	};
private:
	//Members
	HEX             hex;
	VkList<Record*> records;
	char*           filename;
	
	//Methods
	bool LoadHex();
	bool PreParser();
	bool LoadProgram();
	bool PostParser();
	bool RelEntries();
	bool Cleanup();

	//Tool Methods
	uint16_t HexStrToInt(char* str, int size);
	bool     Checksum(char* text);
	Record*  DecodeRecord(char* text);
public:
	//Methods
	HexLoader(const char* filename = NULL);
	~HexLoader();
	bool Load(const char* filename);
	bool Execute(int argc = 0, char* argv[] = NULL);
	bool Exit();
};

#endif //!__VK_HEX_LOADER_H__
