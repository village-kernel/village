//###########################################################################
// rcParser.h
// Parse resource script
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __RC_PARSER_H__
#define __RC_PARSER_H__

#include <string>
#include <list>


///RcParser
class RcParser
{
public:
	//Enumerations
	enum Result
	{
		_OK     = 0,
		_ERR    = 1,
	};
private:
	//Enumerations
	enum ParserStatus
	{
		_NullRecord = 0,
		_RecordResource,
		_SaveResource,
	};

	//Members
	std::list<std::string> resources;

	//Methods
	void Decode(std::string rcString);
public:
	//Methods
	int Load(std::string filePath);
	std::list<std::string> GetResources();
	void Release();
};

#endif //!__RC_PARSER_H__
