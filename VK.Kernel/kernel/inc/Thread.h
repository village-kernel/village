//###########################################################################
// Thread.h
// Declarations of the functions that manage thread
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __THREAD_H__
#define __THREAD_H__

#include "Kernel.h"

extern "C" 
{

void Task0(void);
void Task1(void);

void StartScheduler(void);
}

#endif // !__THREAD_H__
