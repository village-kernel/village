//###########################################################################
// Regex.h
// Text regular expression
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __REGEX_H__
#define __REGEX_H__

#include "Defines.h"

///Regex
class Regex
{
public:
	//Structrues
	struct String
	{
		const char* str;
		String* next;

		String(const char* str = NULL) :
			str(str),
			next(NULL)
		{}
	};
private:
	//Members
	String* strings;
public:
	//Methods
	Regex();
	~Regex();
	String* Split(const char* s, const char r = ' ');
	int Size();
	char** ToArray();
};

#endif //!__REGEX_H__
