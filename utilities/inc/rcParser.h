//###########################################################################
// rcParser.h
// Parse run command script
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __RC_PARSER_H__
#define __RC_PARSER_H__

#include "Defines.h"

///RcParser
class RcParser
{
public:
	//Structrues
	struct RunCmdNode
	{
		const char* cmd;
		RunCmdNode* next;

		RunCmdNode(const char* cmd = NULL) :
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
	void Decode(const char* rcString);
public:
	//Methods
	RcParser(const char* filename = NULL);
	int Load(const char* filename);
	RunCmdNode* GetRunCmds();
	void Release();
};

#endif //!__RC_PARSER_H__
