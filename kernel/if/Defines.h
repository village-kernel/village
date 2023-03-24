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
	_display             = 21,
	_storage             = 31,
	_usbStorage          = 41,
};


///Module id defines
enum ModuleID
{
	_loader              = 1,
	_console             = 2,
	_application         = 200,
};


#endif //!__DEFINES_H__
