//###########################################################################
// Exception.h
// Declarations of the functions that manage exception
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include "Templates.h"


/// @brief Exception
class Exception : public Class
{
private:
	//Methods
	void ATAChannel1();
	void ATAChannel2();
	void GerneralFault();
public:
	//Methods
	Exception();
	~Exception();
	void Initialize();

	//Static methods
	static Exception& Instance();
};

///Declarations exception reference
extern Exception& exception;

#endif //!__EXCEPTION_H__
