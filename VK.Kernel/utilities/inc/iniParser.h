//###########################################################################
// IniParser.h
// Manages system configurations and parameters
//
// $Copyright: Copyright (C) jingwei
//###########################################################################
#ifndef __INI_PARSER_H__
#define __INI_PARSER_H__

#include "HalHeaders.h"
#include <string>
#include <map>


///IniParser
class IniParser
{
private:
	//Enumerations
	enum ParserStatus
	{
		_NullRecord = 0,
		_RecordSectionName,
		_RecordKeyName,
		_RecordKeyValue,
	};

	//Members
	std::map<std::string, std::map<std::string, std::string>> sections;

	//Methods
	std::string RemoveSpaces(std::string str);
	void Decode(std::string iniString);
	std::string Encode();
public:
	//Methods
	void Load(std::string filePath);
	void Save(std::string filePath);

	void WriteValue(std::string section, std::string key, std::string value);
	std::string ReadValue(std::string section, std::string key);
	void Release();
};

#endif // !__INI_PARSER_H__
