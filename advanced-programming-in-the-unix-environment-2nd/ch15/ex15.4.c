/*
 * \file ex15.4.c
 * \brief Program to drive the add2 filter
 * \author Jianlong Chen <jianlong99@gmail.com>
 * \date 2013-12-03
 */
/* $Id$ */

#include "apue.h"

int main (void)
{
	int		n, fd1[2], fd2[2];
	pid_t	pid;
	char	line[MAXLINE];

	if (pipe (fd1) < 0 || pipe (fd2) < 0) {
		err_sys ("pipe error");
	}

	if ((pid = fork ()) < 0) {
		err_sys ("fork error");
	} else if (pid > 0) {
		close (fd1[0]);
		close (fd2[1]);
		while (fgets (line, MAXLINE, stdin) != NULL) {
			n = strlen (line);
			if (write (fd1[1], line, n) != n) {
				err_sys ("write error to pipe");
			}
			if ((n = read (fd2[0], line, MAXLINE)) < 0) {
				err_sys ("read error from pipe");
			}
			if (n == 0) {
				err_msg ("child closed pipe");
				break;
			}
			line[n] = 0;	/* null terminate */
			if (fputs (line, stdout) == EOF) {
				err_sys ("fputs error");
			}
		}
		if (ferror (stdin)) {
			err_sys ("fgets error on stdin");
		}
		exit (0);			/* child */
	} else {
		close (fd1[1]);
		close (fd2[0]);
	}
	exit (0);
}
