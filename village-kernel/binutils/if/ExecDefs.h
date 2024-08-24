//###########################################################################
// ExecDefs.h
// Declarations of the interface executor
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __EXEC_DEFINES_H__
#define __EXEC_DEFINES_H__

#include "stddef.h"
#include "stdint.h"


///Executor register macro
#define REGISTER_EXECUTOR(exec, name)                             \
static struct _Exec_##name {                                      \
	Executor* executor = exec;                                    \
	_Exec_##name() {                                              \
		kernel->process.RegisterExecutor(executor);               \
	}                                                             \
	~_Exec_##name() {                                             \
		kernel->process.UnregisterExecutor(executor);             \
	}                                                             \
} const _exec_##name __attribute__((used,__section__(".executors")))


#endif //!__EXEC_DEFINES_H__
