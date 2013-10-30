/*
 * \file fig8.13.c
 * \brief Modification of Figure8.12 to avoid race condition
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-10-30
 */
/* $Id$ */

#include "apue.h"

static void charatatime (char *);

int main (void)
{
	pid_t		pid;

	TELL_WAIT ();

	if ((pid = fork ()) < 0) {
		err_sys ("fork error");
	} else if (pid == 0) {
		WAIT_PARENT ();			/* parent goes first */
		charatatime ("output from child\n");
	} else {
		charatatime ("output from parent\n");
		TELL_CHILD (pid);
	}
	exit (0);
}

static void charatatime (char *str)
{
	char	*ptr;
	int		c;

	setbuf (stdout, NULL);			/* set unbuffered */
	for (ptr = str; (c = *ptr++) != 0; ) {
		putc (c, stdout);
	}
}
