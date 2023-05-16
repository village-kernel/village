//###########################################################################
// syscalls.c
// Low level file that manages system boot entry
//
// $Copyright: Copyright (C) village
//###########################################################################
/* Includes */
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
#include "HalHeaders.h"


/* Functions */
__attribute__((weak)) void initialise_monitor_handles()
{
}

__attribute__((weak)) int _getpid_r(void)
{
	return 1;
}

__attribute__((weak)) int _kill_r(int pid, int sig)
{
	errno = EINVAL;
	return -1;
}

__attribute__((weak)) void _exit_r(int status)
{
	_kill_r(status, -1);
	while (1) {}		/* Make sure we hang here */
}

__attribute__((weak)) int __io_getchar(void)
{
	return 0;
}

__attribute__((weak)) int _read_r(int file, char *ptr, int len)
{
	for (int index = 0; index < len; index++)
	{
		*ptr++ = __io_getchar();
	}
	return len;
}

__attribute__((weak)) void __io_putchar(int ch)
{
	
}

__attribute__((weak)) int _write_r(int file, char *ptr, int len)
{
	for (int index = 0; index < len; index++)
	{
		__io_putchar(*ptr++);
	}
	return len;
}

__attribute__((weak)) int _close_r(int file)
{
	return -1;
}

__attribute__((weak)) int _fstat_r(int file, struct stat *st)
{
	st->st_mode = S_IFCHR;
	return 0;
}

__attribute__((weak)) int _isatty_r(int file)
{
	return 1;
}

__attribute__((weak)) int _lseek_r(int file, int ptr, int dir)
{
	return 0;
}

__attribute__((weak)) int _open_r(char *path, int flags, ...)
{
	/* Pretend like we always fail */
	return -1;
}

__attribute__((weak)) int _wait_r(int *status)
{
	errno = ECHILD;
	return -1;
}

__attribute__((weak)) int _unlink_r(char *name)
{
	errno = ENOENT;
	return -1;
}

__attribute__((weak)) int _times_r(struct tms *buf)
{
	return -1;
}

__attribute__((weak)) int _stat_r(char *file, struct stat *st)
{
	st->st_mode = S_IFCHR;
	return 0;
}

__attribute__((weak)) int _link_r(char *old, char *new)
{
	errno = EMLINK;
	return -1;
}

__attribute__((weak)) int _fork_r(void)
{
	errno = EAGAIN;
	return -1;
}

__attribute__((weak)) int _execve_r(char *name, char **argv, char **env)
{
	errno = ENOMEM;
	return -1;
}
