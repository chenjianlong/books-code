/*
 * \file fig8.3.c
 * \brief Example of vfork function
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-10-29
 */
/* $Id$ */

#include "apue.h"

int glob = 6;				/* external variable in initialized data */

int main (void)
{
	int var;     /* automatic variable on the stack */
	pid_t pid;

	var = 88;
	printf ("before vfork\n");	/* we don't flush stdio */

	if ((pid = vfork ()) < 0) {
		err_sys ("vfork error");
	} else if (pid == 0) {		/* child */
		glob++;
		var++;
		_exit (0);
	}

	/* Parent continues here. */
	printf ("pid = %d, glob = %d, var = %d\n", getpid (), glob, var);
	exit (0);
}
