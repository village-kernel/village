//###########################################################################
// Debug.h
// Declarations of the debug
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "stdint.h"
#include "stddef.h"

#ifdef Debug
#include "stdio.h"
#define printk(...)               printf(__VA_ARGS__)
#else
#define printk(...)               /* */
#endif

#endif //!__DEBUG_H__
