/*
 * \file ex9.2.c
 * \brief Create a new session
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-11-04
 */
/* $Id$ */

#include "apue.h"
#include <errno.h>

static void pr_ids (char *name)
{
	printf ("%s: pid = %d, ppid = %d, pgrp = %d, tpgrp = %d\n",
		name, getpid (), getppid (), getpgrp (), tcgetpgrp (STDIN_FILENO));
	fflush (stdout);
}

int main (void)
{
	pid_t	pid;

	pr_ids ("parent");
	if ((pid = fork ()) < 0) {
		err_sys ("fork error");
	} else if (pid > 0) { /* parent */
		exit (0);		  /* then parent exits */
	} else {			  /* child */
		pr_ids ("child before setsid");
		if (-1 == setsid ()) {
			err_sys ("setsid failed");
		}
		pr_ids ("child after setsid");			/* prints only if we're continued */
	}
	exit (0);
}


