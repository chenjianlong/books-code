/*
 * \file ex8.7.c
 * \brief Verify opendir is set close-on-exec
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-10-31
 */
/* $Id$ */

#include "apue.h"
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>

int main (void)
{
	DIR *dir = opendir ("/");
	int fd = 0;
	int fdflag = 0;
	if (NULL == dir) {
		err_sys ("opendir error");
	}

	fd = dirfd (dir);
	if (-1 == (fdflag = fcntl (fd, F_GETFD, 0))) {
		err_sys ("fcntl F_GETFD error");
	}
	if (fdflag & FD_CLOEXEC) {
		printf ("FD_CLOEXEC is set in opendir\n");
	} else {
		printf ("FD_CLOEXEC is not set in opendir\n");
	}

	closedir (dir);

	fd = open ("/", O_RDONLY);
	if (-1 == (fdflag = fcntl (fd, F_GETFD, 0))) {
		err_sys ("fcntl F_GETFD error");
	}
	if (fdflag & FD_CLOEXEC) {
		printf ("FD_CLOEXEC is set in open\n");
	} else {
		printf ("FD_CLOEXEC is not set in open\n");
	}

	exit (0);
}

