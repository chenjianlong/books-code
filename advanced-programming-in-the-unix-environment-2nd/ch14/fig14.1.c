/*
 * \file fig14.1.c
 * \brief Large nonblocking write
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-11-25
 */
/* $Id$ */

#include "apue.h"
#include <errno.h>
#include <fcntl.h>

char buf[500000];

int main (void)
{
	int		ntowrite, nwrite;
	char	*ptr;

	ntowrite = read (STDIN_FILENO, buf, sizeof (buf));
	fprintf (stderr, "read %d bytes\n", ntowrite);

	set_fl (STDOUT_FILENO, O_NONBLOCK);	/* set nonblocking */

	ptr = buf;
	while (ntowrite > 0) {
		errno = 0;
		nwrite = write (STDOUT_FILENO, ptr, ntowrite);
		fprintf (stderr, "nwrite = %d, errno = %d\n", nwrite, errno);

		if (nwrite > 0) {
			ptr += nwrite;
			ntowrite -= nwrite;
		}
	}

	clr_fl (STDOUT_FILENO, O_NONBLOCK);	/* clear nonblocking */

	exit (0);
}
