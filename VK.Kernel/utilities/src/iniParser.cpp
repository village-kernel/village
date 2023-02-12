//###########################################################################
// IniParser.cpp
// Manages system configurations and parameters
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "iniParser.h"
#include "stdlib.h"
#include "ff.h"


///Load *.ini file and decode
void IniParser::Load(std::string filePath)
{
	FATFS fs; FIL file; UINT br;

	if (f_mount(&fs, "0:", 1) == FR_OK)
	{
		if (f_open(&file, filePath.c_str(), FA_READ) == FR_OK)
		{
			std::string str;
			str.resize(f_size(&file));
			f_read(&file, (void*)str.c_str(), str.size(), &br);
			f_close(&file);
			Decode(str);
			std::string().swap(str);
		}
		f_unmount("0:");
	}
}


///Encode and save to *.ini file
void IniParser::Save(std::string filePath)
{
	FATFS fs; FIL file; UINT bw;

	if (f_mount(&fs, "0:", 1) == FR_OK)
	{
		if (f_open(&file, filePath.c_str(), FA_CREATE_ALWAYS | FA_WRITE) == FR_OK)
		{
			std::string str = Encode();
			f_write(&file, (void*)str.c_str(), str.size(), &bw);
			f_close(&file);
			std::string().swap(str);
		}
		f_unmount("0:");
	}
}


///Remove leadingand trailing spaces
inline std::string IniParser::RemoveSpaces(std::string str)
{
	if (!str.empty())
	{
		str.erase(str.find_last_not_of(" ") + 1);
		str.erase(0, str.find_first_not_of(" "));
	}
	return str;
}


///Decode the ini data
inline void IniParser::Decode(std::string iniString)
{
	std::string keyName = "";
	std::string keyValue = "";
	std::string sectionName = "";
	std::string::iterator it;
	ParserStatus status = _NullRecord;

	for (it = iniString.begin(); it != iniString.end(); it++)
	{
		char byte = *it;

		switch (byte)
		{
			case '[':
				sectionName = "";
				status = _RecordSectionName;
				break;

			case ']':
				keyName = "";
				status = _RecordKeyName;
				break;

			case '=':
				keyValue = "";
				status = _RecordKeyValue;
				break;

			case '\n':
				if (_RecordKeyValue == status)
				{
					keyName = RemoveSpaces(keyName);
					keyValue = RemoveSpaces(keyValue);
					sectionName = RemoveSpaces(sectionName);
					sections[sectionName][keyName] = keyValue;
				}
				keyName = "";
				status = _RecordKeyName;
				break;

			default:
				if (byte >= ' ' && byte <= '~')
				{
					if (_RecordSectionName == status)
						sectionName += byte;
					else if (_RecordKeyName == status)
						keyName += byte;
					else if (_RecordKeyValue == status)
						keyValue += byte;
				}
				break;
		}
	}
}


///Encode the ini data
inline std::string IniParser::Encode()
{
	std::string iniString = "";
	std::map<std::string, std::string>::iterator keyit;
	std::map<std::string, std::map<std::string, std::string>>::iterator secit;

	for (secit = sections.begin(); secit != sections.end(); secit++)
	{
		iniString += '[' + secit->first + "]\r\n";

		for (keyit = secit->second.begin(); keyit != secit->second.end(); keyit++)
		{
			iniString += keyit->first + '=' + keyit->second + "\r\n";
		}

		iniString += "\r\n";
	}

	return iniString;
}


///Write the section key value
void IniParser::WriteValue(std::string section, std::string key, std::string value)
{
	sections[section][key] = value;
}


///Read the section key value
std::string IniParser::ReadValue(std::string section, std::string key)
{
	return sections[section][key];
}


///Release sections
void IniParser::Release()
{
	sections.clear();
	std::map<std::string, std::map<std::string, std::string>>().swap(sections);
}
