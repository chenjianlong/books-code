/*
 * \file fig4.21.c
 * \brief Example of utime function
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-09-12
 */
/* $Id$ */

#include "apue.h"
#include <fcntl.h>
#include <utime.h>

int main (int argc, char *argv[])
{
	int i, fd;
	struct stat statbuf;
	struct utimbuf timebuf;

	for (i = 1; i < argc; i++) {
		if (stat (argv[i], &statbuf) < 0) {
			err_ret ("%s: stat error", argv[i]);
			continue;
		}
		if ((fd = open (argv[i], O_RDWR | O_TRUNC)) < 0) {
			err_ret ("%s: oepn error", argv[i]);
			continue;
		}
		close (fd);
		timebuf.actime = statbuf.st_atime;
		timebuf.modtime = statbuf.st_mtime;
		if (utime (argv[i], &timebuf) < 0) {
			err_ret ("%s: utime error", argv[i]);
			continue;
		}
	}
	exit (0);
}

