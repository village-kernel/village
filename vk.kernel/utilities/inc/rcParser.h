//###########################################################################
// rcParser.h
// Parse run command script
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __RC_PARSER_H__
#define __RC_PARSER_H__

#include "Defines.h"
#include "Templates.h"

///RcParser
class RcParser
{
private:
	//Enumerations
	enum ParserStatus
	{
		_NotRecord = 0,
		_RecordCmd,
		_SaveCmd,
	};

	//Members
	List<char*> runcmds;

	//Methods
	void Decode(const char* rcString);
public:
	//Methods
	RcParser(const char* filename = NULL);
	int Load(const char* filename);
	List<char*>& GetRunCmds();
	void Release();
};

#endif //!__RC_PARSER_H__
