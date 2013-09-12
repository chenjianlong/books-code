/*
 * \file fig4.16.c
 * \brief Open a file and then unlink it
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-09-12
 */
/* $Id$ */

#include "apue.h"
#include <fcntl.h>

int main (void)
{
	if (open("tempfile", O_RDWR) < 0) {
		err_sys ("open error");
	}
	if (unlink ("tempfile") < 0) {
		err_sys ("unlink error");
	}
	printf ("file unlinked\n");
	sleep (15);
	printf ("done\n");
	exit (0);
}

