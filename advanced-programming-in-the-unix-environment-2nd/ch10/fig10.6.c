/*
 * \file fig10.6.c
 * \brief System V SIGCLD handler doesn't work
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-11-13
 */
/* $Id$ */

#include "apue.h"
#include <sys/wait.h>

static void sig_cld (int);

int main (void)
{
	pid_t	pid = 0;
	if (signal (SIGCLD, sig_cld) == SIG_ERR) {
		perror ("signal error");
	}
	if ((pid = fork ()) < 0) {
		perror ("fork error");
	} else if (pid == 0) {		/* child */
		sleep (2);
		_exit (0);
	}
	pause ();		/* parent */
	exit (0);
}

static void sig_cld (int signo) /* interrupts pause () */
{
	pid_t	pid = 0;
	int		status;

	printf ("SIGCLD received\n");
	if (signal (SIGCLD, sig_cld) == SIG_ERR) { /* reestablish handler */
		perror ("signal error");
	}
	if ((pid == wait (&status)) < 0) {	/* fetch child status */
		perror ("wait error");
	}
	printf ("pid = %d\n", pid);
}
