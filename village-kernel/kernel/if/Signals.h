//###########################################################################
// Signals.h
// Declarations of the interface
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __SIGNALS_H__
#define __SIGNALS_H__

enum Signals
{
	_None = 0,
	
	_Sleep,
	_Standby,
	_Shutdown,
	_Reboot,

	_Kill,
};

#endif //!__SIGNALS_H__
