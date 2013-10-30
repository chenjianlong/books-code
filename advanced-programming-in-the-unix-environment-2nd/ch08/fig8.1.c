/*
 * \file fig8.1.c
 * \brief Example of fork function
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-10-29
 */
/* $Id$ */

#include "apue.h"

int glob = 6;
char buf[] = "a write to stdout\n";

int main (void)
{
	int var;     /* automatic variable on the stack */
	pid_t pid;

	var = 88;
	if (write (STDOUT_FILENO, buf, sizeof (buf) - 1) != sizeof (buf) - 1) {
		err_sys ("write error");
	}
	printf ("before fork\n");	/* we don't flush stdout */

	if ((pid = fork ()) < 0) {
		err_sys ("fork error");
	} else if (pid == 0) {		/* child */
		glob++;
		var++;
	} else {
		sleep (2);				/* parent */
	}

	printf ("pid = %d, glob = %d, var = %d\n", getpid (), glob, var);
	exit (0);
}
