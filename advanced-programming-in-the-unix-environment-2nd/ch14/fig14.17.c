/*
 * \file fig14.17.c
 * \brief Test the isastream function
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-11-25
 */
/* $Id$ */

#include "apue.h"
#include <fcntl.h>

int main (int argc, char *argv[])
{
	int		i, fd;

	for (i = 1; i < argc; i++) {
		if ((fd = open (argv[i], O_RDONLY)) < 0) {
			err_ret ("%s: can't open", argv[i]);
			continue;
		}

		if (isastream (fd) == 0) {
			err_ret ("%s: not a stream", argv[i]);
		} else {
			err_msg ("%s: stream device", argv[i]);
		}
	}

	exit (0);
}
