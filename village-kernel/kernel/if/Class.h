//###########################################################################
// Class.h
// Declarations of the class
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __CLASS_H__
#define __CLASS_H__

#include "stdint.h"
#include "stddef.h"
#include "stdlib.h"


/// @brief Base
class Base
{
private:
	//Members
	int   id;
	char* name;
public:
	//Constructor
	Base(): id(-1), name((char*)"Unknown") {}

	//Destructor
	virtual ~Base() {}

	//Methods
	void SetID(int id)         { this->id = id;     }
	int  GetID()               { return this->id;   }
	void SetName(char* name)   { this->name = name; }
	char* GetName()            { return this->name; }
};


/// @brief Class
class Class {};
typedef void (Class::*Method)(void*);
typedef void (*Function)(void*, void*);

#endif //!__CLASS_H__
