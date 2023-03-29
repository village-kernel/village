//###########################################################################
// rcParser.h
// Parse run command script
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __RC_PARSER_H__
#define __RC_PARSER_H__

#include "Defines.h"
#include <string>

///RcParser
class RcParser
{
public:
	//Structrues
	struct RunCmdNode
	{
		std::string cmd;
		RunCmdNode* next;

		RunCmdNode(std::string cmd = NULL) :
			cmd(cmd),
			next(NULL)
		{}
	};
private:
	//Enumerations
	enum ParserStatus
	{
		_NotRecord = 0,
		_RecordCmd,
		_SaveCmd,
	};

	//Members
	RunCmdNode* runcmds;

	//Methods
	void Decode(char* rcString);
public:
	//Methods
	RcParser(const char* filename = NULL);
	int Load(const char* filename);
	RunCmdNode* GetRunCmds();
	void Release();
};

#endif //!__RC_PARSER_H__
