//###########################################################################
// Defines.h
// Declarations of the interface
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DEFINES_H__
#define __DEFINES_H__

#include "stdint.h"
#include "stddef.h"


///Execute result defines
enum Result
{
	_OK     = 0,
	_ERR    = 1,
};


///Driver id defines
enum DriverID
{
	_serial              = 1,
	_storage             = 21,
	_drvLoadr            = 41,
	_display             = 61,
	_network             = 81,
	_usbdev              = 101,
	_usbhost             = 151,
	_miscdev             = 201,
};


///Module id defines
enum ModuleID
{
	_console             = 1,
	_modLoader           = 2,
	_executor            = 21,
	_application         = 101,
};


#endif //!__DEFINES_H__
