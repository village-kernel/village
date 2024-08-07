//###########################################################################
// CmdDefs.h
// Declarations of the interface cmd
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __CMD_DEFINES_H__
#define __CMD_DEFINES_H__


///Command register macro
#define REGISTER_CMD(cmd, name)                                   \
static struct _CMD_##name {                                       \
	Cmd* command = cmd;                                           \
	_CMD_##name() {                                               \
		kernel->terminal.RegisterCmd(command, (char*)#name);      \
	}                                                             \
	~_CMD_##name() {                                              \
		kernel->terminal.DeregisterCmd(command, (char*)#name);    \
	}                                                             \
} const _cmd_##name __attribute__((used,__section__(".cmds")))


#endif //!__CMD_DEFINES_H__
