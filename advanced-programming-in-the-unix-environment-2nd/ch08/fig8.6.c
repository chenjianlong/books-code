/*
 * \file fig8.6.c
 * \brief Demonstrate various exit statuses
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-10-30
 */
/* $Id$ */

#include "apue.h"
#include <sys/wait.h>

int main (void)
{
	pid_t	pid;
	int		status;

	if ((pid = fork ()) < 0) {
		err_sys ("fork error");
	} else if (pid == 0) {				/* child */
		exit (7);
	}

	if (wait (&status) != pid) {		/* wait for child */
		err_sys ("wait error");
	}
	pr_exit (status);					/* and print its status */

	if ((pid = fork ()) < 0) {
		err_sys ("fork error");
	} else if (pid == 0) {				/* child */
		abort ();						/* generate SIGABRT */
	}

	if (wait (&status) != pid) {		/* wait for child */
		err_sys ("wait error");
	}
	pr_exit (status);					/* and print its status */

	if ((pid = fork ()) < 0) {
		err_sys ("fork error");
	} else if (pid == 0) {				/* child */
		status /= 0;					/* divide by 0 generates SIGFPE */
	}

	if (wait (&status) != pid) {		/* wait for child */
		err_sys ("wait error");
	}
	pr_exit (status);					/* and print its status */
	exit (0);
}
