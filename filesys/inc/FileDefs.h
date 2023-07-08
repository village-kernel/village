//###########################################################################
// FileDefs.h
// Declarations of the interface file system
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FILE_DEFINES_H__
#define __FILE_DEFINES_H__


///Command register macro
#define REGISTER_FS(fs, name)                                 \
static struct _FS_##name {                                    \
	FileOpt* fileOpt = fs;                                    \
	_FS_##name() {                                            \
		FileSystem::Instance().RegisterOpt(fileOpt, #name);   \
	}                                                         \
	~_FS_##name() {                                           \
		FileSystem::Instance().DeregisterOpt(fileOpt, #name); \
	}                                                         \
} const _fs_##name __attribute__((used,__section__(".fs")))


#endif //!__FILE_DEFINES_H__
