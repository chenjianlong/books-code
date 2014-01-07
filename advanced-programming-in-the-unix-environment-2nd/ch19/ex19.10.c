/*
 * \file ex19.10.c
 * \brief exec ex19.10b and send/recv message
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2014-01-07
 */
/* $Id$ */

#include "apue.h"

int main (void)
{
	pid_t pid;
	int fdm;
	char slave_name[20];

	write (STDOUT_FILENO, "begin\n", sizeof ("begin\n"));
	if ((pid = pty_fork (&fdm, slave_name, sizeof (slave_name), NULL, NULL)) < 0) {
		err_sys ("pty_fork failed");
	}

	if (pid == 0) { /* child */
		if (execlp ("./ex19.10b", "ex19.10b") < 0) {
			err_sys ("exec failed");
		}
	}

	sleep (10);
	write (STDOUT_FILENO, "end\n", sizeof ("end\n"));
	exit (0);
}

